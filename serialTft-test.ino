#include <SoftwareSerial.h>         // Include the SoftwareSerial Library 

SoftwareSerial mySerial(2, 3);   // RX, TX ( Creates a new SoftwareSerial object )
int posX,posY,posZ = 0;// touch x,y variable
int tftH = 480,tftW = 320;
int Xtext = tftH * 3 / 4;
String data , cmd ;
int Orientation = 0;
const int TS_LEFT=893,TS_RT=175,TS_TOP=933,TS_BOT=176;

int lastState = 0;

void setup()
{
  Serial.begin(9600);
  Serial.println("reset"); 
  Serial.println("setRotation,"+String(Orientation));
  Serial.println("fillScreen,6");
  Serial.println("fillRoundRect,20,30,100,100,20,2");      
  Serial.println("setTextColor,7,0");
  Serial.println("setTextSize,2");              
}

void loop()
{ 
  Serial.println("getTouch,0");
  if(lastState == 1){
    Serial.println("fillRoundRect,100,100,100,100,20,4");
  }else{
    Serial.println("fillRoundRect,100,100,100,100,20,0");
  }
  //Serial.println("getSize,0");
  if(Serial.available() > 0)
  {
    data = Serial.readStringUntil('\n');
    cmd = getValue(data, ',', 0);
    Serial.println("cmd : = "+data);
    if(cmd == "touchData"){
      int x = getValue(data, ',', 1).toInt();
      int y = getValue(data, ',', 2).toInt();
      int z = getValue(data, ',', 3).toInt();
      Serial.println("x:"+String(x)+" y:"+String(y)+" z:"+String(z));
      if(z > 100 && z < 1000){
        posZ = z;

        switch (Orientation) {
            case 0:
                posX = map(x, TS_LEFT, TS_RT, 0, tftW);
                posY = map(y, TS_TOP, TS_BOT, 0, tftH);
                break;
            case 1:
                posX = map(y, TS_TOP, TS_BOT, 0, tftW);
                posY = map(x, TS_RT, TS_LEFT, 0, tftH);
                break;
            case 2:
                posX = map(x, TS_RT, TS_LEFT, 0, tftW);
                posY = map(y, TS_BOT, TS_TOP, 0, tftH);
                break;
            case 3:
                posX = map(y, TS_BOT, TS_TOP, 0, tftW);
                posY = map(x, TS_LEFT, TS_RT, 0, tftH);
                break;
        }

        if(posX < 200 && posX > 100 && posY > 100 && posY < 200){
          if(lastState == 0){
            digitalWrite(5,HIGH);
            lastState = 1; 
          }else{
            digitalWrite(5,LOW);
            lastState = 0;
          }
        }
      } else {
        posZ = 0;
      }
    }

//    if(cmd == "tftSize"){
//      int h = getValue(data, ',', 1).toInt();
//      int d = getValue(data, ',', 2).toInt();
//      tftH = h;
//      Xtext = tftH * 3 / 4;
//      tftW = d;
//    }
  }
  Serial.println("setCursor,0,"+String(Xtext));
  Serial.println("print,x=" + String(posX) + " y=" + String(posY) + " z=" + String(posZ) + "  ");
}

String getValue(String data, char separator, int index){
  int found = 0;                                        
  int strIndex[] = {0, -1  };                               
  int maxIndex = data.length()-1;                             
  for(int i=0; i<=maxIndex && found<=index; i++){            
  if(data.charAt(i)==separator || i==maxIndex){              
  found++;                                                   
  strIndex[0] = strIndex[1]+1;                              
  strIndex[1] = (i == maxIndex) ? i+1 : i;                   
  }
 }
  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";  
}
