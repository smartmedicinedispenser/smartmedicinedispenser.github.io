
int sensorPin = A0;    
float sensorValue = 0;  
int count=0;
int starttime = 0;
int endtime = 0;
int heartrate = 0;
boolean counted = false;
 int sw=3; 
int sww=0;
 int r1 = 4;    
int r2 = 5;     
int r3 = 6;  
int r4 = 7;
 int co=0;
void setup()
{pinMode(sensorPin, INPUT);
pinMode(sw, INPUT);
  Serial.begin(9600); 
  pinMode(r1, OUTPUT);
 pinMode(r2, OUTPUT);
 pinMode(r3, OUTPUT);
 pinMode(r4, OUTPUT);

}
 
void loop()
{ sww = digitalRead(sw); 
if(sww==1)
{
  Serial.println("switch");
  digitalWrite(r1, HIGH);
   digitalWrite(r2, HIGH);
   digitalWrite(r3, LOW);
   digitalWrite(r4, LOW);
 
}
else
{
starttime = millis();
endtime = starttime;
while ((endtime - starttime) <=10000) 
{
  sensorValue = analogRead(sensorPin);
  
  if (sensorValue >500 && counted == false)         // counting the pulse, and making sure I dont count
  {                                                                // each peak more than once
    count++;
    counted = true; 
  }
  else if (sensorValue < 102)
  {
    counted = false;
  }
  endtime = millis();
}

    heartrate = count*6;   // multiplying by six to get pulse per minute
 Serial.println(heartrate); 
for(;count>0;count--)
{ digitalWrite(r1, HIGH);
   digitalWrite(r2, LOW);
   digitalWrite(r3, HIGH);
   digitalWrite(r4, LOW);
   Serial.println("1");
   delay(100);
    digitalWrite(r1, LOW);
   digitalWrite(r2, LOW);
   digitalWrite(r3, LOW);
   digitalWrite(r4, LOW);
   delay(100);  
   Serial.println("0");                                
}
 digitalWrite(r1, LOW);
   digitalWrite(r2, LOW);
   digitalWrite(r3, HIGH);
   digitalWrite(r4, LOW);
Serial.println("2");
   heartrate=0;
  count =0;
}
}
