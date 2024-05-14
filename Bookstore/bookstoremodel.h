#ifndef BOOKSTOREMODEL_H
#define BOOKSTOREMODEL_H

#include <QWidget>
#include <QTabWidget>
#include <QTableWidget>
#include <QGridLayout>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QHeaderView>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QMessageBox>
#include <QTextCodec>

class Bookstoremodel
{
public:
    Bookstoremodel();
    void FileUpdate();
    QTableWidget* GetBooksTable();
    void SetMinPrice(int x);
    void SetMaxPrice(int x);
    int GetMinPrice();
    int GetMaxPrice();
    void SetBookName(QString x);
    void SetAuthorName(QString x);
    void SetYear(int x);
    void SetCost(int x);
    QString GetBookName();
    QString GetAuthorName();
    int GetYear();
    int GetCost();
private:
    QTableWidget* table = new QTableWidget;
    int minprice = -1, maxprice = -1, year = -1, cost = -1;
    QString bookname = "", authorname = "";
};

class SortingItem : public QTableWidgetItem
{
public:
    bool operator<(const QTableWidgetItem& other) const
    {
        return (this->text().toInt() < other.text().toInt());
    }
};

#endif // BOOKSTOREMODEL_H
