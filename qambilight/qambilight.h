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
#include <QtGui/QWidget>
#include <ambilight.h>
#include <kled.h>


class QAmbilight : public QWidget {
	Q_OBJECT
public:
	QAmbilight(QWidget *parent = 0);
	~QAmbilight();

	QSystemTrayIcon* trayIcon;
	QGroupBox* statusBox;
	KLed* deviceLed;
	QLabel* deviceLedLabel;
	KLed* x11Led;
	QLabel* x11LedLabel;
	QPushButton* button;

public slots:
	void refreshAmbilight(void);

protected:
	void changeEvent(QEvent* e);
	void closeAmbilight(void);
	void initAmbilight(void);
	void retranslateUi(void);
	void setupUi(void);

	struct ambilight_config config;

};


#endif /* QAMBILIGHT_H_ */
