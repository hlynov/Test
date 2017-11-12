



typedef struct
{
    int i;
    GtkWidget *target;
} Data;



static void my_func(GtkButton*, GtkWindow*);
static void my_func2();
void change( GtkWidget *widget,
        Data      *data );

static void button_callback(GtkWidget* w ,gpointer data);

static void print_hello (GtkWidget *widget, gpointer data)
{
    g_print ("Connect button clicked\n");
};

