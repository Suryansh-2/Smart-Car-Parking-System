 
#include <SoftwareSerial.h>
#include <Servo.h>
#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);


Servo myservo1;  // create servo object to control a servo
Servo myservo2;

SoftwareSerial nodemcu(0,1);

#define parking1_slot1_ir_s  4 // parking slot1 infrared sensor connected with pin number 4 of arduino
#define parking1_slot2_ir_s  5
#define parking1_slot3_ir_s  6

#define parking2_slot1_ir_s  7
#define parking2_slot2_ir_s  8
#define parking2_slot3_ir_s  9

#define entrance_gate 12
#define exit_gate 13

int pos1 = 90;    // variable to store the servo position(entrance gate)
int pos2 = 90;    // exit gate
int S1=0, S2=0, S3=0, S4=0, S5=0, S6=0;
int flag1 = 0, flag2 = 0;
int slot = 6;
int total;

String sensor1; 
String sensor2; 
String sensor3; 
String sensor4; 
String sensor5; 
String sensor6; 


String cdata =""; // complete data, consisting of sensors values

void setup()
{
Serial.begin(9600); 
nodemcu.begin(9600);

pinMode(parking1_slot1_ir_s, INPUT);
pinMode(parking1_slot2_ir_s, INPUT);
pinMode(parking1_slot3_ir_s, INPUT);

pinMode(parking2_slot1_ir_s, INPUT);
pinMode(parking2_slot2_ir_s, INPUT);
pinMode(parking2_slot3_ir_s, INPUT);

pinMode(entrance_gate, INPUT);
pinMode(exit_gate, INPUT);

myservo1.attach(3);  // attaches the servo on pin 9 to the servo object
myservo2.attach(11);
myservo1.write(0);

}
void Read_Sensor(){
S1=0, S2=0, S3=0, S4=0, S5=0, S6=0;

if(digitalRead(parking1_slot1_ir_s) == 0){S1=1; delay(10);}
if(digitalRead(parking1_slot2_ir_s) == 0){S2=1;delay(10);}
if(digitalRead(parking1_slot3_ir_s) == 0){S3=1;delay(10);}
if(digitalRead(parking2_slot1_ir_s) == 0){S4=1;delay(10);}
if(digitalRead(parking2_slot2_ir_s) == 0){S5=1;delay(10);}
if(digitalRead(parking2_slot3_ir_s) == 0){S6=1;delay(10);}  

slot=6-(S1+S2+S3+S4+S5+S6); 
if(slot==0)
{lcd.setCursor (0,0);
lcd.print("Sorry, No "); 
lcd.setCursor (0,1);
lcd.print("Parking Space");
  
  }
else
{lcd.setCursor (0,0);
lcd.print("   Have Slot: "); 
lcd.print(slot);
lcd.print("    ");  
}
delay(1000);
}



void loop(){
lcd.begin();
lcd.backlight();  
lcd.setCursor (0,0);
lcd.print("BVP Car Parking");
lcd.setCursor (0,1);
lcd.print("System");
delay (3000);
lcd.clear();
Read_Sensor();
lcd.clear();
lcd.setCursor (0,0);
if(S1==1){lcd.print("S1:Fill ");}
     else{lcd.print("S1:Empty");}

lcd.setCursor (9,0);
if(S2==1){lcd.print("S2:Fill ");}
     else{lcd.print("S2:Empty");}

lcd.setCursor (3,1);
if(S3==1){lcd.print("S3:Fill ");}
     else{lcd.print("S3:Empty");}
delay(1500);
lcd.setCursor (0,0);
if(S4==1){lcd.print("S4:Fill ");}
     else{lcd.print("S4:Empty");}


 lcd.setCursor (9,0);
if(S5==1){lcd.print("S5:Fill ");}
     else{lcd.print("S5:Empty");}


lcd.setCursor (3,1);
if(S6==1){lcd.print("S6:Fill ");}
     else{lcd.print("S6:Empty");}
     delay(1500);
lcd.clear();
p1slot1(); 
p1slot2();
p1slot3(); 

p2slot1();
p2slot2();
p2slot3();

gates();
//conditions();
////
//   cdata = cdata + sensor1 +"," + sensor2 + ","+ sensor3 +","+ sensor4 + "," + sensor5 + "," + sensor6 +","; // comma will be used a delimeter
//  Serial.println(cdata); 
////
//nodemcu.println(cdata);
   delay(100); // 100 milli seconds
}

 // parkng 1 slot1
void p1slot1()
{
  if( digitalRead(parking1_slot1_ir_s) == LOW) 
  {
  sensor1 = "255";
 delay(10); 
  } 
if( digitalRead(parking1_slot1_ir_s) == HIGH)
{
  sensor1 = "0";  
 delay(10);  
}

}

void p1slot2() // parking 1 slot2
{
  if( digitalRead(parking1_slot2_ir_s) == LOW) 
  {
  sensor2 = "255"; 
  delay(10); 
  }
if( digitalRead(parking1_slot2_ir_s) == HIGH)  
  {
  sensor2 = "0";  
 delay(10);
  } 
}


void p1slot3() // parking 1 slot3
{
  if( digitalRead(parking1_slot3_ir_s) == LOW) 
  {
  sensor3 = "255"; 
  delay(100); 
  }
if( digitalRead(parking1_slot3_ir_s) == HIGH)  
  {
  sensor3 = "0";  
 delay(100);
  } 
}


// now for parking 2

void p2slot1() // parking 1 slot3
{
  if( digitalRead(parking2_slot1_ir_s) == LOW) 
  {
  sensor4 = "255"; 
  delay(100); 
  }
if( digitalRead(parking2_slot1_ir_s) == HIGH)  
  {
  sensor4 = "0";  
 delay(100);
  } 
}


void p2slot2() // parking 1 slot3
{
  if( digitalRead(parking2_slot2_ir_s) == LOW) 
  {
  sensor5 = "255"; 
  delay(100); 
  }
if( digitalRead(parking2_slot2_ir_s) == HIGH)  
  {
  sensor5 = "0";  
 delay(100);
  } 
}


void p2slot3() // parking 1 slot3
{
  if( digitalRead(parking2_slot3_ir_s) == LOW) 
  {
  sensor6 = "255"; 
  delay(100); 
  }
if( digitalRead(parking2_slot3_ir_s) == HIGH)  
  {
  sensor6 = "0";  
 delay(100);
  } 
}

// for the gates

void gates()
{
  if (digitalRead(exit_gate) == LOW)
      {
        for (pos2 = 90; pos2 <= 180 ; pos2 += 1) { // goes from 0 degrees to 180 degrees
          // in steps of 1 degree
          myservo2.write(pos2);              // tell servo to go to position in variable 'pos'
          delay(15);                       // waits 15ms for the servo to reach the position
        }
          delay(1000);
        for (pos2 = 180; pos2 >= 90; pos2 -= 1) { // goes from 180 degrees to 0 degrees
          myservo2.write(pos2);              // tell servo to go to position in variable 'pos'
          delay(15);                       // waits 15ms for the servo to reach the position
        }
      }
  
  if ((S1+S2+S3+S4+S5+S6)<6&&(digitalRead(entrance_gate) == LOW))
  {
        for (pos1 = 0; pos1 <= 90 ; pos1 += 1) { // goes from 0 degrees to 180 degrees
          // in steps of 1 degree
          myservo1.write(pos1);              // tell servo to go to position in variable 'pos'
          delay(15);                       // waits 15ms for the servo to reach the position
        }
          delay(1000);
        for (pos1 = 90; pos1 >= 0; pos1 -= 1) { // goes from 180 degrees to 0 degrees
          myservo1.write(pos1);              // tell servo to go to position in variable 'pos'
          delay(15);                       // waits 15ms for the servo to reach the position
        }
    }
}
