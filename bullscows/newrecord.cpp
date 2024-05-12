#include "newrecord.h"
#include "ui_newrecord.h"
#include <QMessageBox>
#include <QDebug>

NewRecord::NewRecord(QString &name, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewRecord), name(name)
{
    ui->setupUi(this);
    connect(ui->OKButton, SIGNAL(clicked()), this, SLOT(WantsOnRecord()));
    connect(ui->CancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

void NewRecord::WantsOnRecord()
{
    if(ui->NameEdit->text() == "")
    {
        QMessageBox::warning(0, "Ошибка", "Введите ваше имя!");
    }
    else
    {
        name = ui->NameEdit->text();
        accept();
    }
}

NewRecord::~NewRecord()
{
    delete ui;
}
