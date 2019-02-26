/**
 * @example TCPClientSingle.ino
 * @brief The TCPClientSingle demo of library WeeESP8266. 
 * @author Wu Pengfei<pengfei.wu@itead.cc> 
 * @date 2015.02
 * 
 * @par Copyright:
 * Copyright (c) 2015 ITEAD Intelligent Systems Co., Ltd. \n\n
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version. \n\n
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
//#include "ESP8266EscapeRoom.h"
#include "ESP8266.h"
#include <SoftwareSerial.h>


#define SSID        "wahoo"
#define PASSWORD    ""

SoftwareSerial esp(7,6);
ESP8266 wifi(esp);

void setup(void)
{
    Serial.begin(115200);
    Serial.print("setup begin\r\n");
    
    Serial.print("FW Version:");
    Serial.println(wifi.getVersion().c_str());
      
    if (wifi.setOprToStationSoftAP()) {
        Serial.print("to station + softap ok\r\n");
    } else {
        Serial.print("to station + softap err\r\n");
    }
    Serial.println("Connecting to WiFi");
    while (!wifi.joinAP(SSID, PASSWORD)) Serial.println("Retrying...");
    /*if (wifi.joinAP(SSID, PASSWORD)) {
        Serial.print("Join AP success\r\n");
        Serial.print("IP:");
        Serial.println( wifi.getLocalIP().c_str());       
    } else {
        Serial.print("Join AP failure\r\n");
    }*/
    
    if (wifi.disableMUX()) {
        Serial.print("single ok\r\n");
    } else {
        Serial.print("single err\r\n");
    }
    
    Serial.print("setup end\r\n");
}
 
void loop(void)
{
    // Replace BKS with the puzzle you want
    // BKS = Books
    // MRS = Morse code
    // TIM = Time machine
    // GRS = Gears
    Serial.println("Mark books done:");
    Serial.println(wifi.markPuzzleDone("BKS"));
    Serial.println("Books status:");
    Serial.println(wifi.getPuzzleStatus("BKS"));
    Serial.println("Mark books incomplete:");
    Serial.println(wifi.markPuzzleIncomplete("BKS"));
    Serial.println("Books status:");
    Serial.println(wifi.getPuzzleStatus("BKS"));
    delay(5000);
}
     
