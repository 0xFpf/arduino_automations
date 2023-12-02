#include <Servo.h>

int pos = 0;

int SensorValue = 0;

int OutputValue = 0;

int ultrasonicSensor = 0;

int delayvar=5; //in milliseconds, modify this to change how quickly the motor goes from 0-90 degrees

int delayloop=500; //in milliseconds, modify this to change how often it reads distance


long readUltrasonicDistance(int triggerPin, int echoPin)
{
  Serial.println("read Distance");
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

Servo servo_2;


void setup()
{
  Serial.println("setup");
  Serial.begin(9600);
  servo_2.attach(2, 500, 2500);
  servo_2.write(0);
}


void flutter(int amount, int delayed) {
      for (int i = 0; i < amount; ++i) {
        for (pos = 1; pos <= 90; pos += 1) {
            servo_2.write(pos);
            delay(delayvar);
        }
        for (pos = 90; pos >= 1; pos -= 1) {
            servo_2.write(pos);
            delay(delayvar);
        }
      }
    delay(delayed);
}


void loop()
{
  Serial.println("-------new loop-------");
  delay(delayvar);
  ultrasonicSensor = 0.01723 * readUltrasonicDistance(7, 6);
  Serial.print("distance= ");
  Serial.println(ultrasonicSensor);
  delay(delayvar);
  
  if (ultrasonicSensor > 80 && ultrasonicSensor <= 110) {
    Serial.println("<110");
    int loopCount = random(1, 3);
    Serial.println(loopCount);
    flutter(loopCount, delayloop);
  }
  
  else if (ultrasonicSensor>60 && ultrasonicSensor<=80) {
    Serial.println("<80");
    int loopCount = random(2, 4);
    flutter(loopCount, delayloop);
  } 
  
  else if(ultrasonicSensor>40 && ultrasonicSensor<=60) {
    Serial.println("<60");
    int loopCount = random(3, 5);
    flutter(loopCount, delayloop);
  } 
  
  else if(ultrasonicSensor <= 40) {
    Serial.println("<40");
    int loopCount = random(3, 6);
    flutter(loopCount, delayloop);
  } 
  
  else {
    servo_2.write(0);
  }   
    
  }