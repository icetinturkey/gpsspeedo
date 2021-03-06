#include <SPI.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display(128, 64, &Wire, 4);
SoftwareSerial ss(2, 3);
#include <TinyGPS++.h>
TinyGPSPlus gps;
bool veriGeldi;
static const unsigned char PROGMEM logo_bmp[] =
{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x03, 0xff, 0xff, 0xcf, 0x03, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x7f, 0xff, 0xff, 0x8f, 0x07, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x01, 0xff, 0xff, 0xff, 0x1e, 0x0f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x07, 0xff, 0xff, 0xfe, 0x3e, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x0f, 0x00, 0x0f, 0xfe, 0x3c, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x0f, 0x00, 0x00, 0xfc, 0x7c, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x07, 0x80, 0x00, 0x38, 0x78, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x03, 0xc0, 0x00, 0x00, 0xf8, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x01, 0xe0, 0x00, 0x00, 0xf1, 0xf0, 0x00, 0x00, 0x00, 0x0f, 0xff, 0x80, 0x00, 0x00, 0x00, 
0x00, 0x00, 0xf0, 0x00, 0x01, 0xf3, 0xe0, 0x00, 0x3f, 0xff, 0xcf, 0xfe, 0x03, 0xf0, 0xfc, 0x3e, 
0x00, 0x00, 0x78, 0x00, 0x01, 0xe7, 0xc0, 0x00, 0x7f, 0xff, 0x9f, 0xfe, 0x07, 0xe1, 0xfc, 0x7e, 
0x00, 0x00, 0x3c, 0x00, 0x03, 0xef, 0x80, 0x00, 0xff, 0xff, 0xbf, 0xfc, 0x0f, 0xe1, 0xfc, 0x7e, 
0x00, 0x00, 0x1e, 0x00, 0x03, 0xdf, 0x00, 0x01, 0xff, 0xe4, 0x38, 0x00, 0x1f, 0xe3, 0xfc, 0xfe, 
0x00, 0x00, 0x0f, 0x00, 0x07, 0xfe, 0x00, 0x00, 0x03, 0xc0, 0x70, 0x00, 0x7f, 0xc3, 0xfc, 0xde, 
0x00, 0x00, 0x07, 0x80, 0x07, 0xfc, 0x7c, 0x01, 0x07, 0x80, 0xff, 0xe0, 0xfb, 0xc7, 0xbd, 0xde, 
0x00, 0x00, 0x01, 0xe0, 0x0f, 0xfe, 0x7c, 0x03, 0xe7, 0x80, 0xff, 0xc1, 0xf7, 0xc7, 0xbd, 0x9e, 
0x00, 0x00, 0x00, 0xf0, 0x0f, 0xfe, 0x3e, 0x07, 0xcf, 0x01, 0xff, 0xc3, 0xc7, 0x8f, 0x3f, 0xbe, 
0x01, 0x00, 0x00, 0x78, 0x1f, 0xff, 0x3e, 0x0f, 0x9e, 0x03, 0x80, 0x07, 0x8f, 0x8f, 0x3f, 0x3e, 
0x03, 0xc0, 0x00, 0x3c, 0x1f, 0xdf, 0x3e, 0x1f, 0x1e, 0x07, 0x80, 0x0f, 0xff, 0x9e, 0x3f, 0x3c, 
0x07, 0xf0, 0x00, 0x1e, 0x3f, 0x8f, 0x1e, 0x3e, 0x3c, 0x07, 0x00, 0x1f, 0xff, 0x1c, 0x3e, 0x3c, 
0x0f, 0xff, 0x00, 0x0e, 0x3f, 0x0f, 0x9f, 0x7c, 0x7c, 0x0f, 0xfe, 0x3f, 0xff, 0x3c, 0x3e, 0x3c, 
0x1f, 0xff, 0xfc, 0x3e, 0x7e, 0x07, 0x8f, 0x7c, 0x78, 0x1f, 0xfe, 0x78, 0x1f, 0x78, 0x3c, 0x3c, 
0x3f, 0xff, 0xff, 0xfc, 0x7c, 0x07, 0x8f, 0xf8, 0xf0, 0x1f, 0xfd, 0xf0, 0x3e, 0x78, 0x3c, 0x3c, 
0x7f, 0xff, 0xff, 0xe0, 0xf8, 0x07, 0xcf, 0xf1, 0xf0, 0x3f, 0xfb, 0xe0, 0x3e, 0xf0, 0x38, 0x7c, 
0x0f, 0xff, 0xfc, 0x00, 0xf0, 0x03, 0xc7, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.drawBitmap(0,16,logo_bmp,128,37,1);
  display.display();
  display.setTextColor(SSD1306_WHITE);
  veriGeldi=false;
  ss.begin(9600);
}

void loop() {
while (ss.available() > 0)
    if (gps.encode(ss.read()))
      displayInfo();
}

void displayInfo()
{
  display.clearDisplay();

  if (gps.time.isValid())
  {
    String saat;
    int d1 = gps.time.hour();
    int d2 = gps.time.minute();
    if(d1+3>23){
    if(d1==21)
      d1=0;
    else if(d1==22)
      d1=1;
    else
      d1=2;}else d1+=3;
    if(d1<10)
      if(d2<10)
        saat="0"+(String)d1+":0"+(String)d2;
      else
        saat="0"+(String)d1+":"+(String)d2;
    else
      if(d2<10)
        saat=(String)d1+":0"+(String)d2;
      else
        saat=(String)d1+":"+(String)d2;
    char _saatDeger[7];
    saat.toCharArray(_saatDeger, 6);
    display.setTextSize(1);
    display.setCursor(4, 0);
    display.write(_saatDeger);

    smartDelay(0);
  }
if (gps.satellites.isValid())
  {
    String uydu=(String)gps.satellites.value();
    char _uyduDeger[4];
    uydu.toCharArray(_uyduDeger,3);
    display.setTextSize(1);
  display.setCursor(85, 0);
    display.write("Uydu; ");
    display.write(_uyduDeger);
    smartDelay(0);
  }
  
  if (gps.speed.isValid())
  {
    int _hiz = (int)gps.speed.kmph();
    if(_hiz>=0)
      veriGeldi=true;
    String hiz=(String)_hiz;
    char _hizDeger[5];
    hiz.toCharArray(_hizDeger,4);
    display.setTextSize(4);
    if(_hiz<100)
      if(_hiz<10)
        display.setCursor(55, 32);
      else
        display.setCursor(43, 32);
    else
      display.setCursor(30, 32);
    display.write(_hizDeger);
    smartDelay(0);
  }

  if(veriGeldi)
    display.display();
  smartDelay(1000);
}
static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}
