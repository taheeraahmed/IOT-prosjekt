#include <Servo.h>

Servo myservo;

#define PUMPPIN 9    //peristaltic pump control pin, connect to arduino digital pin 9
#define waitTime 2000 //interval time(ms) between every state

void setup()
{
  myservo.attach(PUMPPIN);
}

void loop()
{
    myservo.write(0);   //Clockwise maximum speed rotation
    delay(waitTime);
    myservo.write(90);  //Stop
    delay(waitTime);
    myservo.write(180); //Counterclockwise maximum speed rotation
    delay(waitTime);
    myservo.write(90);  //Stop
    delay(waitTime);
}