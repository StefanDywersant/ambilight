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
#include <QtGui/QPainter>
#include <QtGui/QImage>
#include <ambilight.h>

#include "qambilight.h"


QAmbilight::QAmbilight(QWidget* parent) :
	QWidget(parent)
{
	this->setupWidgets();
	this->setupSize(170);
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


void QAmbilight::setupWidgets(void) {
	this->setObjectName(QString::fromUtf8("QAmbilight"));
	this->setWindowIcon(QIcon(QString::fromUtf8("qambilight.png")));

	trayIcon = new QSystemTrayIcon(this);
	trayIcon->setIcon(QIcon(QString::fromUtf8("qambilight.png")));
	trayIcon->show();

	topSlider = new QSlider(Qt::Horizontal, this);

	leftSlider = new QSlider(Qt::Vertical, this);

	bottomSlider = new QSlider(Qt::Horizontal, this);

	rightSlider = new QSlider(Qt::Vertical, this);

	screenshotFrame = new QFrame(this);
	screenshotFrame->setFrameShape(QFrame::Panel);
	screenshotFrame->setFrameShadow(QFrame::Raised);

	screenshotLabel = new QLabel(screenshotFrame);

    line = new QFrame(this);
    line->setFrameShape(QFrame::VLine);
    line->setFrameShadow(QFrame::Sunken);

    hwStatusLed = new KLed(this);
    hwStatusLed->setGeometry(QRect(410, 15, 16, 16));

    hwStatusLabel = new QLabel(this);
    hwStatusLabel->setGeometry(QRect(430, 15, 250, 13));

    thicknessLabel = new QLabel(this);
    thicknessLabel->setGeometry(QRect(410, 45, 70, 13));

    thicknessSlider = new QSlider(Qt::Horizontal, this);
    thicknessSlider->setGeometry(490, 40, 190, 23);

    frequencyLabel = new QLabel(this);
    frequencyLabel->setGeometry(QRect(410, 75, 70, 13));

    frequencySpinBox = new QSpinBox(this);
    frequencySpinBox->setGeometry(QRect(490, 70, 54, 23));

    startStopButton = new QPushButton(this);

    hideButton = new QPushButton(this);
}


void QAmbilight::setupSize(unsigned int height) {
	this->resize(690, height + 60);

	topSlider->setGeometry(QRect(28, 5, 324, 23));
	leftSlider->setGeometry(QRect(5, 28, 23, height + 4));
	bottomSlider->setGeometry(QRect(28, height + 34, 324, 23));
	rightSlider->setGeometry(QRect(354, 28, 23, height + 4));
	screenshotFrame->setGeometry(QRect(28, 28, 324, height + 4));
	screenshotLabel->setGeometry(QRect(2, 2, 320, height));
    line->setGeometry(QRect(380, 7, 16, height + 46));
    startStopButton->setGeometry(QRect(480, height + 32, 97, 22));
    hideButton->setGeometry(QRect(586, height + 32, 97, 22));
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
	hwStatusLabel->setText(QApplication::translate("QAmbilight", "Device status", 0, QApplication::UnicodeUTF8));
	thicknessLabel->setText(QApplication::translate("QAmbilight", "Thickness", 0, QApplication::UnicodeUTF8));
	frequencyLabel->setText(QApplication::translate("QAmbilight", "Frequency", 0, QApplication::UnicodeUTF8));
	startStopButton->setText(QApplication::translate("QAmbilight", "Start", 0, QApplication::UnicodeUTF8));
	hideButton->setText(QApplication::translate("QAmbilight", "Hide", 0, QApplication::UnicodeUTF8));
}


void QAmbilight::initAmbilight(void) {
//	int ret = ambilight_open_device();

/*	switch (ret) {
		case AMBILIGHT_OK:
			deviceLedLabel->setText(QApplication::translate("QAmbilight", "Device initialized", 0, QApplication::UnicodeUTF8));
			deviceLed->setColor(QColor(0, 0xff, 0));
			break;
		default:
			deviceLedLabel->setText(QApplication::translate("QAmbilight", "Unknown device error", 0, QApplication::UnicodeUTF8));
			deviceLed->setColor(QColor(0xff, 0, 0));
	}
*/
/*	ret = ambilight_configure(&config);

	switch (ret) {
		case AMBILIGHT_OK:
			x11LedLabel->setText(QApplication::translate("QAmbilight", "X11 display initialized", 0, QApplication::UnicodeUTF8));
			x11Led->setColor(QColor(0, 0xff, 0));
			break;
		default:
			x11LedLabel->setText(QApplication::translate("QAmbilight", "Can't open x11 display", 0, QApplication::UnicodeUTF8));
			x11Led->setColor(QColor(0xff, 0, 0));
	}
*/

}


/*void QAmbilight::screenshotAmbilight(void) {
	printf("dupsko\n");
	XImage* ximage;
	ambilight_get_screenshot(&ximage);
	QImage image = QImage((const uchar*)ximage->data, ximage->width, ximage->height, ximage->bytes_per_line, QImage::Format_RGB32);
	QImage scaled = image.scaled(192, 108, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

	int i, j;

	for (i = 0; i < scaled.width(); i++) {
		for (j = 0; j < scaled.height(); j++) {
			QColor color = QColor::fromRgb(scaled.pixel(i, j));
			color = color.darker(200);
			scaled.setPixel(i, j, color.rgb());
		}
	}
	screenshotLabel->setPixmap(QPixmap::fromImage(scaled));
}*/


/*void QAmbilight::closeAmbilight(void) {
	ambilight_close_device();
}*/
