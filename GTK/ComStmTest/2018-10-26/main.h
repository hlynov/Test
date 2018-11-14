#ifndef MAIN_h__
#define MAIN_h__

#include <glib.h>
#include <gtk/gtk.h>
#include <pthread.h>
#include "myprog.h"


/*---- CSS ------------*/
GtkCssProvider *provider;
GdkDisplay *display;
GdkScreen *screen;
/*---------------------*/

GtkBuilder      *builder;

GtkWidget *window;
GtkWidget *grid;
GtkWidget *button;
GtkWidget *mybutton;

GtkWidget *lbl1;
GtkWidget *btn1;
GtkWidget *btnExit;


GtkWidget *label_user;
GtkWidget *label_host;
GtkWidget *label_pass;
GtkWidget *label_my;


typedef struct
{
    int check;
    int i;
} Data;



static void my_func(GtkButton*, GtkWindow*);
static void my_func2();
static void button_callback(GtkWidget* w ,gpointer data);
static void window_destroy();


void mainwindowdraw();


#endif










