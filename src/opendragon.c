#include "opendragon.h"
#include "functions/light_mode.h"
#include "functions/profile.h"

MODULE_AUTHOR("Aleksa Ognjanovic <alexa.ognjanovic@protonmail.com>");
MODULE_DESCRIPTION("Open Redragon drivers for Linux. Currently only supporting some mice.");
MODULE_LICENSE("GPL");

DEVICE_ATTR(light_mode, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP, NULL, dev_attr_write_light_mode);
DEVICE_ATTR(profile, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP, NULL, dev_attr_write_profile);

static int redragon_probe(struct hid_device *hdev,
                          const struct hid_device_id *id) {
    struct usb_interface *interface = to_usb_interface(hdev->dev.parent);
    int ret;

    printk(KERN_INFO "opendragon: Module probed");

    // if (interface->cur_altsetting->desc.bInterfaceProtocol == 0) {
    // }
    device_create_file(&hdev->dev, &dev_attr_light_mode);
    device_create_file(&hdev->dev, &dev_attr_profile);

    ret = hid_parse(hdev);
    if (ret) {
        printk(KERN_ERR "opendragon: Failed to parse HID device");
        return ret;
    }

    ret = hid_hw_start(hdev, HID_CONNECT_DEFAULT);
    if (ret) {
        printk(KERN_ERR "opendragon: Failed to start HID device");
        return ret;
    }

    return ret;
}

static void redragon_disconnect(struct hid_device *hdev) {
    printk(KERN_INFO "opendragon: Module disconnected");

    device_remove_file(&hdev->dev, &dev_attr_light_mode);
    device_remove_file(&hdev->dev, &dev_attr_profile);

    hid_hw_stop(hdev);
}

static struct hid_device_id device_table[] = {
    {HID_USB_DEVICE(REDRAGON_VENDOR_ID, REDRAGON_M607_PRODUCT_ID)},
    {HID_USB_DEVICE(REDRAGON_VENDOR_ID, REDRAGON_M909_PRODUCT_ID)},
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