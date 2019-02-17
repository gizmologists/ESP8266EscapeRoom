#ifndef __ESP8266EscapeRoom_H__
#define __ESP8266EscapeRoom_H__

#include "Arduino.h"
#include "ESP8266.h"
#include <SoftwareSerial.h>

class ESP8266EscapeRoom {
  public:
    ESP8266EscapeRoom(int rx, int tx);

  private:
    ESP8266 wifi;
};
#endif
