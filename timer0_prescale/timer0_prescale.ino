/********************************************************************
*	Program:	timer0_prescale.ino                                 *
*	Author:		康心奕 Ewing Kang									*
*	Time: 		2015/11/4											*
*	Contect: 	f039281310@yahoo.com.tw								*
*	License:	GPL                   								*
*       This program give a demonstration about how to set the      *
*       timer control registers for timer 0.                        *
*	Note:															*****
*	http://www.righto.com/2009/07/secrets-of-arduino-pwm.html           *
*   https://www.sparkfun.com/datasheets/Components/SMD/ATMega328.pdf    *
*   http://letsmakerobots.com/content/arduino-101-timers-and-interrupts *
*   http://blog.oscarliang.net/arduino-timer-and-interrupt-tutorial/    *
*************************************************************************/ 

bool clk_prescale[]={0, 0, 1};      // 8 prescaler
                                    // Table 16-5 Clock Select Bit Description
long time_millis, timer_reg;        // time recorder

void setup() {
    Serial.begin(9600);
    Serial.print("initialize the Line Dectector program");
    
    TCCR0B &= (-1<<3);          // reset the last 3 bits of 
                                // Timer/Counter Control Registsers B
                                // of Timer0
    TCCR0B |= (clk_prescale[2] << CS12);        // Clock Select bit
    TCCR0B |= (clk_prescale[1] << CS11);
    TCCR0B |= (clk_prescale[0] << CS10);
}

void loop() {
    time_millis = millis();             // call the function that uses timer0
    timer_reg = TCNT0;                  // get the original value inside Timer/Counter Register 0
    
    Serial.print("time passed is: ");
    Serial.print(time_millis);  Serial.print(" ms, and TCNT0 ");
    Serial.print(timer_reg);  Serial.print(" with prescalar ");
    // print the prescalar, note the order starts from the MSB
    Serial.print(clk_prescale[2]);Serial.print(clk_prescale[1]);Serial.println(clk_prescale[0]);
    delay(100);                 // wait for 0.1 sec

}
