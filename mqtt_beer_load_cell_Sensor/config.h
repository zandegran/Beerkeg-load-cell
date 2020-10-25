
// Wifi Settings
#define SSID                          "<SSID>"
#define PASSWORD                      "<Password>"

#define ENABLE_DHT false
#define ENABLE_DISPLAY true
#define ENABLE_MQTT true
#define ENABLE_SCALE true  // Only for debugging
#define TARE_ON_START false

#define MEASURE_INTERVAL 10000 // 10 sec

// MQTT Settings
#define HOSTNAME                      "beer1"
#define MQTT_SERVER                   "industrial.api.ubidots.com"
#define TOPIC                         "/v1.6/devices/beer1"
#define TARE_TOPIC                    "/v1.6/devices/beer1/tare"
#define mqtt_username                 "<Token>"
#define mqtt_password                 ""
#define PUBLISH_INTERVAL 900000 // Interval between publishing 900 * 1000 = 900000 = 15 mins


// Display variables
#define DURATION 2000 // Duration between screens
typedef void (*Screen)(void);
void drawStats();
void drawLogo();
Screen screens[] = {drawStats, drawLogo};

// HX711 Pins
const int LOADCELL_DOUT_PIN = 2;  // Remember these are ESP GPIO pins, they are not the physical pins on the board.
const int LOADCELL_SCK_PIN = 3;
int calibration_factor = -22500;  // Defines calibration factor we'll use for calibrating.
int offset_factor = -137202;       // Defines offset factor if you have static weight on the loadcell. For exaple the wight of a empty Cornelius keg. 

// DHT Settings
constexpr auto DHT_PIN = 4;            // Remember these are ESP GPIO pins, they are not the physical pins on the board. 
#define DHT_TYPE DHT22                 // DHT11 or DHT22
constexpr auto sendDHTDataDelay = 500ul; // Delay between sending data over MQTT
