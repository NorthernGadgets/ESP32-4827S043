#include "SDCard.h"

SDCard::SDCard(uint8_t csPin) : csPin(csPin) {}

bool SDCard::begin() {
    return SD.begin(csPin);
}

void SDCard::listFiles(const char *dirname, Arduino_RPi_DPI_RGBPanel *gfx) {
    File root = SD.open(dirname);

    if (!root) {
        Serial.println("Failed to open directory");
        return;
    }

    if (!root.isDirectory()) {
        Serial.println("Not a directory");
        return;
    }

    root.rewindDirectory();

    gfx->fillScreen(BLACK);
    gfx->setTextColor(WHITE);
    gfx->setTextSize(2);

    int y = 10; // Starting y position for the text

    while (true) {
        File entry = root.openNextFile();
        if (!entry) {
            break; // No more files
        }

        Serial.println(entry.name());
        gfx->setCursor(10, y);
        gfx->println(entry.name());

        y += 20; // Move to next line

        entry.close();
    }
}
