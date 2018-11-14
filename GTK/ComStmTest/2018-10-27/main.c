/*MY TEST PROGRAMM*/
/******************/

#include "main.h"
#include "myprog.h"

int main (int argc, char *argv[]){
	
    const gchar* home = "mystyle.css";
    GError *error = 0;

	MyData threadData; // создали структуру data

    threadData.i=10;
    char *message[] = {"My message from data struct"};
    threadData.msg = *message;
    
    //переменные для работы с потоками
    int id1, id2, result;
    pthread_t thread1, thread2;
    id1 = 1; /*идентификатор потока*/
    //

    /*This is called in all GTK applications.*/
    gtk_init (&argc, &argv);
    
    /*  g_thread_init(NULL);  /*инициализация работы с потоками*/


    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "form.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));

    // get pointers to label widgets
    lbl1  = GTK_WIDGET(gtk_builder_get_object(builder, "lbl1"));
    lbl2  = GTK_WIDGET(gtk_builder_get_object(builder, "lbl2"));

    btn1 = GTK_WIDGET(gtk_builder_get_object(builder, "btn1"));
    btnExit = GTK_WIDGET(gtk_builder_get_object(builder, "btnExit"));

    /* ----------------- CSS ------------------------------------*/
    provider = gtk_css_provider_new ();
    display = gdk_display_get_default ();
    screen = gdk_display_get_default_screen (display);
    gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider),
    GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    
    gtk_css_provider_load_from_file(provider, g_file_new_for_path(home), &error);
    g_object_unref (provider);

    /* -----------------------------------------------------------*/

    //gtk_builder_connect_signals(builder, status);    // note: second parameter is not NULL
    
    g_signal_connect (btn1, "clicked", G_CALLBACK (button_callback), &threadData);
    g_signal_connect (btnExit, "clicked", G_CALLBACK (window_destroy), NULL);

    g_object_unref(builder);

    /* -----------------------------------------------------------*/
    //Эксперименты с потоками
    /* -----------------------------------------------------------*/

    result = pthread_create (&thread1, NULL, thread_func, &threadData);//создали поток
    if (result != 0) {
        perror("Создание первого потока!");
        return EXIT_FAILURE;
    };
    g_print ("%d\n", result);
    printf("Поток создан\n");
    printf("поле i данных потока = %i \n", threadData.i);

    result = pthread_join(thread1, NULL);
    if (result != 0) {
        perror("Ждём первый поток");
        return EXIT_FAILURE;
    }

    printf("поле i данных потока стало = %i \n", threadData.i);

    

     

    gtk_label_set_text(GTK_LABEL(lbl1), threadData.msg);   
    gtk_label_set_text(GTK_LABEL(lbl2),"qwerty");


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


void *thread_func(void *thread_data)
{
    int i;
    MyData *data = (MyData *) thread_data;

    //int loc_id = * (int *) arg.i;
    int loc_id = data->i;

    for (i = 0; i < 3; i++) {
        printf("Поток %i работает\n", loc_id);

        gtk_label_set_text(GTK_LABEL(lbl2),"ccccccccc");
        sleep(1);
    }
    data->i++;
}
