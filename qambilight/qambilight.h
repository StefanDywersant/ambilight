/* Ambilight Project
 * Ambilight Qt GUI
 *
 * Copyright: (c) 2010 by Karol Maciaszek
 * E-mail   : <karol.maciaszek@gmail.com>
 * WWW      : http://www.czystybeton.pl/
 *
 * $Id$
 */


#ifndef QAMBILIGHT_H_
#define QAMBILIGHT_H_


#include <QtGui/QPushButton>
#include <QtGui/QGroupBox>
#include <QtGui/QLabel>
#include <QtGui/QSystemTrayIcon>
#include <QtGui/QSlider>
#include <QtGui/QSpinBox>
#include <QtGui/QWidget>
#include <ambilight.h>
#include <kled.h>


class QAmbilight : public QWidget {
	Q_OBJECT
public:
	QAmbilight(QWidget *parent = 0);
	~QAmbilight();

	QSystemTrayIcon* trayIcon;
	QSlider* topSlider;
	QSlider* leftSlider;
	QSlider* bottomSlider;
	QSlider* rightSlider;
	QFrame* screenshotFrame;
	QLabel* screenshotLabel;
	QFrame* line;
	KLed* hwStatusLed;
	QLabel* hwStatusLabel;
	QLabel* thicknessLabel;
	QSlider* thicknessSlider;
	QLabel* frequencyLabel;
	QSpinBox* frequencySpinBox;
	QPushButton* startStopButton;
	QPushButton* hideButton;


protected:
	void changeEvent(QEvent* e);
	void closeAmbilight(void);
	void initAmbilight(void);
	void retranslateUi(void);
	void setupWidgets(void);
	void setupSize(unsigned int height);

	struct ambilight_config config;

};


#endif /* QAMBILIGHT_H_ */
