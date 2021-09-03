#pragma once
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>

#include <linux/hid.h>
#include <linux/usb/input.h>
#include <linux/stat.h>

#include "report.h"

#define REDRAGON_VENDOR_ID 0x04d9
#define REDRAGON_M607_PRODUCT_ID 0xfc38
#define REDRAGON_M909_PRODUCT_ID 0xfc4c

#define DATA_LENGTH 16

// DEFAULT VALUES
#define DEFAULT_BRIGHTNESS 0x01
#define DEFAULT_SPEED 0x05
#define DEFAULT_MODE 0x00
#define DEFAULT_RED 255
#define DEFAULT_GREEN 255
#define DEFAULT_BLUE 255
#define DEFAULT_PROFILE 0x00

typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} rgb_t;

typedef enum {
    LIGHT_MODE_BREATHING,
    LIGHT_MODE_RAINBOW,
    LIGHT_MODE_FULL_LIGHTED,
    LIGHT_MODE_WAVE,
    LIGHT_MODE_GO_WITHOUT_TRACE,
    LIGHT_MODE_REACTIVE,
    LIGHT_MODE_FLASH,
    LIGHT_MODE_OFF,
} light_mode_e;

typedef struct {
    light_mode_e light_mode;
    unsigned char brightness;
    unsigned char speed;
    rgb_t color;
} redragon_drvdata_t;
