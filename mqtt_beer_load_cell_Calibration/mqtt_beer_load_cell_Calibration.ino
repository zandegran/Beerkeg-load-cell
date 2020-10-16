#include "HX711.h"

HX711 scale;  // Initializes library functions.

const float KNOWN_WEIGHT = 5.76;  // In kilograms

const int LOADCELL_DOUT_PIN = 2;          //Remember these are ESP GPIO pins, these might not be the pins labeled on the board.
const int LOADCELL_SCK_PIN = 3;

const int INITIAL_INCREMENTS = 50;
const float FLUCTUATION_TOLERANCE = 0.3;

long calibration_factor = -500;

int foundUpperBound = 0;


void setup()
{
  Serial.begin(74880);   
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.println("Initializing scale calibration.");  // Prints user commands.
  Serial.println("Please remove all weight from scale.");

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);   // Initializes the scaling process.
  Serial.println("began");
  scale.set_scale();
  Serial.println("scale set");
  digitalWrite(LED_BUILTIN, HIGH);
  scale.tare();          // Resets the scale to 0.
  digitalWrite(LED_BUILTIN, HIGH); 
  Serial.println("Please place the weight");
  delay(5000);
}

void printBounds(float lowerBound, float upperBound) {
   float midpoint = lowerBound + ((upperBound - lowerBound) / 2);
   Serial.println("#############################");
   Serial.println("##   LB:"+ String(lowerBound) + " UB: " + String(upperBound) + "   ##");
   Serial.println("##   CF:"+ String(midpoint) +  "            ##");
   Serial.println("#############################");
}

void binarySearch(float lowerBound, float upperBound) {
  float wtForUpperBound = getWeight(upperBound);
  float wtForLowerBound = getWeight(lowerBound);
  float wt = 0;
  do {
    float midpoint = lowerBound + ((upperBound - lowerBound) / 2);
    wt = getWeight(midpoint);
    if (wt == KNOWN_WEIGHT) {
      break;
    }
    if (wt > KNOWN_WEIGHT) {
      lowerBound = midpoint;
      wtForLowerBound  = wt;
    }
    else if (wt < KNOWN_WEIGHT) {
      upperBound = midpoint;
      wtForUpperBound = wt;
    }
    Serial.println("LB:  " + String(lowerBound) +" UB:  " + String(wtForUpperBound));
    Serial.println("LBW: " + String(wtForLowerBound) +" UBW: " + String(wtForUpperBound));
    if (wt < wtForLowerBound || wt > wtForUpperBound) {
      // Too much fluctuation retrying
      return; 
     }
  } while (lowerBound < upperBound); // Loop will fail when the fluctuation is high
  printBounds(lowerBound, upperBound);
}

float getWeight(float calibrationFactor) {
  digitalWrite(LED_BUILTIN, LOW); 
  scale.power_up();
  scale.set_scale(calibration_factor); 
  scale.wait_ready();
  float wt = scale.get_units(10);
  Serial.println("Reading: " + String(wt) +" cf: " + String(calibrationFactor));
  scale.power_down();
  digitalWrite(LED_BUILTIN, foundUpperBound == 0 ? LOW : HIGH); // Dont turn off led on no weight
  delay(3000);
  return wt;
}

bool isWeightOnScale(float fluctuationTolerance) {
  float wt = getWeight(calibration_factor);
  Serial.println("wt on scale: " + String(wt));
  wt *= wt < 0 ? -1 : 1; // ABS
  wt > fluctuationTolerance;
}

int getUpperBound() {
  // Seek upper bound
  float wt = getWeight(calibration_factor);
  while (wt < KNOWN_WEIGHT && wt > 0) {
    calibration_factor += INITIAL_INCREMENTS;
    if (calibration_factor != 0) {
      wt = getWeight(calibration_factor);
    }
    Serial.println(wt);
    Serial.println("Seeking bounds: " + String(calibration_factor)+ " current wt: " + String(wt));
  }
  Serial.println("UPPER BOUND FOUND" + String(calibration_factor));
  return calibration_factor;
}

void loop()
{
    if (foundUpperBound == 0) { // Execute once after weight is placed
      foundUpperBound = getUpperBound();
    }
    binarySearch(foundUpperBound - INITIAL_INCREMENTS, foundUpperBound + INITIAL_INCREMENTS);
  
  delay(1000);  
}
