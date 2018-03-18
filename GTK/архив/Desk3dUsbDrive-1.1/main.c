

#include <gtk/gtk.h>
#include "deskusb.h"


/* создание окна */

static GtkWidget*

create_window (void)
{

    /* Declare widgets */
    GtkWidget *window;

    GtkWidget *buttonfunc1;
    GtkWidget *buttonfunc2;
    GtkWidget *buttonfunc3;
    GtkWidget *buttonfunc4;
    GtkWidget *buttonfunc5;

    GtkWidget *lblresult;

    /* End of Declare widgets */

    // instantiate structure, allocating memory for it
    app_widgets  *widgets = g_slice_new(app_widgets);


    /* make window */
    GtkBuilder *builder;


    /* сюда будем складывать ошибки */
    GError* error = NULL;

    /* тут загружаем файл с интерфейсом */
    builder = gtk_builder_new ();
    if (!gtk_builder_add_from_file (builder, "Desk3dUsbDrive-1.1.ui", &error))
    {
        /* загрузить файл не удалось */
        g_critical ("Не могу загрузить файл: %s", error->message);
        g_error_free (error);
    }




    // get pointers to the  widgets
    buttonfunc1 = GTK_WIDGET(gtk_builder_get_object(builder, "buttonfunc1"));
    widgets->w_lbl = GTK_WIDGET(gtk_builder_get_object(builder, "lblresult"));
    //lblresult=data->lblresult;


    /* signals connection */
    gtk_builder_connect_signals (builder, widgets);


    /* получаем виджет окна, чтобы его показать */
    window = GTK_WIDGET (gtk_builder_get_object (builder, "window"));
    if (!window)
    {
        /* что-то не так, наверное, ошиблись в имени */
        g_critical ("Ошибка при получении виджета окна");
    }
    g_object_unref (builder);

    return window;
}

/* MAIN */

int main (int argc, char *argv[])
{

    /* Declare variables */

    int var[3]={100, 200, 300};
    char textForLabel[]="My var works";



    /* виджет окна */
    GtkWidget *window;

    /* запускаем GTK+ */
    gtk_init (&argc, &argv);

    /* вызываем нашу функцию для создания окна */
    window = create_window ();
    gtk_widget_show (window);

    /* передаём управление GTK+ */
    gtk_main ();
    return 0;
}




/* Handlers */

void f1clicked (GtkButton *buttonfunk1, app_widgets *app_wgts)
{
    /* установить метке текст */
    gtk_label_set_text (GTK_LABEL(app_wgts->w_lbl), "Привет, Хабр!");
}
