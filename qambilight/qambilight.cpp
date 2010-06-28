/* Ambilight Project
 * Ambilight Qt GUI
 *
 * Copyright: (c) 2010 by Karol Maciaszek
 * E-mail   : <karol.maciaszek@gmail.com>
 * WWW      : http://www.czystybeton.pl/
 *
 * $Id$
 */


#include <cstdio>
#include <QtGui/QApplication>
#include <QtGui/QIcon>
#include <ambilight.h>

#include "qambilight.h"


QAmbilight::QAmbilight(QWidget* parent) :
	QWidget(parent)
{
	this->setupUi();
	this->retranslateUi();

	config.edge_thickness = 30;
	config.frequency = 25;
	config.leds_bottom = 6;
	config.leds_left = 4;
	config.leds_right = 4;
	config.leds_top = 6;
	config.margin_bottom = 0;
	config.margin_left = 0;
	config.margin_right = 0;
	config.margin_top = 0;

	this->initAmbilight();
}


QAmbilight::~QAmbilight() {

}


void QAmbilight::changeEvent(QEvent* e) {
	QWidget::changeEvent(e);

	switch (e->type()) {
		case QEvent::LanguageChange:
			this->retranslateUi();
		default:
			break;
	}
}


void QAmbilight::retranslateUi(void) {
	this->setWindowTitle(QApplication::translate("QAmbilight", "QAmbilight", 0, QApplication::UnicodeUTF8));
	statusBox->setTitle(QApplication::translate("QAmbilight", "Status", 0, QApplication::UnicodeUTF8));
	button->setText(QApplication::translate("QAmbilight", "Refresh leds", 0, QApplication::UnicodeUTF8));
}


void QAmbilight::setupUi(void) {
	this->setObjectName(QString::fromUtf8("QAmbilight"));
	this->resize(300, 400);
	this->setWindowIcon(QIcon(QString::fromUtf8("qambilight.png")));

	trayIcon = new QSystemTrayIcon(this);
	trayIcon->setIcon(QIcon(QString::fromUtf8("qambilight.png")));
	trayIcon->show();

	statusBox = new QGroupBox(this);
	statusBox->setGeometry(QRect(0, 0, 300, 400));

	deviceLed = new KLed(statusBox);
	deviceLed->setGeometry(QRect(20, 30, 16, 16));
	deviceLedLabel = new QLabel(statusBox);
	deviceLedLabel->setGeometry(QRect(40, 30, 150, 16));

	x11Led = new KLed(statusBox);
	x11Led->setGeometry(QRect(20, 50, 16, 16));
	x11LedLabel = new QLabel(statusBox);
	x11LedLabel->setGeometry(QRect(40, 50, 150, 16));

	button = new QPushButton(statusBox);
	button->setGeometry(QRect(20, 70, 97, 22));

	connect(button, SIGNAL(clicked()), this, SLOT(refreshAmbilight()));
}


void QAmbilight::initAmbilight(void) {
	int ret = ambilight_open_device();

	switch (ret) {
		case AMBILIGHT_OK:
			deviceLedLabel->setText(QApplication::translate("QAmbilight", "Device initialized", 0, QApplication::UnicodeUTF8));
			deviceLed->setColor(QColor(0, 0xff, 0));
			break;
		default:
			deviceLedLabel->setText(QApplication::translate("QAmbilight", "Unknown device error", 0, QApplication::UnicodeUTF8));
			deviceLed->setColor(QColor(0xff, 0, 0));
	}

	ret = ambilight_configure(&config);

	switch (ret) {
		case AMBILIGHT_OK:
			x11LedLabel->setText(QApplication::translate("QAmbilight", "X11 display initialized", 0, QApplication::UnicodeUTF8));
			x11Led->setColor(QColor(0, 0xff, 0));
			break;
		default:
			x11LedLabel->setText(QApplication::translate("QAmbilight", "Can't open x11 display", 0, QApplication::UnicodeUTF8));
			x11Led->setColor(QColor(0xff, 0, 0));
	}

}


void QAmbilight::refreshAmbilight(void) {
	ambilight_refresh();
}


void QAmbilight::closeAmbilight(void) {
	ambilight_close_device();
}
