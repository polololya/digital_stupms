#include <Adafruit_NeoPixel.h> 

//Define variables:
#define SENSOR_PIN  A4
const int LED_PIN = 6;            
const int NUMPIXELS = 75; 
const int INIT_BRIGHTNESS = 255;
int sensor_state;

//Initialize pixel strip
Adafruit_NeoPixel strip (NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

//Custom function, triggered when someone step on platform
void react(int init_brightness=INIT_BRIGHTNESS) {
  int reaction_brightness = init_brightness;
  strip.setBrightness(reaction_brightness);
  strip.fill(strip.Color(141, 90, 151), 0, NUMPIXELS);
  strip.show();
    
  while (reaction_brightness > 0){
    strip.setBrightness(reaction_brightness);
    strip.show();
    reaction_brightness -= 5;
    delay(50);
    }
}

//setup function (required for Arduino)
void setup() {
  pinMode(SENSOR_PIN, INPUT);
  strip.begin(); 
  strip.setBrightness(INIT_BRIGHTNESS);  
  strip.show();
}


//Loop function: required for Arduino, main logic defined here:
void loop(){
  strip.clear(); 
  strip.setBrightness(INIT_BRIGHTNESS);
  strip.show();
  
  int loop_brightness = INIT_BRIGHTNESS;
  sensor_state = digitalRead(SENSOR_PIN);
  if (sensor_state == 0 ) {
    strip.setPixelColor(random(NUMPIXELS),strip.Color(65, 211, 189));
    strip.show();
    while (loop_brightness > 0){
      sensor_state = digitalRead(SENSOR_PIN);
      if (sensor_state > 0){
        break;
      }
      strip.setBrightness(loop_brightness);
      strip.show();
      loop_brightness = loop_brightness - 10;
      delay(30);
      }
    if (sensor_state > 0){
        react();
      }
  }
  else { 
    react();
  }

}
