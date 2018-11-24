/******************************************************************************
* File Name :   main.c
* Author :      DESK3D machinary
* Version :     2.2
* Date :        2018-11-15
* Target :      PC
* Description : TermoFanPC-2.2
*******************************************************************************/

#include "main.h"
#include "myprog.h"


int main (int argc, char *argv[]){

        //Заполнение полей структур
	ComPD comportdata; // экземпляр для работы с COM-портом	
	comportdata.fd = 0;
	strcpy (comportdata.testvar, "Привет из comportData"); //Просто для проверки
	struct comportdata *comportdata_adr;//объявление указателя на структуру. Проверить зачем оно надо!!!
	
	MyData threadData; // создали структуру data, для передачи данных в поток
	//Заполнение полей структур
	threadData.i=10;
	char *message[] = {"My message from data struct"};
	threadData.msg = *message;
	    
    
	//переменные для работы с потоками
    int id1, id2, result;
    pthread_t thread1, thread2, SendTaskThread, GetTaskThread;
    id1 = 1; /*идентификатор потока*/
	
	
	
  	const gchar* home = "mystyle.css";
	GError *error = 0;
	
    /*This is called in all GTK applications.*/
    gtk_init (&argc, &argv);
    /*g_thread_init(NULL);  /*инициализация работы с потоками*/


    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "form.glade", NULL);
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    /* ----------------- CSS ------------------------------------*/
    provider = gtk_css_provider_new ();
    display = gdk_display_get_default ();
    screen = gdk_display_get_default_screen (display);
    gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider),
    GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    gtk_css_provider_load_from_file(provider, g_file_new_for_path(home), &error);
    g_object_unref (provider);
    /* -----------------------------------------------------------*/
    // get pointers to label widgets
    lbl1  = GTK_WIDGET(gtk_builder_get_object(builder, "lbl1"));
    lbl2  = GTK_WIDGET(gtk_builder_get_object(builder, "lbl2"));

    btn1 = GTK_WIDGET(gtk_builder_get_object(builder, "btn1"));
    btn2 = GTK_WIDGET(gtk_builder_get_object(builder, "btn2"));
    btnExit = GTK_WIDGET(gtk_builder_get_object(builder, "btnExit"));
    entry1  = GTK_WIDGET(gtk_builder_get_object(builder, "entry1"));
    spinfan  = GTK_WIDGET(gtk_builder_get_object(builder, "spinfan"));

        //gtk_builder_connect_signals(builder, status);    // note: second parameter is not NULL
    
    g_signal_connect (btn1, "clicked", G_CALLBACK (Press_F1), &comportdata);
    g_signal_connect (btn2, "clicked", G_CALLBACK (Press_F2), NULL);
    g_signal_connect (btnExit, "clicked", G_CALLBACK (window_destroy), NULL);
    g_signal_connect (entry1, "activate",   G_CALLBACK (entry_test), entry1);
    g_signal_connect (spinfan, "value-changed",   G_CALLBACK (spinfan_test), spinfan);

    g_object_unref(builder);

    
    int fd2;
    comportInit(&comportdata);

    char buf[9];/*размер зависит от размера строки принимаемых данных*/
    int outa=0; 
    int iIn;

        //iIn=read(fd2,buf,4); /*чтения приходящих данных из порта*/
        //printf("%s",buf);

   

    /* -----------------------------------------------------------*/
    //Эксперименты с потоками
    /* -----------------------------------------------------------*/

    result = pthread_create (&thread1, NULL, thread_func, &comportdata);//создали поток
    if (result != 0) {
        perror("Создание первого потока!");
        return EXIT_FAILURE;
    };
    g_print ("%d\n", result);
    printf("Поток создан\n");
    printf("поле i данных потока = %i \n", threadData.i);

/*  result = pthread_join(thread1, NULL);
    if (result != 0) {
        perror("Ждём первый поток");
        return EXIT_FAILURE;
    }
*/

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



static void Press_F1 (GtkWidget  *w , gpointer data)
{
    ComPD *dataF1 = (ComPD *) data;
    
    g_print ("Hello World\n");
    g_print (dataF1->testvar);
    
    /* simple output */
    dataF1->wlen = write(dataF1->fd, "0", 1);
    if (dataF1->wlen != 1) {
        printf("Error from write: %d, %d\n", dataF1->wlen, errno);
    }
    tcdrain(dataF1->fd);    /* delay for output */
}


static void Press_F2 (GtkWidget *widget, gpointer data)
{
    g_print ("Connect button clicked\n");

    const gchar *entry_text2;
    entry_text2 = gtk_entry_get_text (GTK_ENTRY(entry1));
    g_print (entry_text2);
    
};


void *thread_func(void *thread_data)
{
    int i;
    char buf[9];
    ComPD *data = (ComPD *) thread_data;
    while(1)
    {
    data->iIn=read(data->fd,buf,4); /*чтения приходящих данных из порта*/
    printf("%s",buf);

        gtk_label_set_text(GTK_LABEL(lbl2),buf);
        sleep(1);
    }
    
}


static void entry_test( GtkWidget *widget, GtkWidget *entry )
{
  const gchar *entry_text;
  entry_text = gtk_entry_get_text (GTK_ENTRY (entry));
  printf ("Entry contents: %s\n", entry_text);
}


static void spinfan_test( GtkWidget *widget, GtkWidget *spinfan)
{
  guint32 spinvalue;
  gchar out_str[100] = {0}; // buffer for string
   spinvalue = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON(spinfan));
  //g_print ("Entry contents: %s\n", spinvalue);
  g_snprintf(out_str, sizeof(out_str), "%d", spinvalue);
  gtk_label_set_text(GTK_LABEL(lbl2), out_str);
}


// Функция потока формирования задачи и отправки по UART
void *SendTask(TfUartTask)
{
	
}






// called when window is closed
void window_destroy()
{
    gtk_main_quit();
}


//End of Programm. D3D. 2018г

