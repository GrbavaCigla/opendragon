#pragma once

#include <linux/usb.h>
#include <uapi/linux/hid.h>
#include <uapi/linux/usb/ch9.h>

int send_report(struct usb_device *dev, unsigned char *sdata, unsigned short slength, unsigned char *rdata);