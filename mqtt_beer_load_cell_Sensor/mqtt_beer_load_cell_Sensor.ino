
#include <Arduino.h>
#include <ArduinoJson.h>
#include <HX711.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
#include "config.h"
// Include custom images
#include "images.h"
#include "SSD1306Brzo.h"
SSD1306Brzo display(0x3c, D2, D1, GEOMETRY_128_32);

WiFiServer server(80);

DHT dht{DHT_PIN, DHT_TYPE};      // Initiate DHT library
HX711 scale;                     // Initiate HX711 library
WiFiClient wifiClient;           // Initiate WiFi library
PubSubClient client(wifiClient); // Initiate PubSubClient library

float publishVolume;
float publishRaw;
float publishTemperature;
float publishHumidity;

int currentScreen = 0;
int seqLength = (sizeof(screens) / sizeof(Screen));
long timeSinceLastModeSwitch = 0;
long timeSinceLastPublish = 0;
long timeSinceLastMeasurement = 0;

void WiFiStart() {
  WiFi.mode(WIFI_STA);
  Serial.print("Connecting to ");
  Serial.println(SSID);
  WiFi.begin(SSID, PASSWORD);
//  WiFi.config(ip, gateway, subnet);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print("_");   
    digitalWrite(LED_BUILTIN, LOW);  
    delay(10);    
    digitalWrite(LED_BUILTIN, HIGH);                 
  }
  Serial.println();
  Serial.println("Done");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("");
                   
}

String getJsonString() {
  DynamicJsonDocument doc(1024);
  doc["rawVolume"] = publishRaw;
  doc["volume"] = publishVolume;
  if (ENABLE_DHT) {
    doc["temperature"] = publishTemperature;
    doc["humidity"] = publishHumidity;
  }
  String output = "";
  serializeJsonPretty(doc, output);
  Serial.println("::"+output);
  return output;
}

void setupScale() {
  Serial.println("Starting Scale Setup");
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN); // Start scale on specified pins
  scale.wait_ready();                               //Ensure scale is ready, this is a blocking function
  scale.set_scale();
  Serial.println("Scale Set");
  scale.wait_ready();
  if (TARE_ON_START) {  // Tare scale on startup
    scale.tare(); 
    scale.wait_ready();
    Serial.println("Scale Zeroed");
  }
}

void setupMqtt() {
  Serial.println("Starting MQTT client");
  client.setServer(MQTT_SERVER, 1883);              // Set MQTT server and port number
  client.setCallback(callback);                     // Set callback address, this is used for remote tare
}

void setupDisplay() {
  Serial.println("Starting Display");
  // Initialising the UI will init the display too.
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
}

void setup()
{
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(74880);
  WiFiStart();
  if (ENABLE_DISPLAY) {
    setupDisplay();
  }  
  if (ENABLE_MQTT){
    setupMqtt();
  }
  if (ENABLE_SCALE) {
    setupScale();   
  }  
  if (ENABLE_DHT) {
    Serial.println("Start DHT library");
    dht.begin();
  }
  // Start the server
  server.begin();
}

void drawStats() {
    // create more fonts at http://oleddisplay.squix.ch/
    display.setFont(ArialMT_Plain_24);
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.drawString(30, 5,  String(" ") +  String(publishVolume));
    display.drawXbm(0, 0, beer_width, beer_height, beer_bits);
}


void drawLogo() {
    // see http://blog.squix.org/2015/05/esp8266-nodemcu-how-to-create-xbm.html
    // on how to create xbm files
    display.drawXbm(0, 0, Logo_width, Logo_height, Logo_bits);
}

void drawDisplay() {
  //  Serial.println("Displaying ");
  // clear the display
  display.clear();
  screens[currentScreen]();
  // write the buffer to the display
  display.display();

  if (millis() - timeSinceLastModeSwitch > DURATION) {
    currentScreen = (currentScreen + 1)  % seqLength;
    timeSinceLastModeSwitch = millis();
  }
  delay(10);
}

void measureScale() {
    if (millis() - timeSinceLastMeasurement > MEASURE_INTERVAL) {
      timeSinceLastMeasurement = millis();
      scale.power_up();
      float reading;                       // Float for reading
      float raw;                           // Float for raw value which can be useful
      scale.wait_ready();                  // Wait till scale is ready, this is blocking if your hardware is not connected properly.
      scale.set_scale(calibration_factor); // Sets the calibration factor.
      scale.set_offset(offset_factor);     // Sets the offset factor.
    
      Serial.print("Reading: "); // Prints weight readings in .2 decimal kg units.
      scale.wait_ready();
      reading = scale.get_units(10); //Read scale in g/Kg
      raw = scale.read_average(5);   //Read raw value from scale too
      Serial.print(reading, 1);
      Serial.println(" L");
      Serial.print("Raw: ");
      Serial.println(raw);
      Serial.print("Calibration factor: "); // Prints calibration factor.
      Serial.println(calibration_factor);
    
      if (reading < 0)
      {
        reading = 0.00; //Sets reading to 0 if it is a negative value, sometimes loadcells will drift into slightly negative values
      }    
      publishVolume = reading;
      publishRaw = raw;
      
      scale.power_down(); // Puts the scale to sleep mode for 3 seconds. I had issues getting readings if I did not do this
    }
  }

void publishMeasurements() {
  // Ensure we are still connected to MQTT Topics
  if (!client.connected())
  {
    reconnect();
  }
   if (millis() - timeSinceLastPublish > PUBLISH_INTERVAL) {
      timeSinceLastPublish = millis();
      Serial.println("Publishing");
      client.publish(TOPIC, getJsonString().c_str());         // Publish weight to the STATE topic
   }
   client.loop();      // MQTT task loop
}

void measureTempAndHumidity() {
  // Reading values from the DHT sensor
  float humidity = dht.readHumidity();       // Read humidity
  float temperature = dht.readTemperature(); // Read temperature

  // Check if we recieved a number from dht libraray
  if (isnan(humidity) || isnan(temperature))
  {
    Serial.println("Error while parse values to numbers from dht");
  }
  publishTemperature = temperature;
  publishHumidity = humidity;
}
void readHttpRequests() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/json");
  client.println(""); //  do not forget this one
  // Match the request
  int value = 0;
  if (request.indexOf("/getstatus") != -1) {
    client.print(getJsonString());
  } 
  else if (request.indexOf("/tare") != -1) {
    tare();
    client.print("Scale reset");
  }
  else {
    client.print("Serving");
  }
  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
}

void (* resetFunc) (void) = 0;
void loop()
{
  if (ENABLE_DISPLAY) {
    drawDisplay();
  }
  if (ENABLE_SCALE) {
    measureScale(); 
  }  
  if (ENABLE_DHT) {
    measureTempAndHumidity();
  }
  if (ENABLE_MQTT) {
    publishMeasurements();
  }
  //Reconnect on lost WiFi connection
  if (WiFi.status() != WL_CONNECTED) {
    resetFunc();
  }
  readHttpRequests();
}



void reconnect()
{
  while (!client.connected())
  { // Loop until connected to MQTT server
    Serial.print("Attempting MQTT connection...");
    if (client.connect(HOSTNAME, mqtt_username, mqtt_password))
    { //Connect to MQTT server
      Serial.println("connected");
      client.subscribe(TARE_TOPIC);                 //Subscribe to tare topic for remote tare
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000); // Will attempt connection again in 5 seconds
    }
  }
}

void tare() {
    Serial.println("starting tare...");
    scale.power_up();
    scale.wait_ready();
    scale.set_scale();
    scale.tare(); //Reset scale to zero
    Serial.println("Scale reset to zero");
    scale.power_down();
}

void callback(char *topic, byte *payload, unsigned int length)
{
  if (strcmp(topic, TARE_TOPIC) == 0)
  {
    tare();
  }
}
