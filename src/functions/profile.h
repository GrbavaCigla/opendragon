#pragma once
#include "../opendragon.h"
#include "../report.h"

ssize_t dev_attr_write_profile(struct device *dev, struct device_attribute *attr, const char *buf, size_t count);

int set_profile(struct usb_device *dev, unsigned char profile_num);