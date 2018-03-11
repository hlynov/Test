
//============================================================================
// Name        : usb_testing.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

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


int res       = 0;  /* return codes from libusb functions */
int numBytes  = 0;  /* Actual bytes transferred. */
int rc;
int transferred = 0;


unsigned char Report_to_read[64];



void interrupt_transfer_loop(libusb_device_handle *handle);
void bulk_transfer_loop(libusb_device_handle *handle);



int main() {
    //cout << std::hex;

    int i=0,
        rv=0,
        bTransfer=0;

    // unsigned char EP_out = 0x81; // write into usb  end point
    // unsigned char EP_in  = 0x01; // read from usb end point

    unsigned char TX[8] = {04, 02, 03, 04, 05, 06, 07, 07}; //reqwest
    unsigned char RX[521]; //answer

    struct libusb_device_descriptor desc; //description of device structure

    libusb_device_handle *dev_handle = NULL;   //a device handle
    libusb_context       *ctx = NULL;           //a libusb session
    libusb_device        *dev = NULL;          //pointer to device
    libusb_device        **devs = NULL;        //pointer to pointer of device


    libusb_init(NULL);   // инициализация

    libusb_set_debug(NULL, USB_DEBUG_LEVEL);  // уровень вывода отладочных сообщений


    libusb_device_handle *handle = libusb_open_device_with_vid_pid(NULL, VID, PID);


    if (handle == NULL) {
        cout << "Устройство не подключено\n";
        return 1;
    } else cout << "Устройство найдено\n";





    if (libusb_kernel_driver_active(handle,DEV_INTF))
        libusb_detach_kernel_driver(handle, DEV_INTF);


    if (libusb_claim_interface(handle,  DEV_INTF) < 0){
        cout << "Ошибка захвата интерфейса\n";
        return 2;
    }




    /* Send the message to endpoint 1 with a 100ms timeout. */
    res = libusb_interrupt_transfer(handle, EP_OUT, TX, 8, &numBytes, 1000);
    if (res == 0)
    {
        printf("%d bytes transmitted successfully.\n", numBytes);
    }
    else
    {
        fprintf(stderr, "Error sending message to device.\n");
    }






    rc = libusb_bulk_transfer(handle, EP_OUT, TX, 8, &transferred, 0);

    if (rc == 0 && transferred == 8)
    {
        printf("\nWrite successful!");
        printf("\nSent %d bytes with string: %s\n", transferred, TX);
    }
    else
        printf("\nError in write! e = %d and transferred = %d\n", rc, transferred);



    unsigned char buf[DATA_SIZE];
    int act_len = 0;

    rc = libusb_bulk_transfer(handle, EP_IN, Report_to_read, DATA_SIZE,&act_len, TIMEOUT);  //64: Max Packet   Length
    if (rc == 0)
    {
        printf("\nReceived: ");
        printf("%c", Report_to_read); //Will read a string
        //sleep(1);
    }
    else
    {
        printf("\nError in read! rc = %d and received = %d\n", rc, act_len);
        return -1;
    }







    interrupt_transfer_loop(handle);
    // bulk_transfer_loop(handle);


    libusb_attach_kernel_driver(handle, DEV_INTF);
    libusb_close(handle);
    libusb_exit(NULL);


    return 0;
}

void interrupt_transfer_loop(libusb_device_handle *handle) {
    cout << "Цикл считывания (interrupt).\n";
    unsigned char buf[DATA_SIZE];
    int ret;
    int i=0x2;

    int cc=0;

    struct timeval start, end;
    long mtime, seconds, useconds;
    gettimeofday(&start, NULL);

    while (i--) {

        int returned = libusb_interrupt_transfer(handle, EP_IN, buf, DATA_SIZE, &ret, TIMEOUT);

        if (returned >= 0) {
            for (short i=0; i < DATA_SIZE; i++) {
                cout << "buf["<< i << "] = " << (int)buf[i] << endl;
            }
        } else cout << libusb_error_name(returned);
        cc++;
    }

    cout << "Считано: " << cc << endl;

    gettimeofday(&end, NULL);

    seconds  = end.tv_sec  - start.tv_sec;
    useconds = end.tv_usec - start.tv_usec;

    mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;

    cout << "Прошло: " << mtime << " мс\n";
}

void bulk_transfer_loop(libusb_device_handle *handle) {
    /// TODO:
    /// write bulk transfer code for ucontroller & this section
    cout << "Цикл считывания (bulk).\n";

    unsigned char buf[DATA_SIZE];
    int act_len = 0;

    int cc=0;
    int i=1;

    struct timeval start, end;
    long mtime, seconds, useconds;
    gettimeofday(&start, NULL);

    while(i--) {
        int returned = libusb_bulk_transfer(handle, EP_IN, buf, DATA_SIZE,&act_len, TIMEOUT);

        // parce transfer errors
        if (returned >= 0) {
            for (short i=0; i < DATA_SIZE; i++) {
                cout << "buf["<< i << "] = " << (int)buf[i] << endl;
            }
        } else cout << libusb_error_name(returned);

        cc++;
    }

    cout << "Считано: " << cc << endl;

    gettimeofday(&end, NULL);

    seconds  = end.tv_sec  - start.tv_sec;
    useconds = end.tv_usec - start.tv_usec;

    mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;

    cout << "Прошло: " << mtime << " мс\n";
}
