#include "report.h"

int send_redragon_report(struct usb_device *dev, unsigned char *sdata, unsigned short slength) {
    const unsigned char endpoint = 0x00;
    const unsigned char request = HID_REQ_SET_REPORT;
    const unsigned char requesttype = USB_TYPE_CLASS | USB_RECIP_INTERFACE | USB_DIR_OUT; // Host-to-device 0x00, type class 0x20, recipient interface 0x01 -> 0x21
    const unsigned short value = 0x0302;
    const unsigned short index = 0x02;
    const int timeout = USB_CTRL_SET_TIMEOUT;

    int ret = usb_control_msg_send(dev, endpoint, request, requesttype, value, index, sdata, slength, timeout, GFP_KERNEL);

    return ret;
}

int send_redragon_reports(struct usb_device *dev, unsigned char *sdata, unsigned short length , unsigned short count) {
    int i, ret = 0;

    for(i = 0; i < count; i++) {
        unsigned char temp[length];
        int j;
        for (j = 0; j < length; j++) {
            temp[j] = sdata[i * length + j];
        }

        int tret = send_redragon_report(dev, temp, length);
        if (tret < 0) ret = tret; 
    }

    return ret;
}