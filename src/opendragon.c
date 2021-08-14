#include "opendragon.h"
#include "functions/light_modes.h"

MODULE_AUTHOR("Aleksa Ognjanovic <alexa.ognjanovic@protonmail.com>");
MODULE_DESCRIPTION("Driver for Redragon mouses (currently only M607)");
MODULE_LICENSE("GPL");

DEVICE_ATTR(light_mode, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP, NULL, dev_attr_write_light_mode);


static int redragon_probe(struct hid_device *hdev,
                          const struct hid_device_id *id) {

    device_create_file(&hdev->dev, &dev_attr_light_mode);

    return 0;
}

static void redragon_disconnect(struct hid_device *hdev) {
    device_remove_file(&hdev->dev, &dev_attr_light_mode);
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