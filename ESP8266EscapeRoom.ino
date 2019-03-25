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
#include "ESP8266.h"
#include <SoftwareSerial.h>

// Connect to wahoo
#define SSID        "wahoo"
#define PASSWORD    ""

// Setup ESP
// Pin 7 is TX on adapter; 6 is RX on adapter
// Adapter takes 5V in VCC
SoftwareSerial esp(7,6);
ESP8266 wifi(esp);

void setup(void)
{
    Serial.begin(115200);
    Serial.print("setup begin\r\n");
    Serial.println("Connecting to WiFi");
    // Connect to WiFi and wait till it's connected
    while (!wifi.joinAP(SSID, PASSWORD)) Serial.println("Retrying...");
    Serial.print("setup end\r\n");
}
 
void loop(void)
{
    // Replace BKS with the puzzle you want
    // BKS = Books
    // MRS = Morse code
    // TIM = Time machine
    // GRS = Gears
    Serial.print("Mark books done: ");
    Serial.println(wifi.markPuzzleDone("BKS"));
    delay(50);
    Serial.print("Books status: ");
    Serial.println(wifi.getPuzzleStatus("BKS"));
    delay(50);
    Serial.print("Mark books incomplete: ");
    Serial.println(wifi.markPuzzleIncomplete("BKS"));
    delay(50);
    Serial.print("Books status: ");
    Serial.println(wifi.getPuzzleStatus("BKS"));
    delay(5000);

    // Reset all puzzles
    Serial.print("Resetting all: ");
    Serial.println(wifi.resetAllPuzzles());
    delay(50);
    // Check them
    Serial.print("Books status: ");
    Serial.println(wifi.getPuzzleStatus("BKS"));
    delay(50);
    Serial.print("Morse status: ");
    Serial.println(wifi.getPuzzleStatus("MRS"));
    delay(50);
    Serial.print("Time machine status: ");
    Serial.println(wifi.getPuzzleStatus("TIM"));
    delay(50);
    Serial.print("Gears status: ");
    Serial.println(wifi.getPuzzleStatus("GRS"));
    delay(5000);
}
     
