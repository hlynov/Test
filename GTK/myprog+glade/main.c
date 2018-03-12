#include <gtk/gtk.h>

/* создание окна в этот раз мы вынесли в отдельную функцию */
static GtkWidget*
create_window (void)
{
        /* это виджет окна */
        GtkWidget *window;
        /* это тот волшебный объект, который сделает за нас окошко */
        GtkBuilder *builder;
        /* сюда будем складывать ошибки */
        GError* error = NULL;

        /* тут загружаем файл с интерфейсом */
        builder = gtk_builder_new ();
        if (!gtk_builder_add_from_file (builder, "habrahabr.ui", &error))
        {
                /* загрузить файл не удалось */
                g_critical ("Не могу загрузить файл: %s", error->message);
                g_error_free (error);
        }

        /* помните, мы подключали сигналы вручную? теперь это происходит автоматически! */
        gtk_builder_connect_signals (builder, NULL);

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

/* это главная функция нашего приложения, которая будет выполнена первой */
int
main (int argc, char *argv[])
{
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

/* это и есть наш обработчик сигнала */
void
helloworld (GtkButton *button,
            gpointer   label)
{
        /* установить метке текст */
        gtk_label_set_text (label, "Привет, Хабр!");
}
