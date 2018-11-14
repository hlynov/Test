#
CC = gcc
BIN = $(SRC:%.c=%)
	SRC = $(wildcard *.c)
	OBJ = $(SRC:%.c=%.o)

# debug
DEBUG=-g
# optimisation
OPT=-O0
# warnings
WARN=-Wall

#APR_LIBS = -L/lib/x86_64-linux-gnu/ -lm -lcrypto -lpthread -lssl -lapr-1 -laprutil-1
#set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread")

#
# Flags d'erreurs:
#
ERROR_CFLAGS = -Wall -W -pedantic


#
# Flags pour le compilateur:
#
GLIB_CFLAGS = $$(pkg-config --cflags glib-2.0)
PANGO_CFLAGS = $$(pkg-config --cflags pango)
GTK_CFLAGS = $$(pkg-config --cflags gtk+-3.0)

CFLAGS = $(ERROR_FLAGS) $(GLIB_CFLAGS) $(PANGO_CFLAGS) $(GTK_CFLAGS)


#
# Flags pour l'editeur de liens:
#
GLIB_LDFLAGS = $$(pkg-config --libs glib-2.0)
PANGO_LDFLAGS = $$(pkg-config --libs pango)
GTK_LDFLAGS = $$(pkg-config --libs gtk+-3.0)

LDFLAGS = $(ERROR_FLAGS) $(GLIB_LDFLAGS) $(PANGO_LDFLAGS) $(GTK_LDFLAGS)


#
# Construction du programme:
#

all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(CFLAGS) -c  $(SRC) 
	$(CC) $(LDFLAGS) -o main $(OBJ) $ -rdynamic -lpthread $(INC) $(LIB)


#
# Nettoyage:
#
clean:
	rm -f *.o *~ core $(BIN)
