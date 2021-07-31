#include "report.h"

int send_report(struct usb_device *dev, unsigned char *sdata, unsigned short slength, unsigned char *rdata) {
    const unsigned char endpoint = 0x00;
    const unsigned char request = HID_REQ_SET_REPORT;
    const unsigned char requesttype = USB_TYPE_CLASS | USB_RECIP_INTERFACE | USB_DIR_OUT; // Host-to-device 0x00, type class 0x20, recipient interface 0x01 -> 0x21
    const unsigned short value = 0x0302;
    const unsigned short index = 0x02;
    const int timeout = USB_CTRL_SET_TIMEOUT;

    printk(KERN_INFO "opendragon: Sending report\n");

    int len = usb_control_msg_send(dev, endpoint, request, requesttype, value, index, sdata, slength, timeout, GFP_KERNEL);

    printk(KERN_INFO "opendragon: Report sent\n");

    return len;
}