#include <QtGui/QApplication>
#include "qambilight.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QAmbilight w;
    w.show();
    return a.exec();
}
