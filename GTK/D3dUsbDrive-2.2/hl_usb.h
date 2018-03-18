

#define VID 0x0477
#define PID 0x5620
#define DEV_INTF 0    // номер интерфейса

#define USB_DEBUG_LEVEL 3

#include <libusb-1.0/libusb.h>

#define DATA_SIZE 2


#define EP_IN 0x81
#define EP_OUT 0x01

#define TIMEOUT 20000

#define ACM_CTRL_DTR   0x01
#define ACM_CTRL_RTS 0x02


void interrupt_transfer_loop(libusb_device_handle *handle);
void bulk_transfer_loop(libusb_device_handle *handle);



struct libusb_device_descriptor desc; //description of device structure

libusb_device_handle *dev_handle = NULL;   //a device handle
libusb_context       *ctx = NULL;           //a libusb session
libusb_device        *dev = NULL;          //pointer to device
libusb_device        **devs = NULL;        //pointer to pointer of device


