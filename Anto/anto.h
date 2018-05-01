#ifndef anto_h
#define anto_h

#include "Arduino.h"
#include <stdio.h>
#include <WiFi.h>
#include <HTTPClient.h>

class anto
{
  public:
    anto(String key,String thing,String channel);
    void send(int data);
  private:
    String URL;
};
#endif