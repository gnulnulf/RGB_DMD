// Copyright (c) 2015 Eli Curtz

#include "rgb_dmd.h"
#include "SplashScreen.h"

const PalleteInfo logoPallete = {
  "Logo",
  {
    {0x00, 0x00, 0x00},
    {0xFF, 0x00, 0x00},
    {0x00, 0xFF, 0x00},
    {0x00, 0x00, 0xFF},
    {0xFF, 0xFF, 0xFF},
    {0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00}
  }
};

const uint8_t logo4Bit[10][32] = {
  {0x11, 0x11, 0x11, 0x11, 0x00, 0x02, 0x22, 0x22, 0x22, 0x20, 0x33, 0x33, 0x33, 0x33, 0x00, 0x00, 0x04, 0x44, 0x44, 0x44, 0x00, 0x04, 0x44, 0x00, 0x00, 0x04, 0x44, 0x04, 0x44, 0x44, 0x44, 0x00},
  {0x11, 0x11, 0x11, 0x11, 0x10, 0x22, 0x22, 0x22, 0x22, 0x20, 0x33, 0x33, 0x33, 0x33, 0x30, 0x00, 0x04, 0x44, 0x44, 0x44, 0x40, 0x04, 0x44, 0x40, 0x00, 0x44, 0x44, 0x04, 0x44, 0x44, 0x44, 0x40},
  {0x11, 0x10, 0x00, 0x11, 0x10, 0x22, 0x20, 0x00, 0x00, 0x00, 0x33, 0x30, 0x00, 0x33, 0x30, 0x00, 0x04, 0x44, 0x00, 0x44, 0x44, 0x04, 0x44, 0x44, 0x04, 0x44, 0x44, 0x04, 0x44, 0x00, 0x44, 0x44},
  {0x11, 0x10, 0x00, 0x11, 0x10, 0x22, 0x20, 0x00, 0x00, 0x00, 0x33, 0x30, 0x00, 0x33, 0x30, 0x00, 0x04, 0x44, 0x00, 0x04, 0x44, 0x04, 0x44, 0x44, 0x44, 0x44, 0x44, 0x04, 0x44, 0x00, 0x04, 0x44},
  {0x11, 0x11, 0x11, 0x11, 0x00, 0x22, 0x20, 0x22, 0x22, 0x00, 0x33, 0x33, 0x33, 0x33, 0x00, 0x00, 0x04, 0x44, 0x00, 0x04, 0x44, 0x04, 0x44, 0x44, 0x44, 0x44, 0x44, 0x04, 0x44, 0x00, 0x04, 0x44},
  {0x11, 0x11, 0x11, 0x11, 0x00, 0x22, 0x20, 0x22, 0x22, 0x20, 0x33, 0x33, 0x33, 0x33, 0x00, 0x00, 0x04, 0x44, 0x00, 0x04, 0x44, 0x04, 0x44, 0x04, 0x44, 0x04, 0x44, 0x04, 0x44, 0x00, 0x04, 0x44},
  {0x11, 0x10, 0x00, 0x11, 0x10, 0x22, 0x20, 0x00, 0x22, 0x20, 0x33, 0x30, 0x00, 0x33, 0x30, 0x00, 0x04, 0x44, 0x00, 0x04, 0x44, 0x04, 0x44, 0x00, 0x40, 0x04, 0x44, 0x04, 0x44, 0x00, 0x04, 0x44},
  {0x11, 0x10, 0x00, 0x11, 0x10, 0x22, 0x20, 0x00, 0x22, 0x20, 0x33, 0x30, 0x00, 0x33, 0x30, 0x00, 0x04, 0x44, 0x00, 0x44, 0x44, 0x04, 0x44, 0x00, 0x00, 0x04, 0x44, 0x04, 0x44, 0x00, 0x44, 0x44},
  {0x11, 0x10, 0x00, 0x11, 0x10, 0x22, 0x22, 0x22, 0x22, 0x20, 0x33, 0x33, 0x33, 0x33, 0x30, 0x44, 0x04, 0x44, 0x44, 0x44, 0x40, 0x04, 0x44, 0x00, 0x00, 0x04, 0x44, 0x04, 0x44, 0x44, 0x44, 0x40},
  {0x11, 0x10, 0x00, 0x11, 0x10, 0x02, 0x22, 0x22, 0x22, 0x00, 0x33, 0x33, 0x33, 0x33, 0x00, 0x44, 0x04, 0x44, 0x44, 0x44, 0x00, 0x04, 0x44, 0x00, 0x00, 0x04, 0x44, 0x04, 0x44, 0x44, 0x44, 0x00}
};

/*
 Display board id, software version, and boot logo
*/
void showSplashScreen(bool showInfo)
{
  backgroundLayer.fillScreen(logoPallete.colors[0]);
  
  for (uint16_t y = 0; y < 10; y++) {
    rgb24* pixelPtr = backgroundLayer.backBuffer() + ((y + 6) * COL_COUNT) + 32;
    for (uint16_t x = 0; x < 32; x++) {
      *pixelPtr = logoPallete.colors[logo4Bit[y][x] >> 4]; pixelPtr++;
      *pixelPtr = logoPallete.colors[logo4Bit[y][x] & 0x0F]; pixelPtr++;
    }
  }

  if (showInfo) {
    // Need some actual font methods, but this will do for now
    backgroundLayer.setFont(font5x7);
    backgroundLayer.drawString(2, 24, logoPallete.colors[4], "ID:");
    backgroundLayer.drawString(2 + (5*3), 24, logoPallete.colors[4], idString);
    backgroundLayer.drawString(COL_COUNT - 2 - (5 * versionLength) - (5*2), 24, logoPallete.colors[4], "V:");
    backgroundLayer.drawString(COL_COUNT - 2 - (5 * versionLength), 24, logoPallete.colors[4], versionString);
  }
  
  backgroundLayer.swapBuffers();
}

