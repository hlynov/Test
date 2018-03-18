#include <gtk/gtk.h>
#include "hl_d3d.h"
#include "hl_usb.h"


//***********************************************************************
//MAIN
//***********************************************************************
//
int main(int argc, char *argv[])

{
    /* Declare variables */
    int var[3]={100, 200, 300};
    char textForLabel[]="My var works";
    /* END of Declare variables */

    // instantiate structure, allocating memory for it
    app_widgets        *widgets = g_slice_new(app_widgets);
    TestStruct         *status = g_slice_new(TestStruct);
    Data data;

    data.i=123;
    check=1;

    /* запускаем GTK+ */
    gtk_init(&argc, &argv);


    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "window_main(1).glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    // get pointers to label widgets
    widgets->w_lbl_time  = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_time"));
    widgets->w_lbl_count = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_count"));
    buttonf2 = GTK_WIDGET(gtk_builder_get_object(builder, "btn2"));

    // widgets pointer will be passed to all widget handler functions as the user_data parameter


    gtk_builder_connect_signals(builder, widgets);    // note: second parameter is not NULL
    //gtk_builder_connect_signals(builder, status);    // note: second parameter is not NULL
    g_signal_connect (buttonf2, "clicked", G_CALLBACK (my_func), &data);


    g_object_unref(builder);


    // USB INIT
    libusb_init(NULL);   // инициализация

    libusb_set_debug(NULL, USB_DEBUG_LEVEL);  // уровень вывода отладочных сообщений
    libusb_device_handle *handle = libusb_open_device_with_vid_pid(NULL, VID, PID);


    if (handle == NULL) {

        g_print ("Device No Connected \n");
        status->x = 1;
        //return 1;
    }
    else
    {
        status->x = 0;
        g_print ("NOppa/n");
    }



    gtk_widget_show(window);
    gtk_main();
    // free up memory used by widget structure, probably not necessary as OS will
    // reclaim memory from application after it exits
    g_slice_free(app_widgets, widgets);

    return 0;
}


//****************************************************************************************
//Callback Functions
//****************************************************************************************



// callback function for button clicked signal
void on_btn_update_clicked(GtkButton *button, app_widgets *app_wdgts)
{
    GDateTime   *time;            // for storing current time and date
    gchar       *time_str;        // current time and date as a string
    static gint count = 0;        // stores number of times button was clicked
    gchar       *count_str;       // button clicked count as a string

    time     = g_date_time_new_now_local();             // get the current time
    time_str = g_date_time_format(time, "%H:%M:%S");    // convert current time to string
    count++;                                            // number of times button clicked
    count_str = g_strdup_printf("%d", count);           // convert count to string

    // update time and count in label widgets
    gtk_label_set_text(GTK_LABEL(app_wdgts->w_lbl_time), time_str);
    gtk_label_set_text(GTK_LABEL(app_wdgts->w_lbl_count), count_str);

    // free memory used by glib functions
    g_free(time_str);
    g_date_time_unref(time);
    g_free(count_str);
}





static void my_func (GtkWidget* w , Data *data)

{
    int a = data->i;

    g_print ("%d\n", a);
}





// called when window is closed
void on_window_main_destroy()
{
    gtk_main_quit();
}
