#include "widget.h"
#include "ui_widget.h"
#include "ui_winnertictac.h"
#include <QPushButton>
#include <QMainWindow>
#include <QSize>
#include <QGridLayout>
#include <QLabel>
#include <QBoxLayout>
#include <QTimer>
#include <QDebug>
#include <QCloseEvent>

Widget::Widget(const int N, QWidget *parent) : QWidget(parent)
  , ui(new Ui::Widget) , btn(N, QVector<QPushButton*>(N))
{
  ui->setupUi(this);
  this->setWindowTitle("Tic-Tac-Toe");
  connect(this, SIGNAL(startAI(QPushButton*)),this,SLOT(AI(QPushButton*)));
  GameLayout = new QBoxLayout(QBoxLayout::TopToBottom);
  TicTacLayout = new QGridLayout;
  lbl = new QLabel;
  Clearbutton = new QPushButton;
  Clearbutton->setText("Clear");
  lbl->setText("Player 1");
  for(int i = 0; i < N; i++)
  {
      for(int j = 0; j < N; j++)
      {
          QPushButton* button = new QPushButton();
          QString text = QString('0' + i + j);
          button->setFixedSize(25, 25);
          btn[i][j] = button;
          TicTacLayout->addWidget(button, i, j);
          TicTacLayout->setColumnStretch(j, 0);
          connect(btn[i][j], SIGNAL(clicked()),this,SLOT(TicTacButtons()));
      }
      TicTacLayout->setRowStretch(i, 0);
  }
  connect(Clearbutton, SIGNAL(clicked()), this, SLOT(ClearBoard()));
  TicTacLayout->setSpacing(0);
  GameLayout->addWidget(lbl);
  GameLayout->addLayout(TicTacLayout);
  GameLayout->addWidget(Clearbutton);
  GameLayout->insertStretch(-1, 1);
  setLayout(GameLayout);
}
Widget::~Widget()
{
    delete ui;
    delete[] GameLayout;
    delete[] TicTacLayout;
    delete lbl;
    for(int i = 0; i < btn.size(); i++)
    {
        for(int j = 0; j < btn.size(); i++)
        {
            delete btn[i][j];
        }
    }
}
void Widget::ClearBoard()
{
    for(int i = 0; i < btn.size(); i++)
    {
        for(int j = 0; j < btn[i].size(); j++)
        {
            btn[i][j]->setText("");
        }
    }
    if(lbl->text() == "Player 1")
    {
        lbl->setText("Player 2");
    }
    else
    {
        lbl->setText("Player 1");
    }
    buttonschecked = 0;
}
void Widget::TicTacButtons()
{
    QPushButton* button = (QPushButton*)sender();
    if(button->text() == "")
    {
        if(lbl->text() == "Player 1")
        {
            button->setText("X");
            lbl->setText("Player 2");
        }
        else
        {
            button->setText("O");
            lbl->setText("Player 1");
        }
        buttonschecked++;
        CheckWin();
        emit startAI(button);
    }
}
void Widget::AI(QPushButton* checkbtn)
{
    int iweight = -100, jweight = 1, btniweight, btnjweight;
    if(buttonschecked != btn.size() * btn.size())
    {
        for(int i = 0; i < btn.size(); i++)
        {
            for(int j = 0; j < btn[i].size(); j++)
            {
                if(checkbtn == btn[i][j])
                {
                      btniweight = i;
                      btnjweight = j;
                      break;
                }
            }
        }
        for(int i = 0; i < btn.size(); i++)
        {
            for(int j = 0; j < btn[i].size(); j++)
            {
                if((btn[i][j] != checkbtn) && (btn[i][j]->text() == "") && ((btniweight * btnjweight) - (iweight * jweight) > (btniweight * btnjweight) - (i * j)))
                {
                      iweight = i;
                      jweight = j;
                }
            }
        }
        if(lbl->text() == "Player 2")
        {
            btn[iweight][jweight]->setText("O");
            lbl->setText("Player 1");
        }
        else
        {
            btn[iweight][jweight]->setText("X");
            lbl->setText("Player 2");
        }
        buttonschecked++;
    }
    CheckWin();
    if(winner != "")
    {
        WinDialogue();
    }
}
QString Widget::CheckWin()
{
    QString TicTac = btn[0][0]->text();
    bool whowins = 1;
    for(int i = 0; i < btn.size(); i++)
    {
        if(btn[i][i]->text() != TicTac || TicTac == "")
        {
            whowins = 0;
            break;
        }
    }
    if(whowins == 1)
    {
        winner = TicTac;
        return winner;
    }
    whowins = 1;
    TicTac = btn[0][btn.size() - 1]->text();
    for(int i = 0, j = btn.size() - 1; i < btn.size(); i++, j--)
    {
        if(btn[i][j]->text() != TicTac || TicTac == "")
        {
            whowins = 0;
            break;
        }
    }
    if(whowins == 1)
    {
        winner = TicTac;
        return winner;
    }
    for(int i = 0; i < btn.size(); i++)
    {
        whowins = 1;
        TicTac = btn[i][0]->text();
        for(int j = 1; j < btn.size(); j++)
        {
            if(btn[i][j]->text() != TicTac || TicTac == "")
            {
                whowins = 0;
                break;
            }
        }
        if(whowins == 1)
        {
            winner = TicTac;
            return winner;
        }
    }
    for(int i = 0; i < btn.size(); i++)
    {
        whowins = 1;
        TicTac = btn[0][i]->text();
        for(int j = 1; j < btn.size(); j++)
        {
            if(btn[j][i]->text() != TicTac || TicTac == "")
            {
                whowins = 0;
                break;
            }
        }
        if(whowins == 1)
        {
            winner = TicTac;
            return winner;
        }
    }
    if(buttonschecked == btn.size() * btn.size())
    {
        winner = "-";
    }
    return winner;
}
void Widget::WinDialogue()
{
    if(winner == "X")
    {
        (new WinnerTicTac("Player 1 wins!"))->show();
    }
    else if(winner == "O")
    {
        (new WinnerTicTac("Player 2 wins!"))->show();
    }
    else
    {
        (new WinnerTicTac("A Draw!"))->show();
    }
    this->setEnabled(false);
    //this->close();
}

WinnerTicTac::WinnerTicTac(QString winnertext, QWidget* parent) : QWidget(parent)
  , ui1(new Ui::WinnerTicTac)
{
    ui1->setupUi(this);
    this->setWindowTitle("Tic-Tac-Toe");
    ui1->label->setText(winnertext);
    connect(ui1->pushButton,SIGNAL(clicked()),this,SLOT(close()));
}
WinnerTicTac::~WinnerTicTac()
{
    delete ui1;
}
