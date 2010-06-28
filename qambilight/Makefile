# Ambilight Project
# Ambilight Qt GUI
#
# Copyright: (c) 2010 by Karol Maciaszek
# E-mail   : <karol.maciaszek@gmail.com>
# WWW      : http://www.czystybeton.pl/
#
# $Id$

  
CC=g++
MOC=/usr/bin/moc
CFLAGS=-c -Wall -I/usr/include -I/usr/local/include
LDFLAGS=-lQtGui -lQtCore -lkdeui -lambilight
SOURCES=main.cpp qambilight.cpp $(MOC_SOURCES)
OBJECTS=$(SOURCES:.cpp=.o)
MOC_SOURCES=$(patsubst %.h, moc_%.cpp, $(shell grep -l Q_OBJECT *.h))

EXECUTABLE=qambilight

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

moc_%.cpp: %.h
	$(MOC) $< -o $@

clean:
	rm -rf $(OBJECTS) $(MOC_SOURCES) $(EXECUTABLE)
