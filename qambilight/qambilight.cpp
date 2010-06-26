#include "qambilight.h"
#include "ui_qambilight.h"

QAmbilight::QAmbilight(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QAmbilight)
{
    ui->setupUi(this);
}

QAmbilight::~QAmbilight()
{
    delete ui;
}

void QAmbilight::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
