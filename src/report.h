#pragma once

#include <linux/usb.h>
#include <uapi/linux/hid.h>
#include <uapi/linux/usb/ch9.h>

int send_redragon_report(struct usb_device *dev, unsigned char *data, unsigned short length);

int send_redragon_reports(struct usb_device *dev, unsigned char *data, unsigned short length, unsigned short count);