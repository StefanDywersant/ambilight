#
# Ambilight
# Aktywne podświetlenie monitora.
#
# Copyright: (c) 2010 by Karol Maciaszek
# E-mail   : <karol.maciaszek@gmail.com>
# WWW      : http://www.czystybeton.pl/
#
# $Id$
#


MAKE=make


all: iohex ledhex

iohex:
	cd iochip && $(MAKE) hex

ledhex:
	cd ledchip && $(MAKE) hex

ioflash:
	cd iochip && $(MAKE) flash

ledflash:
	cd ledchip && $(MAKE) flash

iofuse:
	cd iochip && $(MAKE) fuse

ledfuse:
	cd ledchip && $(MAKE) fuse

ioreset:
	cd iochip && $(MAKE) reset

ledreset:
	cd ledchip && $(MAKE) reset

clean: ioclean ledclean

ioclean:
	cd iochip && $(MAKE) clean

ledclean:
	cd ledchip && $(MAKE) clean
