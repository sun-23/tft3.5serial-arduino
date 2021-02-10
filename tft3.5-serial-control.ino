#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;       // hard-wired for UNO shields anyway.
#include <TouchScreen.h>

char *name = "Please Calibrate.";  //edit name of shield
const int XP=6,XM=A2,YP=A1,YM=7; //ID=0x9341
const int TS_LEFT=893,TS_RT=175,TS_TOP=933,TS_BOT=176; //PORTRAIT
// const int TS_LEFT=993,TS_RT=176,TS_TOP=175,TS_BOT=893; //LANDSCAPE

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
TSPoint tp;

#define MINPRESSURE 200
#define MAXPRESSURE 1000

uint16_t ID, oldcolor, currentcolor;
uint8_t Orientation = 0;    //PORTRAIT
String data,commandData,text;
uint16_t x, y, textSize;// cursor variable
int posX,posY,posZ = 0;// touch x,y variable

#define BLACK   0x0000
#define BLUE    0x00F2
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
uint16_t color = WHITE, blackColor = BLACK; // text color variable
uint16_t Color[] = {BLACK, BLUE, RED, GREEN, CYAN, MAGENTA, YELLOW, WHITE};

void setup() {
  tft.reset();
  ID = tft.readID();
  tft.begin(ID);
  Serial.begin(9600);
//  tft.setRotation(Orientation);
//  tft.fillScreen(BLACK);
//  tft.setTextSize(2);
//  tft.setCursor(0,0);
}

void loop() {
  tp = ts.getPoint();
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  if (tp.z > MINPRESSURE && tp.z < MAXPRESSURE){
    // touch
    posX = tp.x;
    posY = tp.y;
    posZ = tp.z;
//    tft.setTextColor(color, blackColor);
//    tft.setCursor(0, (tft.height() * 3) / 4);
//    tft.print("tp.x=" + String(posX) + " tp.y=" + String(posY) + "   ");
  } else {
    // not touch
    posZ = 0;
//    tft.setTextColor(color, blackColor);
//    tft.setCursor(0, (tft.height() * 3) / 4);
//    tft.print("tp.x=" + String(posX) + " tp.y=" + String(posY) + "   ");
  }
                                           
  if(Serial.available() > 0) {
    data = Serial.readStringUntil('\n');        //อ่านค่ามาเก็บที่ data
    commandData = getValue(data, ',', 0);
    //Serial.println("Data" + data);
    //Serial.println("commandData" + commandData);

    if(commandData == "getTouch"){
      Serial.println("touchData," + String(posX) + "," + String(posY) + "," + String(posZ) + ",00");
      //Serial.println("toucgData,3030,43,355");
      //tft.fillRect(30,30,20,80,4);
    }

    if(commandData == "getSize"){
      Serial.println("tftSize,"+String(tft.height())+","+String(tft.width()));
    }
    
    if(commandData == "setCursor"){
      x = getValue(data, ',', 1).toInt();
      y = getValue(data, ',', 2).toInt();
    }else if(commandData == "setTextColor"){
      color = Color[getValue(data, ',', 1).toInt()];
      blackColor = Color[getValue(data, ',', 2).toInt()];
    }else if(commandData == "setTextSize"){
      textSize = getValue(data, ',', 1).toInt();
      tft.setTextSize(textSize);
    }else if(commandData == "print"){
      text = getValue(data, ',', 1);
      tft.setCursor(x, y);
      tft.setTextColor(color, blackColor);
      tft.print(text);
    }

    if(commandData == "fillScreen"){
      int16_t t = Color[getValue(data, ',', 1).toInt()];
      tft.fillScreen(t);
    }

    if(commandData == "reset"){
      tft.reset();
      ID = tft.readID();
      tft.begin(ID);
      tft.setRotation(Orientation);
    }

    if(commandData == "setRotation"){
      Orientation = getValue(data, ',', 1).toInt();
      tft.setRotation(Orientation);
    }

    if(commandData == "drawFastVLine"){
      int16_t x = getValue(data, ',', 1).toInt();
      int16_t y = getValue(data, ',', 2).toInt();
      int16_t h = getValue(data, ',', 3).toInt();
      int16_t t = Color[getValue(data, ',', 4).toInt()];
      tft.drawFastVLine(x,y,h,t);
    }

    if(commandData == "drawFastHLine"){
      int16_t x = getValue(data, ',', 1).toInt();
      int16_t y = getValue(data, ',', 2).toInt();
      int16_t w = getValue(data, ',', 3).toInt();
      int16_t t = Color[getValue(data, ',', 4).toInt()];
      tft.drawFastHLine(x,y,w,t);
    }

    if(commandData == "drawLine"){
      int16_t xi = getValue(data, ',', 1).toInt();
      int16_t yi = getValue(data, ',', 2).toInt();
      int16_t xj = getValue(data, ',', 3).toInt();
      int16_t yj = getValue(data, ',', 4).toInt();
      int16_t t = Color[getValue(data, ',', 5).toInt()];
      tft.drawLine(xi,yi,xj,yj,t);
    }

    if(commandData == "fillRect"){
      int16_t x = getValue(data, ',', 1).toInt();
      int16_t y = getValue(data, ',', 2).toInt();
      int16_t w = getValue(data, ',', 3).toInt();
      int16_t h = getValue(data, ',', 4).toInt();
      int16_t t = Color[getValue(data, ',', 5).toInt()];
      tft.fillRect(x,y,w,h,t);
    }else if(commandData == "drawRect"){
      int16_t x = getValue(data, ',', 1).toInt();
      int16_t y = getValue(data, ',', 2).toInt();
      int16_t w = getValue(data, ',', 3).toInt();
      int16_t h = getValue(data, ',', 4).toInt();
      int16_t t = Color[getValue(data, ',', 5).toInt()];
      tft.drawRect(x,y,w,h,t);
    }else if(commandData == "fillRoundRect"){
      int16_t x = getValue(data, ',', 1).toInt();
      int16_t y = getValue(data, ',', 2).toInt();
      int16_t w = getValue(data, ',', 3).toInt();
      int16_t h = getValue(data, ',', 4).toInt();
      int16_t r = getValue(data, ',', 5).toInt();
      int16_t t = Color[getValue(data, ',', 6).toInt()];
      tft.fillRoundRect(x,y,w,h,r,t);
    }else if(commandData == "drawRoundRect"){
      int16_t x = getValue(data, ',', 1).toInt();
      int16_t y = getValue(data, ',', 2).toInt();
      int16_t w = getValue(data, ',', 3).toInt();
      int16_t h = getValue(data, ',', 4).toInt();
      int16_t r = getValue(data, ',', 5).toInt();
      int16_t t = Color[getValue(data, ',', 6).toInt()];
      tft.drawRoundRect(x,y,w,h,r,t);
    }

    if(commandData == "drawCircle"){
      int16_t x = getValue(data, ',', 1).toInt();
      int16_t y = getValue(data, ',', 2).toInt();
      int16_t r = getValue(data, ',', 3).toInt();
      int16_t t = Color[getValue(data, ',', 4).toInt()];
      tft.drawCircle(x,y,r,t);
    }else if(commandData == "fillCircle"){
      int16_t x = getValue(data, ',', 1).toInt();
      int16_t y = getValue(data, ',', 2).toInt();
      int16_t r = getValue(data, ',', 3).toInt();
      int16_t t = Color[getValue(data, ',', 4).toInt()];
      tft.fillCircle(x,y,r,t);
    }
  }
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
