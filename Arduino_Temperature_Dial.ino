//include libraries to control the servo and temperature sensor
#include <Servo.h> 
#include <DHT.h> 

//Define the temperature sensor and servo as global variables
DHT dht(2,DHT11);
Servo servo; 

//Function for initial setup
void setup(){ 

//Begin talking to the arduino and the temperature sensor
  Serial.begin(115200); 
  dht.begin();

//Attach the servo to a pwm pin
  servo.attach(11); 
  
  //Define LED as an output and turn it on to indicate dial is active
  pinMode(6,OUTPUT); 
  digitalWrite(6,HIGH); 
}

//Loop function which runs temperature check and moves the dial accordingly
void loop(){

  //Defines variables for the Temperature and servo angle
  float angle, Temperature;

  //Reads Temperature from the sensor and then ensures that the sensor works by verifying its output is a number
  Temperature = dht.readTemperature();
  if(isnan(Temperature)){
    Serial.println("Temperature Sensor Error");
    return;
  }

  //Constrains Temperature to values in the dial's range (0-40°C)
  Temperature = constrain(Temperature,0.0,40.0);

  //Print out Temperature
  Serial.print("The Temperature is ");
  Serial.print(Temperature);
  Serial.println(" °C");

  //Calculates an angle from 0-180° corresponding to the Temperature from 0-40°C
  angle=Temperature*4.5;

  //Print out servo angle
  Serial.print("The angle is ");
  Serial.print(angle);
  Serial.println(" °");

  //Move the servo to the desired angle corresponding to the Temperature
  servo.write(angle);

  //Delay the next Temperature check so the servo isn't constantly moving
  delay(500); 
}