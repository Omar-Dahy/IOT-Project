#include <Arduino.h> 
#include <WiFi.h> 
#include <Firebase.h> 
#include <Firebase_ESP_Client.h> 
#include "addons/TokenHelper.h" 
#include "addons/RTDBHelper.h" 
#include <OneWire.h> 
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 23 

OneWire oneWire(ONE_WIRE_BUS); DallasTemperature sensors(&oneWire); 

#define WIFI_SSID "SSID" 
#define WIFI_PASSWORD "PASSWORD" 
#define API_KEY "API_KEY" 
#define DATABASE_URL "RTDB URL" FirebaseData fbdo;

FirebaseAuth auth;

FirebaseConfig config;

int threshold = 40;

int led_state_1 = 0;
int led_state_2 = 0;
int led_state_3 = 0;
int led_state_4 = 0;

const int Led1 = 15;
const int Led2 = 19;
const int Led3 = 21;
const int Led4 = 22;

const int Button1 = 18;
const int Button2 = 33;
const int Button3 = 12;
const int Button4 = 13;

volatile bool button1Pressed = false;
volatile bool button2Pressed = false;
volatile bool button3Pressed = false;
volatile bool button4Pressed = false;

void IRAM_ATTR handleButton1(){ 
  button1Pressed = true;
}

void IRAM_ATTR handleButton2(){ 
  button2Pressed = true; 
}

void IRAM_ATTR handleButton3(){ 
  button3Pressed = true; 
}

void IRAM_ATTR handleButton4(){ 
  button4Pressed = true; 
}

void setup(){

  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  pinMode(Led1, OUTPUT);
  pinMode(Led2, OUTPUT);
  pinMode(Led3, OUTPUT);
  pinMode(Led4, OUTPUT);

  pinMode(Button1, INPUT_PULLUP);
  pinMode(Button2, INPUT_PULLUP);
  pinMode(Button3, INPUT_PULLUP);
  pinMode(Button4, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(Button1), handleButton1, FALLING);
  attachInterrupt(digitalPinToInterrupt(Button2), handleButton2, FALLING);
  attachInterrupt(digitalPinToInterrupt(Button3), handleButton3, FALLING);
  attachInterrupt(digitalPinToInterrupt(Button4), handleButton4, FALLING);

  sensors.begin();

}

void loop() {
  if (button1Pressed) {
    button1Pressed = false;
    led_touch_flag_1 = !led_touch_flag_1;
    Firebase.RTDB.setString(&fbdo, "IOT_Project_01/dev1/state", led_touch_flag_1 ? "1" : "0");
    digitalWrite(Led1, led_touch_flag_1 ? HIGH : LOW);
  }
  if (button2Pressed) {
    button2Pressed = false;
    led_touch_flag_2 = !led_touch_flag_2;
    Firebase.RTDB.setString(&fbdo, "IOT_Project_01/dev2/state", led_touch_flag_2 ? "1" : "0");
    digitalWrite(Led2, led_touch_flag_2 ? HIGH : LOW);
  }
  if (button3Pressed) {
    button3Pressed = false;
    led_touch_flag_3 = !led_touch_flag_3;
    Firebase.RTDB.setString(&fbdo, "IOT_Project_01/dev3/state", led_touch_flag_3 ? "1" : "0");
    digitalWrite(Led3, led_touch_flag_3 ? HIGH : LOW);
  }
  if (button4Pressed) {
    button41Pressed = false;
    led_touch_flag_4 = !led_touch_flag_4;
    Firebase.RTDB.setString(&fbdo, "IOT_Project_01/dev4/state", led_touch_flag_4 ? "1" : "0");
    digitalWrite(Led4, led_touch_flag_4 ? HIGH : LOW);
  }

  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);
  if (tempC != DEVICE_DISCONNECTED_C) {
    char buff[10];
    snprintf(buff, sizeof(buff), "%f", tempC);
    Firebase.RTDB.setString(&fbdo, "IOT_Project_01/TempSensor/value", buff);
  }

}
