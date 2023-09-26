#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#include <Adafruit_CircuitPlayground.h>

#define LED_PIN 8
#define LED_COUNT 10

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

int LED = 13;
int state = 0;

int button = 4;

String ledVals = "";
int delim = 0;
int r,g,b;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.setTimeout(10);

  pinMode(LED, OUTPUT);
  pinMode(button, INPUT_PULLDOWN);

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(75); // Set BRIGHTNESS to about 1/5 (max = 255)
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0)
  {
    ledVals = Serial.readString();
    delim = 0;

    for(int i = 0; i < strip.numPixels(); i++)
    {
      delim = ledVals.indexOf(',');
      r = ledVals.substring(0, delim).toInt();
      ledVals = ledVals.substring(delim+1, ledVals.length());

      delim = ledVals.indexOf(',');
      b = ledVals.substring(0, delim).toInt();
      ledVals = ledVals.substring(delim+1, ledVals.length());

      delim = ledVals.indexOf(',');
      g = ledVals.substring(0, delim).toInt();
      ledVals = ledVals.substring(delim+1, ledVals.length());

      strip.setPixelColor(i, strip.Color(r,g,b));
    }
  }

  strip.show();

  if(CircuitPlayground.mic.soundPressureLevel(10) > 100)
    state = 0;
  if(digitalRead(button) == HIGH)
    state = 1;

  if(state == 0)
  {
    digitalWrite(LED, state);
  }
  else
  {
    digitalWrite(LED, HIGH);
  }
  Serial.println(state);
  
}
