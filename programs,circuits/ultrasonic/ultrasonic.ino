/********************************************************************
*	Program:	ultrasonic.ino                                     *
*	Author:		康心奕 Ewing Kang									*
*	Time: 		2015/10/25											*
*	Contect: 	f039281310@yahoo.com.tw								*
*	License:	GPL                   								*
*	About:															*
*                                                                   *
*	Note:															*
*																	*
*********************************************************************/ 

#define PIN_TRIG 2   //
#define PIN_ECHO 3

long snr_duration;
float distance;

void setup() {
    Serial.begin(9600); //pin0 pin1 are for serial 
    Serial.print("initialize the Line Dectector program");

    pinMode(PIN_TRIG, OUTPUT);
    digitalWrite(PIN_TRIG, LOW);
    pinMode(PIN_ECHO, INPUT);
}

void loop() {
    Serial.println("Sending soundwave  ;");
    digitalWrite(PIN_TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(PIN_TRIG, LOW);//叫聲納發出音波10毫秒
    
    snr_duration = pulseIn(PIN_ECHO,HIGH);          //測量(t2-t1)，pulsein偵測上升下降的時間
    Serial.print("duration in microseconds: ");     //return datatype ? 任何function 在lib 傳回 long int
    Serial.println(snr_duration);
    
    distance = (float)snr_duration * 340 / 2 / 1000000; //只在這行使snr變成float，這樣才能除
    Serial.print("distance in meters: ");
    Serial.println(distance);
    
    delay(500);                 // wait for 0.1 sec
}
