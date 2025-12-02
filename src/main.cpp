#include <Arduino.h>
#include <M5_PbHub.h>
#include <MicroOscSlip.h>
#include <FastLED.h>
#include <VL53L0X.h>

M5_PbHub myPbHub;

VL53L0X  tof;
#define channelAngle1 0
#define channelAngle2 1
#define channelAngle3 2
#define channelAngle4 3
#define channelAngle5 4
#define channelAngle6 5
#define lumiere 27

CRGB pixel;
unsigned long monChronoDepart;

MicroOscSlip<128> osc(&Serial);

void setup() {
  Serial.begin(115200);
  Wire.begin();
  myPbHub.begin();
  tof.init();

  FastLED.addLeds<WS2812, lumiere, GRB>(&pixel, 1);

  pixel = CRGB(255,0,0);
  FastLED.show();
  delay(1000);
  pixel = CRGB(255,255,0);
  FastLED.show();
  delay(1000);
  pixel = CRGB(0,255,0);
  FastLED.show();
  delay(1000);
  pixel = CRGB(0,0,0);
  FastLED.show();
}

void loop() {
  if ( millis() - monChronoDepart >= 20 ) { 
    monChronoDepart = millis(); 

    int lectureAngle1 = myPbHub.analogRead(channelAngle1);
    int lectureAngle2 = myPbHub.analogRead(channelAngle2);
    int lectureAngle3 = myPbHub.analogRead(channelAngle3);
    int lectureAngle4 = myPbHub.analogRead(channelAngle4);
    int lectureAngle5 = myPbHub.analogRead(channelAngle5);
    int lectureAngle6 = myPbHub.analogRead(channelAngle6);
    int mesureTof = tof.readRangeSingleMillimeters();

    osc.sendInt( "/angleVolume", lectureAngle1);
    osc.sendInt( "/angleChorus" , lectureAngle2);
    osc.sendInt( "/angleReverb", lectureAngle3);
    osc.sendInt( "/anglePan" , lectureAngle4);
    osc.sendInt( "/angleEffectA", lectureAngle5);
    osc.sendInt( "/angleEffectB", lectureAngle6);
  
    osc.sendInt( "/tufVolume", mesureTof);
  }
}
