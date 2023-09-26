#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#include <Adafruit_CircuitPlayground.h>

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

#define PIXELS 8
Adafruit_NeoPixel strip = Adafruit_NeoPixel(10, PIXELS, NEO_GRB + NEO_KHZ800);

int button = 4;
int cover = 8;
int LED = 13;
int sound = 0;

String stripVals = "";
int y = 1;
int color = 0;
int r,g,b;
int state = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.setTimeout(10);

  pinMode(button, INPUT_PULLDOWN);
  pinMode(LED, OUTPUT);
  
  strip.begin();
  strip.setBrightness(80);
  strip.clear();
  strip.show();

}

void loop() {
  // put your main code here, to run repeatedly:
//  while (Serial.available() > 0) {
//    // read the incoming byte:
//    state = Serial.parseInt();
//  }
//  state = digitalRead(button); 

  stripVals = "";
  if(Serial.available() > 0) {
    // read the incoming byte:
    stripVals = Serial.readString();
    y = 0;
    for(int i = 0; i < strip.numPixels(); i++)
    {
      y = stripVals.indexOf(',');
      r = stripVals.substring(0, y).toInt();
      stripVals = stripVals.substring(y+1, stripVals.length());
      y = stripVals.indexOf(',');
      g = stripVals.substring(0, y).toInt();
      stripVals = stripVals.substring(y+1, stripVals.length());
      y = stripVals.indexOf(',');
      b = stripVals.substring(0, y).toInt();
      stripVals = stripVals.substring(y+1, stripVals.length());
      
      strip.setPixelColor(i, strip.Color(r,g,b));   
    }

  }
  strip.show();
  sound = CircuitPlayground.mic.soundPressureLevel(10);
  //Serial.println(sound);
  if(sound > 100)
    state = 0;
  if(digitalRead(button) == HIGH)
    state = 1;
  
  digitalWrite(LED, state);
  Serial.println(state);

  //delay(30);
}
