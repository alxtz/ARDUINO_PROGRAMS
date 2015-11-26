/********************************************************************
*	Program:	ultrasonic2.ino                                     *
*	Author:		康心奕 Ewing Kang									*
*	Time: 		2015/10/25											*
*	Contect: 	f039281310@yahoo.com.tw								*
*	License:	GPL                   								*
*	About:															*
*                                                                   *
*	Note:															*
*																	*
*********************************************************************/ 

#define PIN_MT_L1 6   // the trigger pin
#define PIN_MT_L2 5
#define PIN_MT_R1 10
#define PIN_MT_R2 9
char cmd;
byte spd = 120;
void setup() {
    Serial.begin(9600);
    pinMode(PIN_MT_L1, OUTPUT);  
    pinMode(PIN_MT_L2, OUTPUT);  
    pinMode(PIN_MT_R1, OUTPUT);  
    pinMode(PIN_MT_R2, OUTPUT);  
    digitalWrite(PIN_MT_L1, LOW);
    digitalWrite(PIN_MT_L2, LOW);
    digitalWrite(PIN_MT_R1, LOW);
    digitalWrite(PIN_MT_R2, LOW);
}

void loop()
{
    cmd = Serial.read();
    
    switch(cmd) {
        case 'w':
            analogWrite(PIN_MT_L1, spd);
            analogWrite(PIN_MT_R1, spd);
            analogWrite(PIN_MT_L2, 0);
            analogWrite(PIN_MT_R2, 0);
            break;
        case 'a':
            analogWrite(PIN_MT_L1, 0);
            analogWrite(PIN_MT_R1, spd);
            analogWrite(PIN_MT_L2, spd);
            analogWrite(PIN_MT_R2, 0);
            break;    
        case 's':
            analogWrite(PIN_MT_L1, 0);
            analogWrite(PIN_MT_R1, 0);
            analogWrite(PIN_MT_L2, spd);
            analogWrite(PIN_MT_R2, spd);
            break;
        case 'd':
            analogWrite(PIN_MT_L1, spd);
            analogWrite(PIN_MT_R1, 0);
            analogWrite(PIN_MT_L2, 0);
            analogWrite(PIN_MT_R2, spd);
            break;
        case ' ':
            analogWrite(PIN_MT_L1, 0);
            analogWrite(PIN_MT_R1, 0);
            analogWrite(PIN_MT_L2, 0);
            analogWrite(PIN_MT_R2, 0);
            break;
        case 'r':
            if(spd <= 250) spd += 5;
            else    spd =255;
            break;
        case 'f':
            if(spd >= 5) spd -= 5;
            else    spd =0;
            break;
        default:
            break;
    }
    delay(100);
    Serial.println(spd);
}
