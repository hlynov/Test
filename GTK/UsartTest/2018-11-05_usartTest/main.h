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
GtkWidget *entry1;
GtkWidget *spinfan;

GtkWidget *lbl1;
GtkWidget *lbl2;
GtkWidget *btn1;
GtkWidget *btn2;
GtkWidget *btnExit;


typedef struct teststruct
{
    int check;
    int i;
    char *msg;
} MyData;

typedef struct comport
{
    int fd;
    int wlen;
    char buf[9];/*размер зависит от размера строки принимаемых данных*/
    int outa; 
    int iIn;
    char testvar[40];
} ComPD;


static void my_func(GtkButton*, GtkWindow*);
static void my_func2();
static void window_destroy();
void *thread_func(void *thread_data);
int comportInit(struct comport *t);

static void Press_F1(GtkWidget* w ,gpointer data);
static void Press_F2 (GtkWidget *widget, gpointer data);

static void entry_test( GtkWidget *widget, GtkWidget *entry );
static void spinfan_test( GtkWidget *widget, GtkWidget *spinfan );


void mainwindowdraw();


#endif
