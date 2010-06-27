# Ambilight Project
# Ambilight Qt GUI
#
# Copyright: (c) 2010 by Karol Maciaszek
# E-mail   : <karol.maciaszek@gmail.com>
# WWW      : http://www.czystybeton.pl/
#
# $Id$

  
CC=g++
CFLAGS=-c -Wall -I/usr/include
LDFLAGS=-lQtGui -lQtCore
SOURCES=main.cpp qambilight.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=qambilight

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)
