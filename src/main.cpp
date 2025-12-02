#include <Arduino.h>
#include <M5_PbHub.h>
#include <MicroOscSlip.h>
#include <FastLED.h>
#include <VL53L0X.h>

VL53L0X  tof1;
M5_PbHub myPbHub;
#define channelAngle 0
#define lumiere 27

CRGB pixel;

MicroOscSlip<128> monOsc(&Serial);

void setup() {
  Serial.begin(115200);
  Wire.begin();
  myPbHub.begin();
  tof1.init();
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
  int maLectureAnalogique = myPbHub.analogRead(channelAngle);
  //int mesureTof1 = tof1.readRangeSingleMillimeters();
 // int mesureTof2 = tof2.readRangeSingleMillimeters();
 int mesureTof1 = tof1.readRangeSingleMillimeters();
 // monOsc.sendInt( "/tufPitch" , mesureTof1);
 // monOsc.sendInt( "/tufVolume", mesureTof2);
  monOsc.sendInt( "/analog" , maLectureAnalogique);
  monOsc.sendInt( "/tof", mesureTof1);
  delay(20);
}
