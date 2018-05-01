#include "Arduino.h"
#include "anto.h"
#include <WiFi.h>
#include <HTTPClient.h>

anto::anto(String key,String thing,String channel)
{
  URL="http://api.anto.io/channel/set/"+key+"/"+thing+"/"+channel+"/";
}
void anto::send(int data)
{
if ((WiFi.status() == WL_CONNECTED)) {

    HTTPClient http;

    http.begin(URL + String(data)); 
    int httpCode = http.GET();

    if (httpCode > 0) {

        String payload = http.getString();
        //Serial.println(httpCode);
        //Serial.println(payload);
      }

    else {
      Serial.println("Error on HTTP request");
    }

    http.end();
  }

}