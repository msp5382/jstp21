#ifndef anto_h
#define anto_h

#include "Arduino.h"
#include <stdio.h>
#include <WiFi.h>
#include <HTTPClient.h>

class anto
{
  public:
    anto(String key,String thing);
    void send(String channel,float data);
  private:
    String URL;
    enum ERRC = {ERR_NOT_CONNECT="WiFi not connect",SERVER_FALSE="Server not working...",CON_ERR="Error on connection"};
};
#endif