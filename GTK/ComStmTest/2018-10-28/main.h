#ifndef MAIN_h__
#define MAIN_h__

#include <errno.h>
#include <glib.h>
#include <gtk/gtk.h>
#include <pthread.h>
#include "myprog.h"
#include "comport.h"


#include <fcntl.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>





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
GtkWidget *lbl2;
GtkWidget *btn1;
GtkWidget *btnExit;


typedef struct teststruct
{
    int check;
    int i;
    char *msg;

} MyData;



static void my_func(GtkButton*, GtkWindow*);
static void my_func2();
static void button_callback(GtkWidget* w ,gpointer data);
static void window_destroy();
void *thread_func(void *thread_data);
int comportInit(void);


void mainwindowdraw();


#endif










