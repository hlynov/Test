/* hl_usb.c
 *
 *
 *
 */



#include <gtk/gtk.h>
#include "hl_usb.h"

int res       = 0;  /* return codes from libusb functions */
int numBytes  = 0;  /* Actual bytes transferred. */
int transferred = 0;

libusb_device_handle *dev_handle = NULL;   //a device handle
libusb_context       *ctx = NULL;           //a libusb session
libusb_device        *dev = NULL;          //pointer to device
libusb_device        **devs = NULL;        //pointer to pointer of device



void myTestFunc()
{
    g_print("my TestFunction is work!!! \n");

};



void concheck( libusb_device_handle *handle, GtkWidget *lblConnectionStatus)
{
    //Check connection status
    if (handle == NULL) {
        gtk_label_set_text(GTK_LABEL(lblConnectionStatus), "Device not connected.");
        g_print ("Device No Connected \n");
    }
    else
    {
        gtk_label_set_text(GTK_LABEL(lblConnectionStatus), "OK! Device connected!");
        g_print ("Device Connected \n");
    }

    if (libusb_kernel_driver_active(handle,DEV_INTF))
        libusb_detach_kernel_driver(handle, DEV_INTF);


    if (libusb_claim_interface(handle,  DEV_INTF) < 0){
        g_print ( "Ошибка захвата интерфейса\n");
        //  return 0;
    }


}

//End Check connection status



void testRead (libusb_device_handle *handle)
{
    int rc;
    unsigned char buf[DATA_SIZE];
    int act_len = 0;
    unsigned char Report_to_read[64];

    rc = libusb_bulk_transfer(handle, EP_IN, Report_to_read, DATA_SIZE,&act_len, TIMEOUT);  //64: Max Packet   Length

    if (rc == 0)
    {
        g_print("\nReceived: ");
        g_print("%c", Report_to_read); //Will read a string
        //sleep(1);
    }
    else
    {
        g_print("\nError in read! rc = %d and received = %d\n", rc, act_len);
        //        return -1;
    }
}




void interrupt_transfer_loop(libusb_device_handle *handle, int rx[])
{
    //g_print ("Цикл считывания (interrupt).\n");
    unsigned char buf[DATA_SIZE];
    int ret;
    int i=1;
    int cc=0;

    struct timeval start, end;
    long mtime, seconds, useconds;
    gettimeofday(&start, NULL);

    while (i--) {
        int returned = libusb_interrupt_transfer(handle, EP_IN, buf, DATA_SIZE, &ret, TIMEOUT);

        if (returned >= 0) {
            for (short i=0; i < DATA_SIZE; i++) {
                //g_print ("%u\n", buf[i]) ;
                rx[i]=buf[i];
            }
        } else g_print (libusb_error_name(returned));
        cc++;
    }
}





