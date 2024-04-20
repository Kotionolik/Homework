#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QSize>
#include <QGridLayout>
#include <QLabel>
#include <QBoxLayout>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; class WinnerTicTac; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    Widget(const int N, QWidget *parent = nullptr);
    ~Widget();
private slots:
    void TicTacButtons();
    void AI(QPushButton* checkbtn);
    void ClearBoard();
signals:
    void startAI(QPushButton* checkbtn);
private:
    QString CheckWin();
    void WinDialogue();
    int buttonschecked = 0;
    Ui::Widget *ui;
    QBoxLayout* GameLayout;
    QPushButton* Clearbutton;
    QGridLayout* TicTacLayout;
    QLabel* lbl;
    QVector<QVector<QPushButton*>> btn;
    QString winner = "";
};

class WinnerTicTac : public QWidget
{
    Q_OBJECT
private:
    friend Widget;
    WinnerTicTac(QString winnertext, QWidget *parent = nullptr);
    ~WinnerTicTac();
    Ui::WinnerTicTac *ui1;
};

#endif // WIDGET_H
