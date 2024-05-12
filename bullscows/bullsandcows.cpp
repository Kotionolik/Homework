#include "bullsandcows.h"
#include "ui_bullsandcows.h"
#include <QString>
#include <QMessageBox>
#include <QFile>
#include <QIODevice>
#include <QDebug>
#include <QTextStream>

Bullsandcows::Bullsandcows(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Bullsandcows)
{
    ui->setupUi(this);
    this->setWindowTitle("Быки и Коровы");
    srand(time(0));
    ui->NumberLine->setEnabled(false);
    ui->CheckButton->setEnabled(false);
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setVisible(false);
    ui->tableWidget->setColumnWidth(0, 5);
    ui->tableWidget->setColumnWidth(1, 115);
    ui->tableWidget->setColumnWidth(2, 115);
    ui->tableWidget->insertRow(0);
    ui->tableWidget->setItem(0, 1, new QTableWidgetItem("Число"));
    ui->tableWidget->setItem(0, 2, new QTableWidgetItem("Результат"));
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(ui->RecordsButton, SIGNAL(clicked()), this, SLOT(ShowRecords()));
    connect(ui->NewGameButton, SIGNAL(clicked()), this, SLOT(StartGame()));
    connect(ui->CheckButton, SIGNAL(clicked()), this, SLOT(CheckNumber()));
    ui->NumberLine->setValidator(new QIntValidator(0, 9999, this));
}
void Bullsandcows::ShowRecords()
{
    QFile* txtrecord = new QFile("Records Table.txt");
    CheckingItem* newitem = nullptr;
    txtrecord->open(QIODevice::ReadWrite);
    QTableWidget* changingtable = new QTableWidget;
    changingtable->setColumnCount(3);
    changingtable->insertRow(0);
    changingtable->setItem(0, 0, new QTableWidgetItem("Место: "));
    newitem = new CheckingItem("Попытки: ");
    changingtable->setItem(0, 1, newitem);
    changingtable->setItem(0, 2, new QTableWidgetItem("Имя: "));
    QString line = txtrecord->readLine(), curitem;
    while(!txtrecord->atEnd())
    {
        line = txtrecord->readLine();
        changingtable->insertRow(changingtable->rowCount());
        curitem = "";
        curitem.append(line.begin(), line.indexOf(';'));
        changingtable->setItem(changingtable->rowCount() - 1, 0, new QTableWidgetItem(curitem));
        line.remove(0, line.indexOf(';') + 1);
        curitem = "";
        curitem.append(line.begin(), line.indexOf(';'));
        newitem = new CheckingItem(curitem);
        changingtable->setItem(changingtable->rowCount() - 1, 1, newitem);
        line.remove(0, line.indexOf(';') + 1);
        curitem = line;
        if(curitem.indexOf('\n') != 0)
        {
            curitem.chop(1);
        }
        changingtable->setItem(changingtable->rowCount() - 1, 2, new QTableWidgetItem(curitem));
    }
    table = new recordstable(changingtable);
    table->show();
    changingtable = nullptr;
    delete txtrecord;
    delete newitem;
    delete changingtable;
}
void Bullsandcows::StartGame()
{
    number = (rand() % 9000) + 1000;
    tries = 0;
    ui->NumberLine->setEnabled(true);
    ui->CheckButton->setEnabled(true);
    ui->StatusLabel->setText("Игра началась");
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->insertRow(0);
    ui->tableWidget->setItem(0, 1, new QTableWidgetItem("Число"));
    ui->tableWidget->setItem(0, 2, new QTableWidgetItem("Результат"));
}
void Bullsandcows::CheckNumber()
{
    if(ui->NumberLine->text().size() == 4)
    {
        tries++;
        QString x;
        int bulls = 0, cows = 0;
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        x.setNum(tries);
        ui->tableWidget->setItem(tries, 0, new QTableWidgetItem(x));
        ui->tableWidget->setItem(tries, 1, new QTableWidgetItem(ui->NumberLine->text()));
        QString enterednumber = ui->NumberLine->text();
        x.setNum(number);
        ui->NumberLine->clear();
        if(x == enterednumber)
        {
            bulls = 4;
            ui->StatusLabel->setText("Число угадано!");
            ui->NumberLine->setEnabled(false);
            ui->CheckButton->setEnabled(false);
            SetRecord(tries);
        }
        else
        {
            ui->StatusLabel->setText("Число не угадано.");
            for(int i = 0; i < 4; i++)
            {
                if(enterednumber[i] == x[i])
                {
                    bulls++;
                    enterednumber[i] = '-';
                    x[i] = '.';
                }
            }
            for(int i = 0; i < 4; i++)
            {
                for(int j = 0; j < 4; j++)
                {
                    if(enterednumber[i] == x[j])
                    {
                        cows++;
                        enterednumber[i] = '-';
                        x[j] = '.';
                        break;
                    }
                }
            }
        }
        x = "Быки: " + QString::number(bulls) + "; Коровы: " + QString::number(cows);
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 2, new QTableWidgetItem(x));
    }
    else
    {
        QMessageBox::warning(0, "Ошибка", "Введенные данные должны быть четырёхзначным числом!");
        ui->NumberLine->clear();
    }
}
void Bullsandcows::SetRecord(int x)
{
    bool changed = 0;
    QFile* txtrecord = new QFile("Records Table.txt");
    CheckingItem* newitem = nullptr;
    txtrecord->open(QIODevice::ReadWrite);
    QTableWidget* changingtable = new QTableWidget;
    changingtable->setColumnCount(3);
    changingtable->insertRow(0);
    changingtable->setItem(0, 0, new QTableWidgetItem("Место: "));
    newitem = new CheckingItem("Попытки: ");
    changingtable->setItem(0, 1, newitem);
    changingtable->setItem(0, 2, new QTableWidgetItem("Имя: "));
    QString line = txtrecord->readLine(), curitem;
    while(!txtrecord->atEnd())
    {
        line = txtrecord->readLine();
        changingtable->insertRow(changingtable->rowCount());
        curitem = "";
        curitem.append(line.begin(), line.indexOf(';'));
        changingtable->setItem(changingtable->rowCount() - 1, 0, new QTableWidgetItem(curitem));
        line.remove(0, line.indexOf(';') + 1);
        curitem = "";
        curitem.append(line.begin(), line.indexOf(';'));
        newitem = new CheckingItem(curitem);
        changingtable->setItem(changingtable->rowCount() - 1, 1, newitem);
        line.remove(0, line.indexOf(';') + 1);
        curitem = line;
        if(curitem.indexOf('\n') != 0)
        {
            curitem.chop(1);
        }
        changingtable->setItem(changingtable->rowCount() - 1, 2, new QTableWidgetItem(curitem));
    }
    for(int i = 1; i < changingtable->rowCount(); i++)
    {
        if(changingtable->item(i, 1)->text().toInt() > x)
        {
            changed = 1;
            break;
        }
    }
    if(changingtable->rowCount() < 11)
    {
        changed = 1;
    }
    if(changed)
    {
        QString playername = "";
        NewRecord* rd = new NewRecord(playername);
        rd->show();
        if(rd->exec() == QDialog::Accepted)
        {
            playername = rd->getname();
        }
        if(playername != "")
        {
            if(changingtable->rowCount() <= 11)
            {
                changingtable->insertRow(changingtable->rowCount());
                line.setNum(changingtable->rowCount() - 1);
                changingtable->setItem(changingtable->rowCount() - 1, 0, new QTableWidgetItem(line));
                line.setNum(x);
                changingtable->setItem(changingtable->rowCount() - 1, 1, new QTableWidgetItem(line));
                newitem = new CheckingItem(line);
                changingtable->setItem(changingtable->rowCount() - 1, 1, newitem);
                changingtable->setItem(changingtable->rowCount() - 1, 2, new QTableWidgetItem(playername));
                changingtable->sortByColumn(1, Qt::AscendingOrder);
            }
            else
            {
                changingtable->insertRow(changingtable->rowCount());
                line.setNum(changingtable->rowCount() - 1);
                changingtable->setItem(changingtable->rowCount() - 1, 0, new QTableWidgetItem(line));
                line.setNum(x);
                changingtable->setItem(changingtable->rowCount() - 1, 1, new QTableWidgetItem(line));
                newitem = new CheckingItem(QString::number(x));
                changingtable->setItem(changingtable->rowCount() - 1, 1, newitem);
                changingtable->setItem(changingtable->rowCount() - 1, 2, new QTableWidgetItem(playername));
                changingtable->sortByColumn(1, Qt::AscendingOrder);
                changingtable->setRowCount(11);
            }
        }
        txtrecord->resize(0);
        QTextStream out(txtrecord);
        for(int i = 0; i < changingtable->rowCount(); i++)
        {
           if(i > 0)
           {
               changingtable->item(i, 0)->setText(QString::number(i));
           }
           out << changingtable->item(i, 0)->text() << ';' << changingtable->item(i, 1)->text() << ';' << changingtable->item(i, 2)->text() << '\n';
           out.flush();
        }
        delete rd;
    }
    delete newitem;
    delete txtrecord;
    delete changingtable;
}

CheckingItem::CheckingItem(QString str)
{
    this->setText(str);
}

Bullsandcows::~Bullsandcows()
{
    delete ui;
    delete table;
}
