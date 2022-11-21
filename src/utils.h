#include <Arduino.h>
#include <ESP32_Servo.h>

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
    Serial.println(plant.moisturePercent);
    return plant;
}

// Turn on pump
void turnOnPump(Servo myServo, Plant plant, int highThreshold, int PUMP_PIN) {
    int position = 0;
    myServo.attach(PUMP_PIN);

    while(plant.moisturePercent < highThreshold) {
        myServo.write(position);
        position++;
        delay(20);
        plant = updatePlantValues(plant);
        Serial.print("In while, moisture: ");
        Serial.println(plant.moisturePercent);
    }

    myServo.detach();
}