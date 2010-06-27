/* Ambilight Project
 * Ambilight Qt GUI
 *
 * Copyright: (c) 2010 by Karol Maciaszek
 * E-mail   : <karol.maciaszek@gmail.com>
 * WWW      : http://www.czystybeton.pl/
 *
 * $Id$
 */


#include <QtGui/QApplication>

#include "qambilight.h"


int main (int argc, char* argv[]) {
	QApplication a(argc, argv);
	QAmbilight qa;
	qa.show();
	return a.exec();
}
