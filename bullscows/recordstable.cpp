#include "recordstable.h"
#include "ui_recordstable.h"
#include<QTableWidgetItem>
#include<QGridLayout>
#include<QLabel>
#include<QDebug>

recordstable::recordstable(QTableWidget* table, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::recordstable)
{
    ui->setupUi(this);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setVisible(false);
    ui->tableWidget->setRowCount(table->rowCount());
    ui->tableWidget->setColumnCount(table->columnCount());
    for(int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        for(int j = 0; j < ui->tableWidget->columnCount(); j++)
        {
            ui->tableWidget->setItem(i, j, new QTableWidgetItem(table->item(i, j)->text()));
        }
    }
}

recordstable::~recordstable()
{
    delete ui;
}
