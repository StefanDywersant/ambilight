# Ambilight Project
# Console application
#
# Copyright: (c) 2010-2011 by Karol Maciaszek
# E-mail   : <karol.maciaszek@gmail.com>
# WWW      : http://www.czystybeton.pl/
#
# $Id$
  
USBFLAGS=`pkg-config --cflags libusb-1.0`
USBLIBS=`pkg-config --libs libusb-1.0`
X11LIBS=`pkg-config --libs x11`

CC=gcc
CFLAGS=-O -Wall $(USBFLAGS) -I/usr/local/include
LIBS=$(USBLIBS) $(X11LIBS) -lgd -lambilight

OBJ=main.o
PROGRAM=ambilight

all: $(PROGRAM)

$(PROGRAM): $(OBJ)
	$(CC) -o $(PROGRAM) $(OBJ) $(LIBS)

strip: $(PROGRAM)
	strip $(PROGRAM)

clean:
	rm -f $(OBJ) $(PROGRAM)

.c.o:
	$(CC) -fPIC $(CFLAGS) -c $*.c -o $*.o
