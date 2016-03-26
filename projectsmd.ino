#include "Wire.h"
#include <Servo.h>
#define DS3231_I2C_ADDRESS 0x68
Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;
 Servo myservo5; 
 int alm=17;
int bdoor=0;
int block=0;
int bcup=0;
int irdoor=A0;
int irlock=A2;
int ircup=A1;
int count=0;
int c=0;
char sms[50];
char phone[]="9447777118"; // Number to which sms is sending
int led=13;
//2345 rf
//8-12 serv0
//6,7 gprs
//clock A4,A5
//ir a0-a2
int flag2=0;
int rd1 = 2;    
int rd2 = 3;    
int rd3 = 4;  
int rd4 = 5;
int a1 = 0;
int a2 = 0;
int a3 = 0;
int a4 = 0;
int a5 = 0;
int alcount=0;
int b=0;
int d=0;
int e=0;
int sas=0;
int pos = 180;    
int i,dose11=1,dose12=2,dose13=2,dose21=2,dose22=1,dose23=1,dose31=1,dose32=1,dose33=2,flagalm=0,flagd1=0,flagd2=0,flagd3=0,flagdoor=0;
void setDS3231time(byte second, byte minute, byte hour, byte dayOfWeek, byte
dayOfMonth, byte month, byte year);
byte decToBcd(byte val)
{
  return( (val/10*16) + (val%10) );
}
byte bcdToDec(byte val)
{
  return( (val/16*10) + (val%16) );
}
void setup()
{
  Wire.begin();
  Serial.begin(9600);
  

   pinMode(irdoor, INPUT);
   pinMode(irlock, INPUT);
   pinMode(ircup, INPUT);
 pinMode(rd1, INPUT);
 pinMode(rd2, INPUT);
 pinMode(rd3, INPUT);
 pinMode(rd4, INPUT);
 pinMode(alm, OUTPUT);
  //6,7 gprs
  myservo1.attach(8);  
  myservo2.attach(9);
  myservo3.attach(10);
   myservo4.attach(11);
  myservo5.attach(12);
  myservo1.write(180);
  myservo2.write(180);
  myservo3.write(180);
  myservo4.write(180);
  myservo5.write(80);
  
   setDS3231time(00,00,15,5,17,03,16);
}
void setDS3231time(byte second, byte minute, byte hour, byte dayOfWeek, byte
dayOfMonth, byte month, byte year)
{
 
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set next input to start at the seconds register
  Wire.write(decToBcd(second)); // set seconds
  Wire.write(decToBcd(minute)); // set minutes
  Wire.write(decToBcd(hour)); // set hours
  Wire.write(decToBcd(dayOfWeek)); // set day of week (1=Sunday, 7=Saturday)
  Wire.write(decToBcd(dayOfMonth)); // set date (1 to 31)
  Wire.write(decToBcd(month)); // set month
  Wire.write(decToBcd(year)); // set year (0 to 99)
  Wire.endTransmission();
}
void readDS3231time(byte *second,
byte *minute,
byte *hour,
byte *dayOfWeek,
byte *dayOfMonth,
byte *month,
byte *year)
{
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set DS3231 register pointer to 00h
  Wire.endTransmission();
  Wire.requestFrom(DS3231_I2C_ADDRESS, 7);
  // request seven bytes of data from DS3231 starting from register 00h
  *second = bcdToDec(Wire.read() & 0x7f);
  *minute = bcdToDec(Wire.read());
  *hour = bcdToDec(Wire.read() & 0x3f);
  *dayOfWeek = bcdToDec(Wire.read());
  *dayOfMonth = bcdToDec(Wire.read());
  *month = bcdToDec(Wire.read());
  *year = bcdToDec(Wire.read());
}
void displayTime()
{
  byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
  int i;
  // retrieve data from DS3231
  readDS3231time(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month,
  &year);
  // send it to the serial monitor
  Serial.print(hour, DEC);
  // convert the byte variable to a decimal number when displayed
  Serial.print(":");
  if (minute<10)
  {
    Serial.print("0");
  }
  Serial.print(minute, DEC);
  Serial.print(":");
  if (second<10)
  {
    Serial.print("0");
  }
  Serial.print(second, DEC);
  Serial.print(" ");
  Serial.print(dayOfMonth, DEC);
  Serial.print("/");
  Serial.print(month, DEC);
  Serial.print("/");
  Serial.print(year, DEC);
   Serial.print(" Day of week: ");
  switch(dayOfWeek){
  case 1:
    Serial.println("Sunday");
    break;
  case 2:
    Serial.println("Monday");
    break;
  case 3:
    Serial.println("Tuesday");
    break;
  case 4:
    Serial.println("Wednesday");
    break;
  case 5:
    Serial.println("Thursday");
    break;
  case 6:
    Serial.println("Friday");
    break;
  case 7:
    Serial.println("Saturday");
    break;
  }

    if(hour==15&&minute==01 && flagd1==0)//morning slot
    {
      flagalm=1;
      flagd1=1;
      flagd3=0;
      
      for(i=0;i<dose11;i++)//frst cartridge
      {
        for (pos = 180; pos >= 135; pos -= 1)
        { 
           // in steps of 1 degree
           myservo1.write(pos);             
            delay(50);                      

         }
        for (pos = 135; pos <= 180; pos += 1) 
        { 
          myservo1.write(pos);              
          delay(50);                       
         }
         
      }

      for(i=0;i<dose21;i++)//second cartridge
      {
        for (pos = 180; pos >= 135; pos -= 1)
        { 
           // in steps of 1 degree
           myservo2.write(pos);             
            delay(50);                      

         }
        for (pos = 135; pos <= 180; pos += 1) 
        { 
          myservo2.write(pos);              
          delay(50);                       
         }
      }

      for(i=0;i<dose31;i++)//third cartridge
      {
        for (pos = 180; pos >= 135; pos -= 1)
        { 
           // in steps of 1 degree
           myservo3.write(pos);             
            delay(50);                      

         }
        for (pos = 135; pos <= 180; pos += 1) 
        { 
          myservo3.write(pos);              
          delay(50);                       
         }
      }
      
    }

if(hour==13&&minute==25&&flagd2==0)//afternoon slot
    {
      
      flagalm=1;
      flagd2=1;
      flagd1=0;
      for(i=0;i<dose12;i++)//frst cartridge
      {
        for (pos = 180; pos >= 135; pos -= 1)
        { 
           // in steps of 1 degree
           myservo1.write(pos);             
            delay(50);                      

         }
        for (pos = 135; pos <= 180; pos += 1) 
        { 
          myservo1.write(pos);              
          delay(50);                       
         }
      }

      for(i=0;i<dose22;i++)//second cartridge
      {
        for (pos = 180; pos >= 135; pos -= 1)
        { 
           // in steps of 1 degree
           myservo2.write(pos);             
            delay(50);                      

         }
        for (pos = 135; pos <= 180; pos += 1) 
        { 
          myservo2.write(pos);              
          delay(50);                       
         }
      }

      for(i=0;i<dose32;i++)//third cartridge
      {
        for (pos = 180; pos >= 135; pos -= 1)
        { 
           // in steps of 1 degree
           myservo3.write(pos);             
            delay(50);                      

         }
        for (pos = 135; pos <= 180; pos += 1) 
        { 
          myservo3.write(pos);              
          delay(50);                       
         }
      }
      
    }


   if(hour==20&&minute==25&&flagd3==0)//evening slot
    {
      flagalm=1;
      flagd3=1;
      flagd2=0;
      for(i=0;i<dose13;i++)//frst cartridge
      {
        for (pos = 180; pos >= 135; pos -= 1)
        { 
           // in steps of 1 degree
           myservo1.write(pos);             
            delay(50);                      

         }
        for (pos = 135; pos <= 180; pos += 1) 
        { 
          myservo1.write(pos);              
          delay(50);                       
         }
      }

      for(i=0;i<dose23;i++)//second cartridge
      {
        for (pos = 180; pos >= 135; pos -= 1)
        { 
           // in steps of 1 degree
           myservo2.write(pos);             
            delay(50);                      

         }
        for (pos = 135; pos <= 180; pos += 1) 
        { 
          myservo2.write(pos);              
          delay(50);                       
         }
      }

      for(i=0;i<dose33;i++)//third cartridge
      {
        for (pos = 180; pos >= 135; pos -= 1)
        { 
           // in steps of 1 degree
           myservo3.write(pos);             
            delay(50);                      

         }
        for (pos = 135; pos <= 180; pos += 1) 
        { 
          myservo3.write(pos);              
          delay(50);                       
         }
      }
      
    }
    alcount=0;
    if(flagalm==1)
    {
      
    while(alcount!=20)
    {
       a1 = digitalRead(rd1);
a2 = digitalRead(rd2);
a3 = digitalRead(rd3);
a4 = digitalRead(rd4);


bdoor=analogRead(irdoor);
block=analogRead(irlock);
bcup=analogRead(ircup);
if(bdoor>400)
 b=1;
 if (b==1 )
{

  
 if (a1==1 &&a2==1&&a3==0&&a4==0 )
  { 
    myservo4.write(80); 
  Serial.println("switch");
  b=0;
  

  
}
}
      bcup=analogRead(ircup);
      if(bcup>300&&d==0)
  {Serial.println("in");
  d=2;
  }
  if(bcup<300 && d==2)
  {Serial.println("in1");
     
  d=3;}
  if(bcup>300 && d==3)
  { 
 Serial.println("in2");
 delay(2000);
  myservo4.write(180); 
  
  break;
}

      
       
       else
       {
        digitalWrite(alm,HIGH);
        delay(1000);
        digitalWrite(alm,LOW);
        delay(1000);
        alcount++;
       }
    }
    } 
}

void loop()
{
  displayTime();
   a1 = digitalRead(rd1);
a2 = digitalRead(rd2);
a3 = digitalRead(rd3);
a4 = digitalRead(rd4);


bdoor=analogRead(irdoor);
block=analogRead(irlock);
bcup=analogRead(ircup);
if(bdoor>400)
 b=1;
 if (b==1 )
{

  
 if (a1==1 &&a2==1&&a3==0&&a4==0 )
  { 
    myservo4.write(90); 
  Serial.println("switch");
  b=0;
 d=0;
  while(b==0)
  {
    bcup=analogRead(ircup);
    Serial.println(bcup);
  if(bcup>300&&d==0)
  {Serial.println("in");
  d=2;
  }
  if(bcup<300 && d==2)
  {Serial.println("in1");
     
  d=3;}
  if(bcup>300 && d==3)
  { 
 Serial.println("in2");
 delay(2000);
  myservo4.write(180); 
  
  b=1;
}

  }      
  
  Serial.println("in2");
  delay(2000);

}
}
   if(block>300)
   {e=1;
   d=1;}
   while(e==1)
   {   block=analogRead(irlock);
   a1 = digitalRead(rd1);
a2 = digitalRead(rd2);
a3 = digitalRead(rd3);
a4 = digitalRead(rd4);
   if(block<300&&d==1)
        d=3;
   if (a1==1 &&a2==1&&a3==0&&a4==1&&d==3  )
   {myservo5.write(180);
   d=0; 
   }
   if(block>300 && d==0)
    { delay(1000);
    myservo5.write(90);
   d=1;
   e=0;
   delay(1000);
    }
   }
   if (a1==1 &&a2==0&&a3==1&&a4==0 && sas==0 )
   {
    Serial.println("first time");
    while(1){
   if(a1==0 &&a2==0&&a3==1&&a4==0)
 
   {sas=1;
   break;
   }
   else  if(a1==1 &&a2==1&&a3==0&&a4==0)
 
   {sas=1;
   break;
   }
   else
   { 
    Serial.println("seco time");
    a1 = digitalRead(rd1);
a2 = digitalRead(rd2);
a3 = digitalRead(rd3);
a4 = digitalRead(rd4);
 if (a1==1 &&a2==0&&a3==1&&a4==0 &&c==0 )
 {
  c=1;
  flag2=1;
  Serial.println("firime");
  count++;
 }
  if (a1==0&&a2==0&&a3==0&&a4==0  )
 c=0;
   }
    }
}
   
if(a1==0 &&a2==0&&a3==1&&a4==0&&flag2==1){
flag2=0;
c=count*6;
String smss="heart rate =" + String(c) ;
smss.toCharArray(sms,50);
Serial.print("heart rate=");
Serial.print(c);
if(c>80)
{digitalWrite(13, HIGH);   // set the LED on
  delay(1000);              // wait for a second
  digitalWrite(13, LOW);    // set the LED off
  delay(1000);              // wait for a second
  
  Serial.println("AT+CMGF=1");
  delay(700);
  Serial.print("AT+CMGS=\"");
  Serial.print(phone);
  Serial.println("\"");
  delay(700);
  Serial.println(sms);  //message
  delay(700);
  Serial.write(26);
  delay(700);
  delay(5000);
}
if(c<60)
{digitalWrite(13, HIGH);   // set the LED on
  delay(1000);              // wait for a second
  digitalWrite(13, LOW);    // set the LED off
  delay(1000);              // wait for a second
  
  Serial.println("AT+CMGF=1");
  delay(700);
  Serial.print("AT+CMGS=\"");
  Serial.print(phone);
  Serial.println("\"");
  delay(700);
  Serial.println(sms);  //message
  delay(700);
  Serial.write(26);
  delay(700);
  delay(5000);// waits 15ms for the servo to reach the position
                    
}
count=0;
sas=0;


}
count=0;
sas=0;
   }   
