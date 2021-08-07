#pragma once

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>

#include <linux/hid.h>
#include <linux/string.h>
#include <linux/uaccess.h>
#include <linux/usb/input.h>

#include "../report.h"

ssize_t dev_attr_write_light_mode(struct device *dev, struct device_attribute *attr, const char *buf, size_t count);

int set_light_mode(struct usb_device *dev, unsigned short mode, unsigned short brightness, unsigned short speed);