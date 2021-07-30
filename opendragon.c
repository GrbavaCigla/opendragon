#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>

#include <linux/hid.h>
#include <linux/usb/input.h>

#include "opendragon.h"

MODULE_AUTHOR("Aleksa Ognjanovic <alexa.ognjanovic@protonmail.com>");
MODULE_DESCRIPTION("Driver for Redragon mouses (currently only M607)");
MODULE_LICENSE("GPL");

static int redragon_probe(struct hid_device *hdev,
                          const struct hid_device_id *id) {
    printk(KERN_INFO "opendragon: New device: %s  -  %s\n", hdev->name, hdev->phys);

    return 0;
}

static void redragon_disconnect(struct hid_device *hdev) {}

static int redragon_raw_event(struct hid_device *hdev,
                              struct hid_report *report,
                              unsigned char *data,
                              int size) {
    return 0;
}

static struct hid_device_id device_table[] = {
    {HID_USB_DEVICE(REDRAGON_M607_VENDOR_ID, REDRAGON_M607_PRODUCT_ID)},
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