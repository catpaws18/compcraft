#include <Adafruit_CircuitPlayground.h>

const int growthSensorPin1 = A1; //detection of base1 
const int growthSensorPin2 = A2; // detection of base2

const int neoPixel1 = 0; //when the grnd connects to base 1 
const int neoPixel2 = 5; //when the grnd connects to base 2 
const int connectiondata = 700; //threshold value.. the average threshold is 300 when not connected 


int readings1[5] = {0, 0, 0, 0, 0}; //taking average of 5 readings 
int readings2[5] = {0, 0, 0, 0, 0}; //taking average of 5 readings to "reduce the noise"
int readIndex = 0;

void setup() {
  CircuitPlayground.begin();
  CircuitPlayground.setBrightness(30); //brightness level 
  
  pinMode(growthSensorPin1, INPUT_PULLUP); //inputpulldown activates an internal resistor that weakly connects the pin to ground 
  pinMode(growthSensorPin2, INPUT_PULLUP); //making sure the pinMode is reading all the input data from the sensorpins 
  

  Serial.begin(9600); //serial communication 

}

void loop() {

  int baseValue1 = analogRead(growthSensorPin1); //analogread reads the sensor value 
  int baseValue2 = analogRead(growthSensorPin2); 
  
  readings1[readIndex] = baseValue1; //LLM suggestion to average the last 5 readings, random spikes or drops get smoothed out 
  readings2[readIndex] = baseValue2; 
  readIndex = (readIndex + 1) % 5;
  
  int avgValue1 = 0;
  int avgValue2 = 0;
  for (int i = 0; i < 5; i++) {
    avgValue1 += readings1[i];
    avgValue2 += readings2[i];
  }
  avgValue1 = avgValue1 / 5;
  avgValue2 = avgValue2 / 5;
  
  Serial.print("Base1 Value: ");
  Serial.print(baseValue1);
  Serial.print(" Avg: ");
  Serial.print(avgValue1);
  Serial.print("\tBase2 Value: ");
  Serial.print(baseValue2);
  Serial.print(" Avg: ");
  Serial.println(avgValue2);
 
  //Base1 value checking
  if (avgValue1 > connectiondata) {
    CircuitPlayground.setPixelColor(neoPixel1, 0, 255, 0); //turns on the neopixel  
  } else {
    CircuitPlayground.setPixelColor(neoPixel1, 0, 0, 0); // turns off
  }
  
  // Base2 value checking 
  if (avgValue2 > connectiondata) {
    CircuitPlayground.setPixelColor(neoPixel2, 0, 0, 255); //turns on the neopixel blue 
  } else {
    CircuitPlayground.setPixelColor(neoPixel2, 0, 0, 0); // turns off
  }
  
  delay(100);
}