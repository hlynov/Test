
#include <gtk/gtk.h>
#include <string.h>  /* for css */



int main (int argc, char *argv[]){

    /*---- CSS ------------*/
    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;
    /*---------------------*/


    /* Declare widgets */
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;
    GtkWidget *label;

    /*This is called in all GTK applications. Arguments are parsed from the command
      line and are returned to the application.*/
    gtk_init (&argc, &argv);

    /* create a new window, set its title and put it on center */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "FTP Client");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 300);

    g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE); /* window is NOT resizable */

    /* Here we construct the container that is going pack our buttons */
    grid = gtk_grid_new ();
    gtk_grid_set_row_spacing (GTK_GRID (grid), 10);
    gtk_grid_set_column_spacing (GTK_GRID (grid), 10);

    /* Pack the container in the window */
    gtk_container_add (GTK_CONTAINER (window), grid);

    /*Add Labels*/
    label=gtk_label_new("  *Label new*  ");
    gtk_grid_attach (GTK_GRID (grid), label, 1,1,1,1);



    /* ----------------- CSS ------------------------------------*/
    provider = gtk_css_provider_new ();
    display = gdk_display_get_default ();
    screen = gdk_display_get_default_screen (display);
    gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider),
            GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    const gchar* home = "mystyle.css";

    GError *error = 0;

    gtk_css_provider_load_from_file(provider, g_file_new_for_path(home), &error);
    g_object_unref (provider);
    /* -----------------------------------------------------------*/









    /* Now that we are done packing our widgets, we show them all in one go,
       by calling gtk_widget_show_all() on the window.*/
    gtk_widget_show_all (window);

    /* All GTK applications must have a gtk_main().
       Control ends here and waits for an event to occur (like a key press or a mouse event),
     * until gtk_main_quit() is called. */
    gtk_main ();

    return 0;
}

