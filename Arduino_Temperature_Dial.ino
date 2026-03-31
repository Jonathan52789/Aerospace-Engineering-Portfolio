//include libraries to control the servo and temperature sensor
#include <Servo.h>
#include <DHT.h>


//Define the pin numbers with their apparatus
const int GreenPin=6,RedPin=9,ServoPin=11,TempPin=2;


//Define the minimum and maximum temperatures of the dial and the movement threshold
const float TempMin=0.0,TempMax=40.0,ChangeThreshold=0.1;


//Define the temperature sensor and servo as global variables
DHT dht(TempPin,DHT11);
Servo servo;


//Function for flashing the red LED
void FlashRed(){
 
  //Flashes the red LED for 100ms
  digitalWrite(RedPin,HIGH);
  delay(100);
  digitalWrite(RedPin,LOW);
}


//Function for initial setup
void setup(){


//Begin talking to the arduino and the temperature sensor
  Serial.begin(115200);
  dht.begin();


//Attach the servo to a pwm pin to control its motion
  servo.attach(ServoPin);
 
  //Define LEDs as outputs and turns on the green one to indicate the dial is running
  pinMode(GreenPin,OUTPUT);
  pinMode(RedPin,OUTPUT);
  digitalWrite(GreenPin,HIGH);
}


//Loop function which runs temperature check and moves the dial accordingly
void loop(){


  //Defines angle and temperature variables along with a lastTemp variable for tracking changes between cycles
  float angle, Temperature;
  static float lastTemp;


  //Reads Temperature from the sensor and then ensures that the sensor works by verifying its output is a number
  Temperature = dht.readTemperature();
  if(isnan(Temperature)){
    Serial.println("Temperature Sensor Error");
    return;
  }


  //Constrains Temperature to values in the dial's range (0-40°C)
  Temperature = constrain(Temperature,TempMin,TempMax);


  //Print out Temperature
  Serial.print("The Temperature is ");
  Serial.print(Temperature);
  Serial.println(" °C");


  //Calculates an angle from 0-180° corresponding to the current Temperature
  angle=Temperature/(TempMax-TempMin)\*180;


  //Print out servo angle
  Serial.print("The angle is ");
  Serial.print(angle);
  Serial.println(" °");


  //Move the servo to the desired angle corresponding to the Temperature
  servo.write(angle);


  //Flash red LED if change is above the threshold
  if(abs(Temperature-lastTemp)>ChangeThreshold){
    FlashRed();
  }


  //Sets the current temperature as the last temperature for the next loop
  lastTemp=Temperature;


  //Delay the next Temperature check to avoid constant servo movement
  delay(500);


}