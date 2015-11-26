/********************************************************************
*	Program:	pwm_modify.ino                                      *
*	Author:		康心奕 Ewing Kang									*
*	Time: 		2015/11/4											*
*	Contect: 	f039281310@yahoo.com.tw								*
*	License:	GPL                   								*
*	About:															*
*       This program give a demonstration about how to set the      *
*       timer control and output registers for timer 1.             *
*	Note:															*****
*	http://www.righto.com/2009/07/secrets-of-arduino-pwm.html           *
*   https://www.sparkfun.com/datasheets/Components/SMD/ATMega328.pdf    *
*   http://letsmakerobots.com/content/arduino-101-timers-and-interrupts *
*   http://blog.oscarliang.net/arduino-timer-and-interrupt-tutorial/    *
*************************************************************************/ 

#define PIN_TIMER1A 9       // pin that is controled by timer 1, OCR1A
#define PIN_TIMER1B 10      // pin that is controled by timer 1, OCR1B

bool clk_prescale[]={0, 1, 0};  // 8 prescaler
                                // Table 16-5 Clock Select Bit Description

void setup() {
    Serial.begin(9600);
    Serial.print("initialize the Line Dectector program");
    
    pinMode(PIN_TIMER1A, OUTPUT);
    pinMode(PIN_TIMER1B, OUTPUT);
   
    TCCR1A = _BV(COM1A1) | _BV(COM1B0) | _BV(COM1B1) | _BV(WGM11) | _BV(WGM10);
    
    OCR1A = 400;            // Output Compare Register timer1 A
    OCR1B = 1000;           // Output Compare Register timer1 B
    TCCR1B &= (-1<<3);          // reset the last 3 bits of 
                                // Timer/Counter Control Registsers B
                                // of Timer1
    TCCR1B |= (clk_prescale[2] << CS12);    // Clock Select bit
    TCCR1B |= (clk_prescale[1] << CS11);
    TCCR1B |= (clk_prescale[0] << CS10);

}

void loop() {
    Serial.println("program");
    delay(500);                 // wait for 0.1 sec
}
