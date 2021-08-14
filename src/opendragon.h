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

#define DATA_LENGTH 16

typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} rgb_t;