#include "bullsandcows.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Bullsandcows w;
    w.show();
    return a.exec();
}
