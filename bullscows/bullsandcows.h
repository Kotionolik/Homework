#ifndef BULLSANDCOWS_H
#define BULLSANDCOWS_H

#include <QMainWindow>
#include <QDebug>
#include <QTableWidgetItem>
#include "newrecord.h"
#include "recordstable.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Bullsandcows; }
QT_END_NAMESPACE

class Bullsandcows : public QMainWindow
{
    Q_OBJECT

public:
    Bullsandcows(QWidget *parent = nullptr);
    ~Bullsandcows();
public slots:
    void ShowRecords();
    void StartGame();
    void CheckNumber();
private:
    void SetRecord(int x);
    Ui::Bullsandcows *ui;
    int number = -1;
    int tries = 0;
    recordstable* table = nullptr;
};
class CheckingItem: public QTableWidgetItem
{
 public:
     CheckingItem(QString str);
     bool operator< (const QTableWidgetItem &other) const
     {
         if(this->text()[0] < '0' || this->text()[0] > '9')
         {
             return true;
         }
         else return (this->text().toInt() < other.text().toInt());
     }
};
#endif // BULLSANDCOWS_H
