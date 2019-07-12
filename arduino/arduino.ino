#include <Servo.h>
#define TRIG 9
#define ECHO 8
#define value 100
Servo motor1;
long duration, distance;

String data;
int cnt = 0;
String inData;
String AP = "os_window";
String PASS = "a12345678";

String HOST = "192.168.137.238";
String PORT = "8000";

void left(){
  analogWrite(5,value+50);
  analogWrite(6,0);
  analogWrite(10,0);
  analogWrite(11,value+50);
  
}
void right(){
  analogWrite(5,0);
  analogWrite(6,value+50);
  analogWrite(10,value+50);
  analogWrite(11,0);
}
void front(){
  analogWrite(5,0);
  analogWrite(6,value);
  analogWrite(10,0);
  analogWrite(11,value);
}
void back(){
  analogWrite(5,value);
  analogWrite(6,0);
  analogWrite(10,value);
  analogWrite(11,0);
}
void stopgo(){
   analogWrite(5,0);
   analogWrite(6,0);
   analogWrite(10,0);
   analogWrite(11,0);
}
void feed(){
  stopgo();
  motor1.write(90);
  delay(1000);
  motor1.write(0);
}
void autogo(){
   int count = 0;
   do
   {
      digitalWrite(TRIG,LOW);
      delayMicroseconds(2);
      digitalWrite(TRIG,HIGH);
      delayMicroseconds(10);
      digitalWrite(TRIG,LOW);
      duration = pulseIn(ECHO,HIGH);
      distance = duration * 17 / 1000;
      delay(1000);
      count = random(2);
      if(count == 0){
        left();
      }
      else
        right();
   }while(distance<15);
   front();
}


void respond()
{
  delay(4000);
  if(Serial3.available())
  {
      data = Serial3.readStringUntil("\n");
      Serial.println(data);
  }
  Serial.println("next");
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial3.begin(115200);
  motor1.attach(7);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(TRIG,OUTPUT);
  pinMode(ECHO,INPUT);
  stopgo();
  Serial3.println("AT");
  respond();
  Serial3.println("AT+CWMODE=1");
  respond();
  Serial3.println("AT+CIPSTART=\"TCP\",\""+ HOST +"\","+ PORT);
  respond();
}

void loop() {
  if(Serial.available())
  {
    Serial3.write(Serial.read());
  }
  // put your main code here, to run repeatedly:
  char input[100] = {0};
  motor1.write(0);
  // put your main code here, to run repeatedly:
  while(Serial3.available()>0){
    String inputstring = Serial3.readStringUntil('\n');
    inputstring.toCharArray(input,inputstring.length()+1);
    char a = input[inputstring.length()-1];
    if(a=='w'){
      front();
    }
    else if( a == 's'){
      back();
    }
    else if( a == 'a'){
      left();
    }
    else if( a == 'd'){
      right(); 
    }
    else if( a == 'x'){
      stopgo();         
    }
    else if( a == 'o'){
      feed();
    }
    else if( a == 'g'){
      while(1)
        autogo();
    }
  }
  
}
