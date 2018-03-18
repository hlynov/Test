#include <gtk/gtk.h>

// custom structure that will hold pointers to widgets and / or user variables
typedef struct {
    GtkWidget *w_lbl_time;
    GtkWidget *w_lbl_count;
} app_widgets;

int main(int argc, char *argv[])
{
    GtkBuilder      *builder; 
    GtkWidget       *window;
    // instantiate structure, allocating memory for it
    app_widgets        *widgets = g_slice_new(app_widgets);

    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "window_main.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    // get pointers to label widgets
    widgets->w_lbl_time  = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_time"));
    widgets->w_lbl_count = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_count"));
    // widgets pointer will be passed to all widget handler functions as the user_data parameter
    gtk_builder_connect_signals(builder, widgets);    // note: second parameter is not NULL
    g_object_unref(builder);

    gtk_widget_show(window);                
    gtk_main();
    // free up memory used by widget structure, probably not necessary as OS will
    // reclaim memory from application after it exits
    g_slice_free(app_widgets, widgets);

    return 0;
}

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

// called when window is closed
void on_window_main_destroy()
{
    gtk_main_quit();
}
