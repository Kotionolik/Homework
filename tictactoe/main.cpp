#include "widget.h"
#include <QDebug>
#include <QTimer>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    const int N = 3;
    Widget w(N);
    w.show();
    return a.exec();
}
