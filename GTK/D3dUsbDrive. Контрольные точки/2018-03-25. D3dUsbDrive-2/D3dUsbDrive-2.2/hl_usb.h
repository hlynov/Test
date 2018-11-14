#ifndef hl_usb_h__
#define hl_usb_h__

#define VID 0x0477
#define PID 0x5620
#define DEV_INTF 0    // номер интерфейса

#define USB_DEBUG_LEVEL 3

#include <libusb-1.0/libusb.h>

#define DATA_SIZE 8


#define EP_IN 0x81
#define EP_OUT 0x01

#define TIMEOUT 20000

#define ACM_CTRL_DTR   0x01
#define ACM_CTRL_RTS 0x02




struct libusb_device_descriptor desc; //description of device structure



//void interrupt_transfer_loop(libusb_device_handle *handle);
void bulk_transfer_loop(libusb_device_handle *handle);
void myTestFunc(void);
void concheck (libusb_device_handle *handle, GtkWidget *lblConnectionStatus);
void testRead (libusb_device_handle *handle);
void interrupt_transfer_loop(libusb_device_handle *handle, int rx[]);

#endif
