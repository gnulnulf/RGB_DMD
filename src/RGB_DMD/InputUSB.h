// Copyright (c) 2015 Eli Curtz

#ifndef InputUSB_h
#define InputUSB_h

enum {
  CMD_ACK = 0,
  CMD_GET_VERS=1,
  CMD_GET_ID=2,
  CMD_ROW_DATA_RGB=3,
  CMD_SCREEN_DATA_RGB=4,
  CMD_ROW_DATA_8=5,
  CMD_SCREEN_DATA_8=6,
  CMD_ROW_DATA_4=7,
  CMD_SCREEN_DATA_4=8,
  CMD_PLANE_DATA=9,
  CMD_FLIP_BUFFER=10,
  CMD_SET_PALETTE=11,
  CMD_SAVE_PALETTE=12,
  CMD_ACTIVATE_PALETTE=13,
  CMD_REFRESH_RATE=14,
  CMD_SAVE_SETTINGS=15,
  CMD_RESTART=16,

  CMD_COUNT
};

#define USB_MARKER_LENGTH 4

typedef struct {
  uint8_t marker[USB_MARKER_LENGTH];
  uint8_t command;
  uint8_t argument;
  uint16_t checksum;
} USBCommandHeader;

const uint8_t usbMarker[USB_MARKER_LENGTH] = {0xBA, 0x11, 0x00, 0x03};

uint32_t usbInputIndex;

void initializeInputUSB();

bool hasInputUSB();

void configureInputUSB();

bool handleInputUSB();

#endif
