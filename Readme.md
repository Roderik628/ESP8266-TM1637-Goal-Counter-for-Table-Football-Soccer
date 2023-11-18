
# ESP8266 TM1637 Goal Counter for Table Football Soccer
Controller for an Arduino based Automatic Gate Slider

## Desciption
Modified the code from Mr. Morgenthaler (http://oszt.ch/projekt-automatischer-torzaehler-fuer-tischkicker/) to work with ESP8266 and TM1637 display. (maybe even with ESP32 if the pins are configured accordingly) 
  
<img src="/display.jpg">


## Things used in this project 
- ESP8266 x1
- DC5V Infrared Beam Sensor x2		https://www.aliexpress.com/item/4000264402274.html?spm=a2g0o.order_list.order_list_main.131.6f7c1802ionLN1
- TM1637 7-segment display x1		https://www.aliexpress.com/item/1005002059351703.html?spm=a2g0o.order_list.order_list_main.161.6f7c1802ionLN1
- Breadboard x1
- Jumper cables (for better reliability i suggest a soldering the connections or using durable connectors)
- Momentary switch x1
- USB cable x1

## Modification
The display can´t show the colon symbol when there isnt a grater number then 0 so i had to modifiy the display with a jumper resistor on the seven segment display. I used a 220Ω smd resistor so the colon symbol is turned on.
<img src="/displaycolonmod.jpg">


## Connection

<img src="/circuit.png">

## code
Install TM1637 library by Avishay Orpaz  (https://github.com/avishorp/TM1637)

https://github.com/Roderik628/ESP8266-TM1637-Goal-Counter-for-Table-Football-Soccer/blob/e1b069ad7dda86bd175c4e2eb9a5251f3075e6a3/ESP8266_TM1637_Goal_Counter_for_Table_Football_Soccer.ino#L1