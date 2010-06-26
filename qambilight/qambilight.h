#ifndef QAMBILIGHT_H
#define QAMBILIGHT_H

#include <QWidget>

namespace Ui {
    class QAmbilight;
}

class QAmbilight : public QWidget {
    Q_OBJECT
public:
    QAmbilight(QWidget *parent = 0);
    ~QAmbilight();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::QAmbilight *ui;
};

#endif // QAMBILIGHT_H
