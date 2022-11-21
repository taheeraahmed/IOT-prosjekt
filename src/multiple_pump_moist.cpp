#include <Arduino.h>
#include <ESP32_Servo.h>
#include <map>
#include <list>

// Defining the necessary pins
const int MOISTURE_PIN_1 = 39;
const int MOISTURE_PIN_2 = 34;
const int MOISTURE_PIN_3 = 35;
const int PUMP_PIN = 26;
Servo servo; 

// Humidity threshold values
const int lowThreshold = 20;
const int highThreshold = 60;

struct Plant {
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
Plant updatePlantValues(Plant plant) {
    const int airValue = 4094;
    const int waterValue = 2800;

    plant.moistureValue = analogRead(plant.moisturePin); 
    plant.moisturePercent = getPercent(plant.moistureValue, waterValue, airValue,   100, 0);
    return plant;
}

// Turn on pump
void turnOnPump(Servo myServo, Plant plant, int highThreshold) {
    int position = 0;
    myServo.attach(PUMP_PIN);

    while(plant.moisturePercent < highThreshold) {
        myServo.write(position);
        position++;
        delay(20);
        plant = updatePlantValues(plant);
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
    Serial.println("Going into the loop!");
    plant1 = updatePlantValues(plant1);
    plant2 = updatePlantValues(plant2);
    plant3 = updatePlantValues(plant3);

    // If the soil moisture is below the low threshold, turn on the pump
    if(plant1.moisturePercent < lowThreshold) {
        turnOnPump(servo, plant1, highThreshold);
    }
    else if(plant2.moisturePercent < lowThreshold) {
        turnOnPump(servo, plant2, highThreshold);
    }
    else if(plant3.moisturePercent < lowThreshold) {
        turnOnPump(servo, plant3, highThreshold);
    }
}