#include "bookstore.h"

Bookstore::Bookstore(Bookstoremodel* mvcmodel, QWidget *parent)
    : QWidget(parent), model(mvcmodel)
{
    resize(387, 500);
    QGridLayout* layout;
    QTabWidget* tabs = new QTabWidget;
    QWidget *findbooks = new QWidget, *addbook = new QWidget;
    layout = new QGridLayout(findbooks);
    QPushButton* checkbtn = new QPushButton("Вывести список");
    QLabel* minmaxlabel = new QLabel("Нижний порог цены (не более 2000000000 рублей):");
    QLineEdit* minmaxedit = new QLineEdit;
    minmaxedit->setValidator(new QIntValidator(0, 2000000000));
    layout->addWidget(minmaxlabel, 0, 0);
    layout->addWidget(minmaxedit, 0, 1);
    connect(minmaxedit, SIGNAL(textEdited(const QString&)), this, SLOT(NotifyMinPriceChange(const QString&)));
    minmaxlabel = new QLabel("Верхний порог цены (не более 2000000000 рублей):");
    minmaxedit = new QLineEdit;
    minmaxedit->setValidator(new QIntValidator(0, 2000000000));
    layout->addWidget(minmaxlabel, 1, 0);
    layout->addWidget(minmaxedit, 1, 1);
    layout->addWidget(checkbtn, 2, 0, 2, 0);
    connect(minmaxedit, SIGNAL(textEdited(const QString&)), this, SLOT(NotifyMaxPriceChange(const QString&)));
    connect(checkbtn, SIGNAL(clicked()), this, SLOT(NotifyCheck()));
    layout = new QGridLayout(addbook);
    checkbtn = new QPushButton("Добавить книгу");
    connect(checkbtn, SIGNAL(clicked()), this, SLOT(NotifyAdd()));
    minmaxlabel = new QLabel("Название книги:");
    minmaxedit = new QLineEdit;
    connect(minmaxedit, SIGNAL(textEdited(const QString&)), this, SLOT(NotifyBookNameChange(const QString&)));
    minmaxedit->setValidator(new QRegularExpressionValidator(QRegularExpression("[^;]+")));
    layout->addWidget(minmaxlabel, 1, 0);
    layout->addWidget(minmaxedit, 1, 1);
    minmaxlabel = new QLabel("Имя автора:");
    minmaxedit = new QLineEdit;
    connect(minmaxedit, SIGNAL(textEdited(const QString&)), this, SLOT(NotifyAuthorNameChange(const QString&)));
    minmaxedit->setValidator(new QRegularExpressionValidator(QRegularExpression("[^;]+")));
    layout->addWidget(minmaxlabel, 2, 0);
    layout->addWidget(minmaxedit, 2, 1);
    minmaxlabel = new QLabel("Год издания:");
    minmaxedit = new QLineEdit;
    connect(minmaxedit, SIGNAL(textEdited(const QString&)), this, SLOT(NotifyYearChange(const QString&)));
    minmaxedit->setValidator(new QIntValidator(0, 2000000000));
    layout->addWidget(minmaxlabel, 3, 0);
    layout->addWidget(minmaxedit, 3, 1);
    minmaxlabel = new QLabel("Цена (в рублях):");
    minmaxedit = new QLineEdit;
    connect(minmaxedit, SIGNAL(textEdited(const QString&)), this, SLOT(NotifyCostChange(const QString&)));
    minmaxedit->setValidator(new QIntValidator(0, 2000000000));
    layout->addWidget(minmaxlabel, 4, 0);
    layout->addWidget(minmaxedit, 4, 1);
    layout->addWidget(checkbtn, 5, 0, 2, 0);

    tabs->addTab(model->GetBooksTable(), "Список книг");
    tabs->addTab(findbooks, "Найти книги по цене");
    tabs->addTab(addbook, "Добавить книгу");
    layout = new QGridLayout(this);
    layout->addWidget(tabs);
}
void Bookstore::NotifyMinPriceChange(const QString& text)
{
    emit SignalMinPriceChange(text);
}
void Bookstore::NotifyMaxPriceChange(const QString& text)
{
    emit SignalMaxPriceChange(text);
}
void Bookstore::NotifyCheck()
{
    emit SignalCheck();
}
void Bookstore::DisplayTable(QTableWidget* pricebooktable)
{
    if(pricebooktable->rowCount() == 0)
    {
        QMessageBox::warning(0, "Ошибка", "Книги в заданном ценовом диапазоне отсутствуют!");
        return;
    }
    pricebooktable->show();
}
void Bookstore::NotifyBookNameChange(const QString& text)
{
    emit SignalBookNameChange(text);
}
void Bookstore::NotifyAuthorNameChange(const QString& text)
{
    emit SignalAuthorNameChange(text);
}
void Bookstore::NotifyYearChange(const QString& text)
{
    emit SignalYearChange(text);
}
void Bookstore::NotifyCostChange(const QString& text)
{
    emit SignalCostChange(text);
}
void Bookstore::NotifyAdd()
{
    emit SignalAdd();
}

Bookstorecontroller::Bookstorecontroller(Bookstoremodel* mvcmodel) : model(mvcmodel){}
void Bookstorecontroller::ChangeModelMinPrice(const QString& text)
{
    int mn;
    if(text == "")
    {
        mn = -1;
    }
    else
    {
        mn = text.toInt();
    }
    model->SetMinPrice(mn);
}
void Bookstorecontroller::ChangeModelMaxPrice(const QString& text)
{
    int mx;
    if(text == "")
    {
        mx = -1;
    }
    else
    {
        mx = text.toInt();
    }
    model->SetMaxPrice(mx);
}
void Bookstorecontroller::CheckPrices()
{
    if(model->GetMinPrice() == -1 || model->GetMaxPrice() == -1)
    {
        QMessageBox::warning(0, "Ошибка", "Введите весь диапозон!");
        return;
    }
    if(model->GetMinPrice() > model->GetMaxPrice())
    {
        QMessageBox::warning(0, "Ошибка", "Минимальная цена должна быть не больше максимальной!");
        return;
    }
    QTableWidget* pricerange = new QTableWidget, *checkingtable = model->GetBooksTable();
    pricerange->setColumnCount(checkingtable->columnCount());
    pricerange->setEditTriggers(QAbstractItemView::NoEditTriggers);
    pricerange->verticalHeader()->hide();
    for(int i = 0; i < checkingtable->columnCount(); i++)
    {
        pricerange->setHorizontalHeaderItem(i, new QTableWidgetItem(checkingtable->horizontalHeaderItem(i)->text()));
    }
    for(int i = 0; i < checkingtable->rowCount(); i++)
    {
        if(checkingtable->item(i, 3)->text().toInt() >= model->GetMinPrice() && checkingtable->item(i, 3)->text().toInt() <= model->GetMaxPrice())
        {
            pricerange->insertRow(pricerange->rowCount());
            pricerange->setItem(pricerange->rowCount() - 1, 0, new QTableWidgetItem(checkingtable->item(i, 0)->text()));
            pricerange->setItem(pricerange->rowCount() - 1, 1, new QTableWidgetItem(checkingtable->item(i, 1)->text()));
            pricerange->setItem(pricerange->rowCount() - 1, 2, new QTableWidgetItem(checkingtable->item(i, 2)->text()));
            pricerange->setItem(pricerange->rowCount() - 1, 3, new QTableWidgetItem(checkingtable->item(i, 3)->text()));
        }
    }
    pricerange->adjustSize();
    emit TableReady(pricerange);
}

void Bookstorecontroller::BookNameChange(const QString& text)
{
    model->SetBookName(text);
}
void Bookstorecontroller::AuthorNameChange(const QString& text)
{
    model->SetAuthorName(text);
}
void Bookstorecontroller::YearChange(const QString& text)
{
    int y;
    if(text == "")
    {
        y = -1;
    }
    else
    {
        y = text.toInt();
    }
    model->SetYear(y);
}
void Bookstorecontroller::CostChange(const QString& text)
{
    int c;
    if(text == "")
    {
        c = -1;
    }
    else
    {
        c = text.toInt();
    }
    model->SetCost(c);
}
void Bookstorecontroller::AddBook()
{
    if(model->GetYear() == -1 || model->GetCost() == -1 || model->GetAuthorName() == "" || model->GetBookName() == "")
    {
        QMessageBox::warning(0, "Ошибка", "Одно из полей не заполнено!");
        return;
    }
    model->GetBooksTable()->insertRow(model->GetBooksTable()->rowCount());
    QTableWidgetItem* itm = new SortingItem;
    itm->setText(model->GetBookName());
    model->GetBooksTable()->setItem(model->GetBooksTable()->rowCount() - 1, 0, itm);
    itm = new SortingItem;
    itm->setText(model->GetAuthorName());
    model->GetBooksTable()->setItem(model->GetBooksTable()->rowCount() - 1, 1, itm);
    itm = new SortingItem;
    itm->setText(QString::number(model->GetYear()));
    model->GetBooksTable()->setItem(model->GetBooksTable()->rowCount() - 1, 2, itm);
    itm = new SortingItem;
    itm->setText(QString::number(model->GetCost()));
    model->GetBooksTable()->setItem(model->GetBooksTable()->rowCount() - 1, 3, itm);
    model->GetBooksTable()->sortByColumn(2, Qt::AscendingOrder);
    model->GetBooksTable()->resizeColumnsToContents();
    model->FileUpdate();
}

