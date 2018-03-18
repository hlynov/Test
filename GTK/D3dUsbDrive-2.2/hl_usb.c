



int res       = 0;  /* return codes from libusb functions */
int numBytes  = 0;  /* Actual bytes transferred. */
int rc;
int transferred = 0;
unsigned char Report_to_read[64];
