/********************************************************************
*	Program:	line_detect.ino                                     *
*	Author:		康心奕 Ewing Kang									*
*	Time: 		2015/10/25											*
*	Contect: 	f039281310@yahoo.com.tw								*
*	License:	GPL                   								*
*	About:															*
*                                                                   *
*	Note:															*
*																	*
*********************************************************************/ 
#define LD_COUNT 3
#define PIN_LD_L 13 // the LED pin
#define PIN_LD_M 12
#define PIN_LD_R 11
byte pin_lndec[] = {PIN_LD_L, PIN_LD_M, PIN_LD_R};
bool LD_state[LD_COUNT];

void setup() {
    Serial.begin(9600);
    Serial.print("initialize the Line Dectector program");
    for (byte i=0; i<LD_COUNT; i++)
    {
        pinMode(pin_lndec[i], INPUT);     //set the pin_rc to input
        digitalWrite(pin_lndec[i], HIGH); //use the internal pullup resistor
        LD_state[i] = LOW;
    }
}

void loop() {
    for (byte i=0; i<LD_COUNT; i++)
    {
        LD_state[i] = digitalRead(pin_lndec[i]); //read the digital state
        if (LD_state[i])
        {
          Serial.print(i);
        }
    }
    Serial.println("  ;");
    delay(100);                 // wait for 0.1 sec
}
