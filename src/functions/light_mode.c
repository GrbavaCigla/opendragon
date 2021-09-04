#include "light_mode.h"

ssize_t dev_attr_write_light_mode(struct device *dev, struct device_attribute *attr, const char *buf, size_t count) {
    struct usb_interface *interface = to_usb_interface(dev->parent);
    struct usb_device *usb_dev = interface_to_usbdev(interface);
    int res;

    unsigned short mode = DEFAULT_MODE;
    unsigned short brightness = DEFAULT_BRIGHTNESS;
    unsigned short speed = DEFAULT_SPEED;
    rgb_t color = {
        .r = DEFAULT_RED,
        .g = DEFAULT_GREEN,
        .b = DEFAULT_BLUE,
    };

    res = sscanf(buf, "%hu %hhu %hhu %hhu %hu %hu", &mode, &color.r, &color.g, &color.b, &brightness, &speed);
    if (res < 6) {
        printk(KERN_INFO "opendragon: Only %d arguments valid, using default values", res);
    }

    res = set_light_mode(usb_dev, mode, color, brightness, speed);
    printk(KERN_INFO "opendragon: Setting light mode returned status code %d", res);

    return (ssize_t)count;
}

int set_light_mode(struct usb_device *dev, light_mode_e mode, rgb_t color, unsigned short brightness, unsigned short speed) {
    unsigned char lmode, umode;

    switch (dev->descriptor.idProduct) {
    case REDRAGON_M607_PRODUCT_ID: {
        unsigned char lmodes[] = {0x01, 0x01, 0x01, 0x02, 0x06, 0x07, 0x01, 0x00};
        unsigned char umodes[] = {0x04, 0x08, 0x02, 0x00, 0x00, 0x00, 0x10, 0x00};

        lmode = lmodes[mode];
        umode = umodes[mode];
    }

    break;
    case REDRAGON_M909_PRODUCT_ID: {
        unsigned char lmodes[] = {0x02, 0x03, 0x01, 0x05, 0xff, 0xff, 0x04, 0x00};

        lmode = lmodes[mode];
    }
        if (mode == LIGHT_MODE_GO_WITHOUT_TRACE || mode == LIGHT_MODE_REACTIVE) {
            printk(KERN_ERR "opendragon: M909 doesn't support modes 4 \"Go without trace\" and 5 \"Reactive\"");
            return -EINVAL;
        }
        umode = 0x01;
        break;
    }

    // clang-format off
    unsigned char data[] = {
    //  start, unknown, id?,  unknown, arg count, padding,          arg1,       arg2,       arg3,    arg4,  arg5,  arg6,  padding
        0x02,  0xf3,    0x46, 0x01,    0x02,      0x00, 0x00, 0x00, 0x00,       0x00,       0x00,    0x00,  0x00,  0x00,  0x00, 0x00,
        0x02,  0xf3,    0x49, 0x01,    0x06,      0x00, 0x00, 0x00, color.r,    color.g,    color.b, lmode, speed, umode, 0x00, 0x00,
        0x02,  0xf3,    0x4f, 0x01,    0x01,      0x00, 0x00, 0x00, brightness, 0x00,       0x00,    0x00,  0x00,  0x00,  0x00, 0x00,
        0x02,  0xf1,    0x02, 0x01,    0x00,      0x00, 0x00, 0x00, 0x00,       0x00,       0x00,    0x00,  0x00,  0x00,  0x00, 0x00
    };
    // clang-format on

    return send_redragon_reports(dev, data, DATA_LENGTH, sizeof(data) / sizeof(data[0]) / DATA_LENGTH);
}
