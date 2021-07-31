#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>

#include <linux/hid.h>
#include <linux/usb/input.h>

#include "opendragon.h"
#include "report.h"

MODULE_AUTHOR("Aleksa Ognjanovic <alexa.ognjanovic@protonmail.com>");
MODULE_DESCRIPTION("Driver for Redragon mouses (currently only M607)");
MODULE_LICENSE("GPL");

static ssize_t read_test(struct device *dev, struct device_attribute *attr, char *buf) {
    return sprintf(buf, "%d\n", 0);
}

static ssize_t write_test(struct device *dev, struct device_attribute *attr, const char *buf, size_t count) {
    struct usb_interface *interface = to_usb_interface(dev->parent);
    struct usb_device *usb_dev = interface_to_usbdev(interface);

    unsigned char data[] = {0x02, 0xf1, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    int len = send_report(usb_dev, data, 16, 0);
    printk(KERN_INFO "opendragon: length: %d", len);

    return (ssize_t)count;
}

DEVICE_ATTR(test, 0664, read_test, write_test);

static int redragon_probe(struct hid_device *hdev,
                          const struct hid_device_id *id) {

    device_create_file(&hdev->dev, &dev_attr_test);

    return 0;
}

static void redragon_disconnect(struct hid_device *hdev) {
    device_remove_file(&hdev->dev, &dev_attr_test);
}

static struct hid_device_id device_table[] = {
    {HID_USB_DEVICE(REDRAGON_VENDOR_ID, REDRAGON_M607_PRODUCT_ID)},
    {},
};

MODULE_DEVICE_TABLE(hid, device_table);

static struct hid_driver redragon_driver = {
    .name = "opendragon",
    .id_table = device_table,

    .probe = redragon_probe,
    .remove = redragon_disconnect,
};

module_hid_driver(redragon_driver);