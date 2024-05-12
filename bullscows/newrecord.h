#ifndef NEWRECORD_H
#define NEWRECORD_H

#include <QDialog>

namespace Ui {
class NewRecord;
}

class NewRecord : public QDialog
{
    Q_OBJECT

public:
    explicit NewRecord(QString &name, QWidget *parent = nullptr);
    ~NewRecord();
    QString getname()
    {
        return name;
    }
public slots:
    void WantsOnRecord();
private:
    Ui::NewRecord *ui;
    QString &name;
};

#endif // NEWRECORD_H
