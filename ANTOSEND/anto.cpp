#include "Arduino.h"
#include "anto.h"
#include <WiFi.h>
#include <HTTPClient.h>

anto::anto(String key,String thing)
{
  URL="http://api.anto.io/channel/set/"+key+"/"+thing+"/";
}
void anto::send(String channel,float data)
{
if ((WiFi.status() == WL_CONNECTED)) {

    HTTPClient http;

    http.begin(URL + "channel/" + String(data)); 
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