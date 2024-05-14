#include "bookstore.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Bookstoremodel mdl;
    Bookstorecontroller cntrl(&mdl);
    Bookstore view(&mdl);
    QObject::connect(&view, SIGNAL(SignalMinPriceChange(const QString&)), &cntrl, SLOT(ChangeModelMinPrice(const QString&)));
    QObject::connect(&view, SIGNAL(SignalMaxPriceChange(const QString&)), &cntrl, SLOT(ChangeModelMaxPrice(const QString&)));
    QObject::connect(&view, SIGNAL(SignalCheck()), &cntrl, SLOT(CheckPrices()));
    QObject::connect(&cntrl, SIGNAL(TableReady(QTableWidget*)), &view, SLOT(DisplayTable(QTableWidget*)));
    QObject::connect(&view, SIGNAL(SignalBookNameChange(const QString&)), &cntrl, SLOT(BookNameChange(const QString&)));
    QObject::connect(&view, SIGNAL(SignalAuthorNameChange(const QString&)), &cntrl, SLOT(AuthorNameChange(const QString&)));
    QObject::connect(&view, SIGNAL(SignalYearChange(const QString&)), &cntrl, SLOT(YearChange(const QString&)));
    QObject::connect(&view, SIGNAL(SignalCostChange(const QString&)), &cntrl, SLOT(CostChange(const QString&)));
    QObject::connect(&view, SIGNAL(SignalAdd()), &cntrl, SLOT(AddBook()));
    view.show();
    return a.exec();
}
