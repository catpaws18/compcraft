
const int pressureSensorPin = A0; // analog input pin A0 that senses the pressure 
const int ledPin = A2;            // LED digital output pin 


const int FLICKER_ON_TIME = 50;     // duration LED stays on during flickering 
const int FLICKER_OFF_TIME = 50;    // duration LED stays off during flickering 
const int LOOP_DELAY = 10;

void setup() {
  pinMode(ledPin, OUTPUT);       //sets A2 as output 
  Serial.begin(9600);            //way for Arduino to communicate with the playground express 
}

void loop() {
  
  int pressure = analogRead(pressureSensorPin); //reads pressure sensor 

  Serial.println(pressure); //for debugging to see if there is pressure or not 

  if (pressure > HARD_PRESSURE) { //if the pressure when the two dots meet together is larger then hard pressure threshold then, LED flickers 
  
    digitalWrite(ledPin, HIGH);     // Turns LED on
    delay(FLICKER_ON_TIME);         // Keep LED on for the time defined earlier 
    digitalWrite(ledPin, LOW);      // Turn LED off 
    delay(FLICKER_OFF_TIME);        // Keep it off for 10sec for the flickering effect 

  }
  else if (pressure > LIGHT_PRESSURE) {  //if the pressure when the two dots meet together is between 200-500 then the LED only lights up 

    digitalWrite(ledPin, HIGH); //turns LED on 
  }
  else {
    
    digitalWrite(ledPin, LOW); //no pressure then the LED is off 
  }

  delay(LOOP_DELAY); //short delay
}
