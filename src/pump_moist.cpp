#include <Arduino.h>
#include <ESP32_Servo.h>
#include <map>

// Defining the necessary pins
const int MOISTURE_PIN_1 = 25;
const int MOISTURE_PIN_2 = 25;
const int MOISTURE_PIN_3 = 25;
const int PUMP_PIN = 26;
Servo servo; 

// Humidity threshold values
const int threshold = [20,60];

struct plant {
    int moisturePin;
    int moistureValue;
    int moisturePercent;
} plant1, plant2, plant3;

// Map-like function which constraints the input and output values
int getPercent(int x, int in_min, int in_max, int out_min, int out_max) {
    if (x > in_max) {
        return out_max;
    }
    else if (x < in_min) {
        return out_min;
    } 
    else {
        return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    }
}

// Function which updates the moisture values 
plant updatePlantValues(plant plant) {
    const int airValue = 4094;
    const int waterValue = 2800;

    plant.moistureValue = analogRead(plant.moisturePin); 
    plant.moisturePercent = getPercent(soilMoistureValue, waterValue, airValue,   100, 0);
    return plant;
}

// Turn on pump
void turnOnPump(Servo myServo, int soilMoisturePercent, int highThreshold) {
    int position = 0;
    myServo.attach(PUMP_PIN);

    while(soilMoisturePercent < highThreshold) {
        myServo.write(position);
        position++;
        delay(20);
        soilMoisturePercent = updateMoistureValues();
    }
    myServo.detach();
}

void setup() {
    Serial.begin(9600); 
    plant1.moisturePin = MOISTURE_PIN_1;
    plant2.moisturePin = MOISTURE_PIN_2;
    plant3.moisturePin = MOISTURE_PIN_3;
}
 
void loop() {
    plant1 = updatePlantValues(plant1);
    plant2 = updatePlantValues(plant2);
    plant3 = updatePlantValues(plant3);

    // If the soil moisture is below the low threshold, turn on the pump
    switch() {
        case plant1.moisturePercent < threshold[0]:
            turnOnPump(servo, plant1.moisturePercent, threshold[1]);
            break;
        case plant2.moisturePercent < threshold[0]:
            turnOnPump(servo, plant2.moisturePercent, threshold[1]);
            break;
        case plant3.moisturePercent < threshold[0]:
            turnOnPump(servo, plant3.moisturePercent, threshold[1]);
            break;
    }
}