#include <WiFi.h>
#include <HTTPClient.h>
#include <anto.h>

const char* ssid = "IDEALAB2.4";
const char* password =  "Idealab01";
String key = "Hh2yVDGHNIQUZwjOVvI4mRGYeBgKQTXk6cVrJayB";
String thing = "nodepico";
String channel = "input";

anto anto(key,thing,channel);

void setup() {

  Serial.begin(115200);
  delay(4000);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println("Connected to the WiFi network");

}
int a = 0;
void loop() {
 anto.send(a);
 a=a+1;
 delay(10000);
}
