#
CC = g++
BIN = $(SRC:%.c=%)
	SRC = $(wildcard *.c)
	OBJ = $(SRC:%.c=%.o)


#
# Flags d'erreurs:
#
ERROR_CFLAGS = -Wall -W -pedantic


#
# Flags pour le compilateur:
#
GLIB_CFLAGS = $$(pkg-config --cflags glib-3.0)
PANGO_CFLAGS = $$(pkg-config --cflags pango)
GTK_CFLAGS = $$(pkg-config --cflags gtk+-3.0)

CFLAGS = $(ERROR_FLAGS) $(GLIB_CFLAGS) $(PANGO_CFLAGS) $(GTK_CFLAGS)


#
# Flags pour l'editeur de liens:
#
GLIB_LDFLAGS = $$(pkg-config --libs glib-3.0)
PANGO_LDFLAGS = $$(pkg-config --libs pango)
GTK_LDFLAGS = $$(pkg-config --libs gtk+-3.0)

LDFLAGS = $(ERROR_FLAGS) $(GLIB_LDFLAGS) $(PANGO_LDFLAGS) $(GTK_LDFLAGS)


#
# Construction du programme:
#
LIB=-L/usr/lib/libusb-1.0 -lusb-1.0 -pthread  
INC=-I/usr/include/libusb-1.0

all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)
	$(CC) $(LDFLAGS) -o $(BIN) $(OBJ) $(INC) $(LIB)


#
# Nettoyage:
#
clean:
	rm -f *.o *~ core $(BIN)
