#include "bookstoremodel.h"

Bookstoremodel::Bookstoremodel()
{
    QFile booktable("Book Table.txt");
    table->setColumnCount(4);
    table->setHorizontalHeaderItem(0, new QTableWidgetItem("Название"));
    table->setHorizontalHeaderItem(1, new QTableWidgetItem("Автор"));
    table->setHorizontalHeaderItem(2, new QTableWidgetItem("Год издания"));
    table->setHorizontalHeaderItem(3, new QTableWidgetItem("Цена (рубли)"));
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->verticalHeader()->hide();
    if(booktable.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while(!booktable.atEnd())
        {
            table->insertRow(table->rowCount());
            QString line = booktable.readLine(), curpart;
            SortingItem* x = new SortingItem;
            curpart = line.mid(0, line.indexOf(';'));
            line.remove(0, line.indexOf(';') + 1);
            x->setText(curpart);
            table->setItem(table->rowCount() - 1, 0, x);
            x = new SortingItem;
            curpart = line.mid(0, line.indexOf(';'));
            line.remove(0, line.indexOf(';') + 1);
            x->setText(curpart);
            table->setItem(table->rowCount() - 1, 1, x);
            x = new SortingItem;
            curpart = line.mid(0, line.indexOf(';'));
            line.remove(0, line.indexOf(';') + 1);
            x->setText(curpart);
            table->setItem(table->rowCount() - 1, 2, x);
            curpart = line.mid(0, line.indexOf('\n'));
            x = new SortingItem;
            x->setText(curpart);
            table->setItem(table->rowCount() - 1, 3, x);
        }
        table->sortByColumn(2, Qt::AscendingOrder);
        table->resizeColumnsToContents();
        booktable.close();
    }
}
QTableWidget* Bookstoremodel::GetBooksTable()
{
    return table;
}
void Bookstoremodel::SetMinPrice(int x)
{
    minprice = x;
}
void Bookstoremodel::SetMaxPrice(int x)
{
    maxprice = x;
}
int Bookstoremodel::GetMinPrice()
{
    return minprice;
}
int Bookstoremodel::GetMaxPrice()
{
    return maxprice;
}
void Bookstoremodel::SetBookName(QString x)
{
    bookname = x;
}
void Bookstoremodel::SetAuthorName(QString x)
{
    authorname = x;
}
void Bookstoremodel::SetYear(int x)
{
    year = x;
}
void Bookstoremodel::SetCost(int x)
{
    cost = x;
}
QString Bookstoremodel::GetBookName()
{
    return bookname;
}
QString Bookstoremodel::GetAuthorName()
{
    return authorname;
}
int Bookstoremodel::GetYear()
{
    return year;
}
int Bookstoremodel::GetCost()
{
    return cost;
}
void Bookstoremodel::FileUpdate()
{
    QFile booktable("Book Table.txt");
    if(booktable.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        booktable.resize(0);
        QTextStream output(&booktable);
        output.setCodec(QTextCodec::codecForName("UTF-8"));
        output.flush();
        for(int i = 0; i < table->rowCount(); i++)
        {
            for(int j = 0; j < table->columnCount(); j++)
            {
                output << table->item(i, j)->text();
                if(j + 1 < table->columnCount())
                {
                    output << ';';
                }
            }
            output << '\n';
            output.flush();
        }
        booktable.close();
    }
}
