#include <Adafruit_NeoPixel.h> // подключаем библиотеку
// KY-037
const int LED_PIN = 6;             // указываем пин для подключения ленты
const int NUMPIXELS = 60;  // указываем количество светодиодов в ленте
const int INIT_BRIGHTNESS = 255;

const int SENSOR_PIN = 2;
int sensor_state = 0;

// создаем объект strip с нужными характеристиками
Adafruit_NeoPixel strip (NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
//  Serial.begin (115200);      
  pinMode(SENSOR_PIN, INPUT);
  strip.begin();                     // инициализируем ленту
  strip.setBrightness(INIT_BRIGHTNESS);  // указываем яркость светодиодов (максимум 255)    
  strip.show();
}

void react(int init_brightness=INIT_BRIGHTNESS) {
  int reaction_brightness = init_brightness;
  strip.setBrightness(reaction_brightness);
  strip.fill(strip.Color(141, 90, 151), 0, NUMPIXELS);   // включаем белый цвет на 3 светодиоде
  strip.show();   // отправляем сигнал на ленту
    
    // delay(500);
  while (reaction_brightness > 0){
    strip.setBrightness(reaction_brightness);
    strip.show();
    reaction_brightness -= 5;
    delay(50);
    sensor_state = digitalRead(SENSOR_PIN);
    // if (sensor_state == 1){
    //   break;
    // }
    }
}

void loop(){

  strip.clear(); 
  

  strip.setBrightness(INIT_BRIGHTNESS);
//  strip.fill(strip.Color(255, 255, 255), 0, 30);    // включаем белый цвет на 3 светодиоде
  strip.show();

  int loop_brightness = INIT_BRIGHTNESS;
  sensor_state = digitalRead(SENSOR_PIN);
  if (sensor_state == 0) {
    strip.setPixelColor(random(NUMPIXELS),strip.Color(65, 211, 189));
    strip.show();
    while (loop_brightness > 0){
      sensor_state = digitalRead(SENSOR_PIN);
      if (sensor_state == 1){
        react();
      }
      strip.setBrightness(loop_brightness);
      strip.show();
      loop_brightness = loop_brightness - 20;
      delay(50);
      }
  }

  if (sensor_state == 1){
    int reaction_brightness = INIT_BRIGHTNESS;
    strip.setBrightness(reaction_brightness);
    strip.fill(strip.Color(141, 90, 151), 0, NUMPIXELS);   // включаем белый цвет на 3 светодиоде
    strip.show();   // отправляем сигнал на ленту
    
    // delay(500);
    while (reaction_brightness > 0){
      strip.setBrightness(reaction_brightness);
      strip.show();
      reaction_brightness -= 5;
      delay(50);
      sensor_state = digitalRead(SENSOR_PIN);
      // if (sensor_state == 1){
      //   break;
      // }
    }
  }
}
