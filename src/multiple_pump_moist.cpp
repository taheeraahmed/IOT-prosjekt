#include <utils.h>

// Defining the necessary pins
const int MOISTURE_PIN_1 = 39;
const int MOISTURE_PIN_2 = 34;
const int MOISTURE_PIN_3 = 35;
const int PUMP_PIN = 26;
Servo servo; 

// Humidity threshold values
const int lowThreshold = 20;
const int highThreshold = 60;

void setup() {
    Serial.begin(9600); 
    plant1.moisturePin = MOISTURE_PIN_1;
    plant2.moisturePin = MOISTURE_PIN_2;
    plant3.moisturePin = MOISTURE_PIN_3;
}
 
void loop() {
    Serial.println("Going into the loop!");
    plant1 = updatePlantValues(plant1);
    plant2 = updatePlantValues(plant2);
    plant3 = updatePlantValues(plant3);

    // If the soil moisture is below the low threshold, turn on the pump
    if(plant1.moisturePercent < lowThreshold) {
        turnOnPump(servo, plant1, highThreshold, PUMP_PIN);
    }
    else if(plant2.moisturePercent < lowThreshold) {
        turnOnPump(servo, plant2, highThreshold, PUMP_PIN);
    }
    else if(plant3.moisturePercent < lowThreshold) {
        turnOnPump(servo, plant3, highThreshold, PUMP_PIN);
    }
}