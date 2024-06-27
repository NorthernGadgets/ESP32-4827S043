#include <Arduino_GFX_Library.h>
#include <SPI.h>
#include <SD.h>
#include <WiFi.h>
#include <time.h>
#include "Screen.h"
#include "SDCard.h"

int Brightness = 255; // Value between 0 - 255 

// WiFi credentials
const char* ssid = "NETWORK NAME";
const char* password = "PASSWORD";

// NTP server
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 0;
const int daylightOffset_sec = 3600;

// Initialize the display bus
Arduino_ESP32RGBPanel *bus = new Arduino_ESP32RGBPanel(
    GFX_NOT_DEFINED /* CS */, GFX_NOT_DEFINED /* SCK */, GFX_NOT_DEFINED /* SDA */,
    40 /* DE */, 41 /* VSYNC */, 39 /* HSYNC */, 42 /* PCLK */,
    45 /* R0 */, 48 /* R1 */, 47 /* R2 */, 21 /* R3 */, 14 /* R4 */,
    5 /* G0 */, 6 /* G1 */, 7 /* G2 */, 15 /* G3 */, 16 /* G4 */, 4 /* G5 */,
    8 /* B0 */, 3 /* B1 */, 46 /* B2 */, 9 /* B3 */, 1 /* B4 */
);

// Initialize the SDCard class
SDCard sdCard(10);

// Initialize the screen class
Screen screen(38, 18, &sdCard, bus);

void setup(void)
{
    Serial.begin(115200); // Start serial communication for debugging

    ledcSetup(0, 25000, 8); // channel 0, 25kHz, 8-bit resolution
    ledcAttachPin(2, 0);    // attach pin 2 to channel 0
    ledcWrite(0, Brightness); // set the brightness

    // Initialize the screen
    if (!screen.begin()) {
        Serial.println("Failed to initialize screen");
        while (1);
    }

    Serial.println("Screen initialized.");

    // List files on SD card
    sdCard.listFiles("/", screen.gfx);

    // Connect to WiFi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");

    // Init and get the time
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    printLocalTime();
}

void loop()
{
    screen.drawTouchPoint();
    delay(100); // Small delay to avoid excessive processing
}

void printLocalTime()
{
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        Serial.println("Failed to obtain time");
        return;
    }
    Serial.println(&timeinfo, "Current time: %A, %B %d %Y %H:%M:%S");
}
