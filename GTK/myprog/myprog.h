

typedef struct
{
    int i;
    GtkWidget *target;
} Data;



static void my_func(GtkButton*, GtkWindow*);
static void my_func2();

void change( GtkWidget *widget, Data *data );

static void button_callback(GtkWidget* w ,gpointer data);


void mainwindowdraw();



/* Declare widgets */
GtkWidget *window;
GtkWidget *grid;
GtkWidget *button;
GtkWidget *mybutton;

GtkWidget *u_name;
GtkWidget *h_name;
GtkWidget *pass;
GtkWidget *label_user;
GtkWidget *label_host;
GtkWidget *label_pass;
GtkWidget *label_my;











