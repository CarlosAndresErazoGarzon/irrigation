/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#line 1 "d:/Proyect_final/Particle/irrigation/src/irrigation.ino"
/*
 * Project irrigation
 * Description:
 * Author:
 * Date:
 */


#include "Adafruit_DHT.h"
#include "GA1A12S202.h"
#include "Ubidots.h"
#include "Particle.h"

void setup();
void loop();
void upload_data(const char *event, const char *data);
int alive(String extra);
void start_watering();
int update_wTime(String extra);
#line 14 "d:/Proyect_final/Particle/irrigation/src/irrigation.ino"
#define DEVICE "SYS01_1"

//Defining DHT sensors on D8 and D7
#define DHT_TYPE22 DHT22
#define DHT_TYPE11 DHT11		
#define DHT_8PIN 8
#define DHT_7PIN 7

DHT dht_1(DHT_8PIN, DHT_TYPE22);
DHT dht_2(DHT_7PIN, DHT_TYPE11);

//Defining GA1A12S202 sensor on A5
#define GAA5 A5

GA1A12S202 lux_1(GAA5);

//Defining YL100 sensor on A4-D6
#define HYGRO_D5 D6
#define HYGRO_A1 A4

//Defininf a function to coordinate the watering
bool success_alive = Particle.function("alive", alive);
bool success_update_wTime = Particle.function("update_wTime", update_wTime);

//Defining Relay module on D5
#define RELAYPIN D5

//Defining water time
int wTime = 2000;

void setup() {

  dht_1.begin();
  dht_2.begin();

  pinMode(HYGRO_D5, INPUT_PULLDOWN);
  
  Particle.subscribe("upload_data", upload_data);

  pinMode(RELAYPIN, OUTPUT);
  digitalWrite(RELAYPIN, HIGH);

  Particle.variable("wTime", &wTime, INT);
}


void loop() {
  delay(3000);
}

void upload_data(const char *event, const char *data) {
  char buf[622];
  memset(buf, 0, sizeof(buf));
  JSONBufferWriter writer(buf, sizeof(buf) - 1);

  writer.beginObject();
    writer.name("device").value(DEVICE);
    writer.name("temp_01").beginArray();  
      for(int i=0; i<10; i++){
        float aux = dht_1.getTempCelcius();
        if(!isnan(aux)){
          writer.value(aux);
        }
        else{
          i--;
          delay(1000);
        }
      }  
    writer.endArray();
    
    writer.name("temp_02").beginArray();
      for(int i=0; i<10; i++){
        float aux = dht_2.getTempCelcius();
        if(!isnan(aux)){
          writer.value(aux);
        }
        else{
          i--;
          delay(1000);
        }
      }     
    writer.endArray();

    writer.name("hum_01").beginArray();     
      for(int i=0; i<10; i++){
        float aux = dht_1.getHumidity();
        if(!isnan(aux)){
          writer.value(aux);
        }
        else{
          i--;
          delay(1000);
        }
      }
    writer.endArray();

    writer.name("hum_02").beginArray();
      for(int i=0; i<10; i++){
        float aux = dht_2.getHumidity();
        if(!isnan(aux)){
          writer.value(aux);
        }
        else{
          i--;
          delay(1000);
        }
      }      
    writer.endArray();

    writer.name("hygro_01").beginArray();
      for(int i=0; i<10; i++){
        int aux = analogRead(HYGRO_A1);
        if(!isnan(aux)){
          writer.value(aux);
        }
        else{
          i--;
          delay(1000);
        }
      }     
    writer.endArray();
    
    writer.name("lux_01").beginArray();
      for(int i=0; i<10; i++){
        float aux = lux_1.getLux(true);
        if(!isnan(aux)){
          writer.value(aux);
        }
        else{
          i--;
          delay(1000);
        }
      }         
    writer.endArray();
      
  writer.endObject();

  Particle.publish("irrigation-system", String(buf));
}

int alive(String extra) {
  start_watering();
  return 200;
}

void start_watering(){
  int deviceId = Particle.deviceID().toInt();
  Particle.publish("Device", String(deviceId));

  digitalWrite(RELAYPIN, LOW);
  delay(wTime);
  digitalWrite(RELAYPIN, HIGH);
}

int update_wTime(String extra){
  wTime = atoi(extra);
  return 200;
}