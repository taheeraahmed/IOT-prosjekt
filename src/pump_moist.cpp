#include <Arduino.h>
#include <ESP32_Servo.h>

// Defining the necessary variables
const int MOISTURE_PIN = 25;
const int PUMP_PIN = 26;
const int airValue = 4094;
const int waterValue = 2800;
const int lowThreshhold = 20;
const int highThreshold = 60;
int soilMoistureValue = 0;
int soilMoisturePercent = 0;
int position = 0;
Servo myServo; 

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
int updateMoistureValues() {
    soilMoistureValue = analogRead(MOISTURE_PIN); 
    soilMoisturePercent = getPercent(soilMoistureValue, waterValue, airValue,   100, 0);
    return soilMoisturePercent;
}

void setup() {
    Serial.begin(9600); 
}
 
void loop() {
    soilMoisturePercent = updateMoistureValues();

    // If the soil moisture is below the low threshold, turn on the pump
    if(soilMoisturePercent < lowThreshhold) {
        myServo.attach(PUMP_PIN);
        // Turn on pump
        while(soilMoisturePercent < highThreshold) {
            myServo.write(position);
            position++;
            delay(20);
            soilMoisturePercent = updateMoistureValues();
        }
        delay(20);
        myServo.detach();
    }

}