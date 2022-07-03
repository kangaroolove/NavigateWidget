#include "NavigateWidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NavigateWidget w;
    w.show();
    return a.exec();
}
