#ifndef BOOKSTORE_H
#define BOOKSTORE_H

#include "bookstoremodel.h"

class Bookstore : public QWidget
{
    Q_OBJECT

public slots:
    void NotifyMinPriceChange(const QString& text);
    void NotifyMaxPriceChange(const QString& text);
    void NotifyCheck();
    void DisplayTable(QTableWidget* pricebooktable);
    void NotifyBookNameChange(const QString& text);
    void NotifyAuthorNameChange(const QString& text);
    void NotifyYearChange(const QString& text);
    void NotifyCostChange(const QString& text);
    void NotifyAdd();
signals:
    void SignalMinPriceChange(const QString&);
    void SignalMaxPriceChange(const QString&);
    void SignalCheck();
    void SignalBookNameChange(const QString&);
    void SignalAuthorNameChange(const QString&);
    void SignalYearChange(const QString&);
    void SignalCostChange(const QString&);
    void SignalAdd();
public:
    Bookstore(Bookstoremodel* mvcmodel, QWidget *parent = nullptr);

private:
    Bookstoremodel* model;
};

class Bookstorecontroller : public QObject
{
    Q_OBJECT
public slots:
    void ChangeModelMinPrice(const QString& text);
    void ChangeModelMaxPrice(const QString& text);
    void CheckPrices();
    void BookNameChange(const QString& text);
    void AuthorNameChange(const QString& text);
    void YearChange(const QString& text);
    void CostChange(const QString& text);
    void AddBook();
signals:
    void TableReady(QTableWidget* pricebooktable);
public:
    Bookstorecontroller(Bookstoremodel* mvcmodel);
private:
    Bookstoremodel* model;
};

#endif // BOOKSTORE_H
