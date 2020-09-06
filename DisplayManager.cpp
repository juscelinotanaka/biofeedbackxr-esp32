//
// Created by Juscelino Tanaka on 06/09/20.
//

#include "DisplayManager.h"

void DisplayManager::init() {
    tft.init();
    tft.setRotation(3);
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
}

void DisplayManager::initialMessage() {
    tft.setTextDatum(TC_DATUM);
    tft.setTextColor(TFT_WHITE);
    tft.drawString("BioFeedback XR", w / 2, 2 , 4);
    delay(500);
    fillScreen();
}

void DisplayManager::setTime(unsigned long i)
{
    currentTime = i;
}

void DisplayManager::printPage() {
    // Set "cursor" at top left corner of display (0,0) and select font 2
    // (cursor will move to next line automatically during printing with 'tft.println'
    //  or stay on the line is there is room for the text with tft.print)
    tft.setCursor(0, 0, 2);

    // Set the font colour to be white with a black background
    tft.setTextColor(TFT_WHITE, TFT_BLACK);

    // Set text size multiplier to 1
    tft.setTextSize(2);

    // We can now plot text on screen using the "print" class
    tft.println("BioFeedback XR");
    // reset text size to 1
    tft.setTextSize(1);
    tft.println();

    // Set the font colour to be red with black background,
    tft.setTextColor(TFT_RED, TFT_BLACK);
    // Set to font 4
    tft.setTextFont(4);
    tft.print("BPM: ");
    tft.println((long)3735928559, HEX); // Should print DEADBEEF

    // Set the font colour to be yellow with no background
    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    // set to font 7
    tft.setTextFont(2);
    tft.print("Value: ");
    tft.println(currentTime);

    // Set the font colour to be green with black background, set to font 2
    tft.setTextColor(TFT_GREEN,TFT_BLACK);
    tft.setTextFont(2);
    tft.print("Time: ");
    tft.print(hh);
    tft.print(":");
    tft.println(mm);

    // Test some print formatting functions
    float fnumber = 123.45;
    // Set the font colour to be blue with no background, set to font 2
    tft.setTextColor(TFT_BLUE);    tft.setTextFont(2);
//    tft.print("Float = "); tft.println(fnumber);           // Print floating point number
//    tft.print("Binary = "); tft.println((int)fnumber, BIN); // Print as integer value in binary

    tft.setCursor(w - 100, h - 18, 2);
    // Set the font colour to be white with a black background
    tft.setTextColor(TFT_WHITE, TFT_BLACK);

    // Set text size multiplier to 1
    tft.setTextSize(1);

    tft.setTextDatum(BR_DATUM);
    tft.drawString(buildString, w - 6, h, 2);
}

void DisplayManager::fillScreen() {
    // Fill screen with grey so we can see the effect of printing with and without
    // a background colour defined
    tft.fillScreen(TFT_BLACK);

}
