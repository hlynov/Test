/* Descrizione: GUI Client FTP sviluppato come progetto per il corso di Reti di Calcolatori (laurea SSRI presso DTI Crema)
 * Sviluppatori: Paolo Stivanin, Filippo Roncari, Stefano Agostini.
 * Anno: 2012
 * Licenza: GNU AGPL v3 <http://www.gnu.org/licenses/agpl-3.0.html>
 * Sito web: <https://github.com/polslinux/FTPUtils> */

#include "main.h"
#include "myprog.h"



int main (int argc, char *argv[]){
	
	Data data;
	int exit_cod;
	       
	       
    /*This is called in all GTK applications.*/
    gtk_init (&argc, &argv);
    //g_thread_init(NULL);  /*инициализация работы с потоками*/


    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "form.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));

    // get pointers to label widgets
    lbl1  = GTK_WIDGET(gtk_builder_get_object(builder, "lbl1"));
    btn1 = GTK_WIDGET(gtk_builder_get_object(builder, "btn1"));
    btnExit = GTK_WIDGET(gtk_builder_get_object(builder, "btnExit"));

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

    //gtk_builder_connect_signals(builder, status);    // note: second parameter is not NULL
    g_signal_connect (btn1, "clicked", G_CALLBACK (button_callback), &data);
    g_signal_connect (btnExit, "clicked", G_CALLBACK (window_destroy), NULL);

    g_object_unref(builder);

    g_print ("sssssss"); 
    gtk_label_set_text(GTK_LABEL(lbl1),"ass");   

    /* Now that we are done packing our widgets, we show them all in one go, by calling gtk_widget_show_all() on the window.*/
    gtk_widget_show_all (window);

    /* All GTK applications must have a gtk_main(). Control ends here and waits for an event to occur (like a key press or a mouse event),
     * until gtk_main_quit() is called. */



    gtk_main ();

    return 0;
}



static void button_callback(GtkWidget* w ,gpointer data)
{
    g_print ("Hello World\n");
}


static void print_hello (GtkWidget *widget, gpointer data)
{
    g_print ("Connect button clicked\n");
};


// called when window is closed
void window_destroy()
{
    gtk_main_quit();
}



