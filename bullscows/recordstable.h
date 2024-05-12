#ifndef RECORDSTABLE_H
#define RECORDSTABLE_H

#include <QWidget>
#include <QTableWidget>

namespace Ui {
class recordstable;
}

class recordstable : public QWidget
{
    Q_OBJECT

public:
    explicit recordstable(QTableWidget* table, QWidget *parent = nullptr);
    ~recordstable();

private:
    Ui::recordstable *ui;
};

#endif // RECORDSTABLE_H
