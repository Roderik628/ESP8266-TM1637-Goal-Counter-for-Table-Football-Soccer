/*   
  Code for automatic table soccer counter. By teacher Morgenthaler and student Leo at Swiss school www.oszt.ch
  Modified by Roderik628
  https://github.com/Roderik628/ESP8266-TM1637-Goal-Counter-for-Table-Football-Soccer
*/
                                           
// Libraries 
#include <Wire.h>                                 
#include <TM1637Display.h>

#define CLK  14    // The ESP8266 pin D5 connected to CLK
#define DIO  12    // The ESP8266 pin D6  connected to DIO


// create a display object of type TM1637Display
TM1637Display display = TM1637Display(CLK, DIO);

// Defining varialbes for the two goals
int Red;                                          
int Blue;

// Defining ESP's board-LED. For controlling purpose only during coding
#define LEDPIN 13                                 
                                                 
// Defining the two pins the data connections of the breakbeam sensors 
#define SENSORPIN 4     // The ESP8266 pin D2 (Blue Goal)                      
#define SENSORPIN2 5    // The ESP8266 pin D1 (Red Goal)

// Defining the pin for the back to zero button                            
#define SENSORPIN3 3    // The ESP8266 pin RX                         

 // Initalizing and defining states for the breakbeam sensors and the back to zero button 
int sensorState = 0, lastState=0;               
int sensorState2 = 0, lastState2=0;              
int sensorState3 = 0, lastState3=0;              
                                                 
void setup() {        
  
  display.clear();
  
  Serial.begin(115200);
  Serial.println("Successfully started, find out more on https://github.com/Roderik628/ESP8266-TM1637-Goal-Counter-for-Table-Football-Soccer");
  
  // Initializing Arduino's board LED for output                                                
  pinMode(LEDPIN, OUTPUT);                        
                                                  
  // Initializing pin for input from breakbeam sensor                                               
  pinMode(SENSORPIN, INPUT);  
  // Activating the pullup resistor for this pin to make the two sensor states clear for Arduino                    
  digitalWrite(SENSORPIN, HIGH);                  

  // Same for other breakbeam sensor
  pinMode(SENSORPIN2, INPUT);                     
  digitalWrite(SENSORPIN2, HIGH);

  // Same for back to zero button
  pinMode(SENSORPIN3, INPUT);                     
  digitalWrite(SENSORPIN3, HIGH);

  // Start value for goals
  Red = 0;                                         
  Blue = 0;
  
  
  display.setBrightness(7); // set the brightness to 7 (0:dimmest, 7:brightest)                              
//-------------------------------------------------------------------------------------------------------
  // Display score on start Red on left side, Blue on right side 
  //display.showNumberDecEx(Red, false, 0b01000000, 1, 0);
  //display.showNumberDecEx(Blue, false, 0b01000000, 2, 2);

  // If you want to switch the sides uncomment the 2 lines above and comment these 2 lines and change the display code in void loop()
  display.showNumberDecEx(Blue, false, 0b01000000, 1, 0);
  display.showNumberDecEx(Red, false, 0b01000000, 2, 2);
//-------------------------------------------------------------------------------------------------------  
}


void loop(){                                      
  // Next 3 lines: Read and save states of the 2 sensors and the back to zero button                                               
  sensorState = digitalRead(SENSORPIN);           
  sensorState2 = digitalRead(SENSORPIN2);
  sensorState3 = digitalRead(SENSORPIN3);         
    
//-------------------------------------------------------------------------------------------------------
    // The following lines are for displaying the the goal values on the display.
    // This if argument prevents from displaying a zero with numbers under 10

  /*
    
    // Display Red
    if (Red < 10) {
      display.showNumberDecEx(Red, 0b01000000, false, 1, 0);
    }
    else {
      display.showNumberDecEx(Red, 0b01000000, false, 2, 0);
    }

    // Display Blue
    display.showNumberDecEx(Blue, 0b01000000, false, 2, 2);

  */
    
    // Uncomment the above lines and comment these lines too if you want to switch the sides
    //Display Blue
    
    if (Blue < 10) {
      display.showNumberDecEx(Blue, 0b01000000, false, 1, 0);
    }
    else {
      display.showNumberDecEx(Blue, 0b01000000, false, 2, 0);
    }

    // Display Red
    display.showNumberDecEx(Red, 0b01000000, false, 2, 2);      
                   
//-------------------------------------------------------------------------------------------------------

   // 3 if-else arguments following for the two breakbeam sensors and the back to zero button 
   // If sensor light beam is broken, system reads status low and turns the control LED on                                     
  if (sensorState == LOW) {                 
    digitalWrite(LEDPIN, HIGH);             
  } 
  // otherwise no power for the control LED
  else {
    digitalWrite(LEDPIN, LOW);            
  }
  
  // If SensorState does not differ from lastState...
  // (The "!" reverses the signal state to function correclty.
  // Without it, the goal values constantly increase when light beams ar UNbroken)
  if (sensorState && !lastState) {                
                                                  
    // ...The message Unbroken would be displayed on Arduino's serial monitor                                              
    Serial.println("1 Unbroken");                 
                                               
  } 
  // If it differs, "Broken" would be displayed and the goal variable Red is increased. 
  if (!sensorState && lastState) {
    Serial.println("1 Broken");                                                               
    Red = Red + 1;                                 
  }
  
  // Same for other breakbeam sensor
  if (sensorState2 && !lastState2) {               
    Serial.println("2 Unbroken");
  }
  if (!sensorState2 && lastState2) {
    Serial.println("2 Broken");
    Blue = Blue + 1;                              
  }
  // Check status of back to zero button 
  if (sensorState3 && !lastState3) {               
  }
  // If pressed, the serial display would show "reset" and both goal variables are reset to zero.
  if (!sensorState3 && lastState3) {
    Serial.println("reset");                       
    Blue = 0;                                      
    Red = 0;
    // Clears everything displayed on LED
    display.clear();
  }
 // Save the last sensor states 
  lastState = sensorState;                     
  lastState2 = sensorState2;                       
  lastState3 = sensorState3;
}                                                  
// End of programm. Restart void loop
