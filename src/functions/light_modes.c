#include "light_modes.h"

ssize_t dev_attr_write_light_mode(struct device *dev, struct device_attribute *attr, const char *buf, size_t count) {
    struct usb_interface *interface = to_usb_interface(dev->parent);
    struct usb_device *usb_dev = interface_to_usbdev(interface);

    unsigned short mode, brightness, speed;

    sscanf(buf, "%hu %hu %hu", &mode, &brightness, &speed);

    set_light_mode(usb_dev, mode, brightness, speed);

    return (ssize_t)count;
}

int set_light_mode(struct usb_device *dev, unsigned short mode, unsigned short brightness, unsigned short speed) {

    unsigned char data[] = {
    //  start, unknown, id?,  command? argument count, padding,          arg1, arg2, arg3, arg4, arg5,  arg6, padding
        0x02,  0xf3,    0x46, 0x04,    0x02,           0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00,
        0x02,  0xf3,    0x49, 0x04,    0x06,           0x00, 0x00, 0x00, 0x9c, 0x82, 0xcd, 0x01, speed, 0x08, 0x00, 0x00,
        0x02,  0xf3,    0x4f, 0x04,    0x01,           0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00,
        0x02,  0xf1,    0x02, 0x04,    0x00,           0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00
    };

    return send_redragon_reports(dev, data, 16, sizeof(data)/sizeof(data[0]) / 16);
}
