# Ambilight Project
# Ambilight device access library
#
# Copyright: (c) 2010 by Karol Maciaszek
# E-mail   : <karol.maciaszek@gmail.com>
# WWW      : http://www.czystybeton.pl/
#
# $Id$


USBFLAGS=`pkg-config --cflags libusb-1.0`
USBLIBS=`pkg-config --libs libusb-1.0`
X11LIBS=`pkg-config --libs x11`

CC=gcc
INSTALL=/bin/install
RM=/bin/rm
LDCONFIG=/sbin/ldconfig

CFLAGS=-O -Wall -fPIC $(USBFLAGS)
LIBS=$(USBLIBS) $(X11LIBS)

OBJS=ambilight.o usb.o x11capture.o

LIBNAME=libambilight.so
VERSION=1.0.0
SONAME=$(LIBNAME).$(VERSION)

PREFIX=/usr/local
HEADER=ambilight.h

all: $(LIBNAME)


$(LIBNAME): $(OBJS)
	$(CC) $(LIBS) -shared -Wl,-soname,$(LIBNAME) -o $(SONAME) $(OBJS)


clean:
	$(RM) -f $(OBJS) $(SONAME)


.c.o:
	$(CC) $(CFLAGS) -c $*.c -o $*.o


install: $(LIBNAME)
	$(INSTALL) $(SONAME) $(PREFIX)/lib/
	$(INSTALL) $(HEADER) $(PREFIX)/include/
	$(LDCONFIG)


uninstall:
	$(RM) $(PREFIX)/lib/$(SONAME)
	$(RM) $(PREFIX)/include/$(HEADER)
	$(LDCONFIG)
