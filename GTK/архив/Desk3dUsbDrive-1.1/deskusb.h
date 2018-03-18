#ifndef DESKUSB_H
#define DESKUSB_H

#include <gtk/gtk.h>




int x;

typedef struct
{
    GtkLabel *lblresult;
    int x, y;
} mystruct;

typedef struct {
    GtkWidget *w_lbl;
    GtkWidget *w_lbl_count;
} app_widgets;

#endif //  DESKUSB_H



