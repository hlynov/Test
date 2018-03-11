
#include <gtk/gtk.h>

int main (int argc, char *argv[]){


    /* Declare widgets */
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;
    GtkWidget *label;

    /*This is called in all GTK applications. Arguments are parsed from the command line and are returned to the application.*/
    gtk_init (&argc, &argv);

    /* create a new window, set its title and put it on center */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "FTP Client");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 300);














    /* Now that we are done packing our widgets, we show them all in one go, by calling gtk_widget_show_all() on the window.*/
    gtk_widget_show_all (window);

    /* All GTK applications must have a gtk_main(). Control ends here and waits for an event to occur (like a key press or a mouse event),
     * until gtk_main_quit() is called. */
    gtk_main ();

    return 0;
}

