#include "clockdetailview.h"

//****************************************************************************
// konstuktory a destruktory
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// konstuktor - vytvoření detailu
ClockDetailView::ClockDetailView(ClockModel* _clockModel, MainWindow* _mainWindow, QWidget *parent) : QWidget(parent)
{
    if(_clockModel == NULL || _mainWindow == NULL) throw new QString("Nepodařilo se vytvořit detail hodin");

    this->clockModel = _clockModel;
    this->mainWindow = _mainWindow;

}

//----------------------------------------------------------------------------
// destruktor
ClockDetailView::~ClockDetailView(){
    if(layout != NULL) delete layout;
}

//****************************************************************************
// metody pro vykreslení
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// vykreslení detailu
void ClockDetailView::paint(QWidget *widget){

    if(widget == NULL) throw new QString("Nepodařilo se vykreslit detail hodin");

    if(layout != NULL) delete layout;

    layout = new QGridLayout();

    QLabel *title = new QLabel("Upravit hodiny");
    title->setFont(QFont("Tahoma", 12, QFont::Bold));
    layout->addWidget(title, 1, 1, 1, 7);

    fieldHour = new QLineEdit();
    fieldMinute = new QLineEdit();
    fieldSecond = new QLineEdit();

    QLabel *labelHour = new QLabel("Hodina: ");
    QLabel *labelMinute = new QLabel("Minuta: ");
    QLabel *labelSecond = new QLabel("Sekunda: ");

    layout->addWidget(labelHour, 2, 1, 1, 2);
    layout->addWidget(labelMinute, 3, 1, 1, 2);
    layout->addWidget(labelSecond, 4, 1, 1, 2);
    layout->addWidget(fieldHour, 2, 3, 1, 5);
    layout->addWidget(fieldMinute, 3, 3, 1, 5);
    layout->addWidget(fieldSecond, 4, 3, 1, 5);

    btnInit = new QPushButton(tr("Inicializovat"));
    layout->addWidget(btnInit, 5, 3, 1, 5);

    fieldSpeed = new QLineEdit();
    QLabel *labelSpeed = new QLabel("Rychlost: ");
    layout->addWidget(labelSpeed, 6, 1, 1, 2);
    layout->addWidget(fieldSpeed, 6, 3, 1, 5);

    btnSpeed = new QPushButton(tr("Upravit rychlost"));
    layout->addWidget(btnSpeed, 7, 3, 1, 5);

    btnClose = new QPushButton(tr("Zavřít"));
    layout->addWidget(btnClose, 8, 3, 1, 5);

    fieldHour->setText(QString::number(clockModel->getHour()));
    fieldMinute->setText(QString::number(clockModel->getMinute()));
    fieldSecond->setText(QString::number(clockModel->getSecond()));
    fieldSpeed->setText(QString::number(clockModel->getSpeed()));

    widget->setLayout(layout);


    connect(btnInit, SIGNAL(clicked()), this, SLOT(btnInitClicked()));
    connect(btnSpeed, SIGNAL(clicked()), this, SLOT(btnSpeedClicked()));
    connect(btnClose, SIGNAL(clicked()), this, SLOT(btnCloseClicked()));
}

//****************************************************************************
// metody pro interakce s uživatelem
//---------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// kliknutí na inicializaci hodin
void ClockDetailView::btnInitClicked(){

    try{
        int hour = QString(fieldHour->text()).toInt();
        int minute = QString(fieldMinute->text()).toInt();
        int second = QString(fieldSecond->text()).toInt();

        clockModel->initialize(hour, minute, second);
        mainWindow->clockInitialized();
    }
    catch(const QString *exc){ mainWindow->showException(exc); }

}

//--------------------------------------------------------------------------------
// kliknutí na uložení rychlosti
void ClockDetailView::btnSpeedClicked(){

    try{
        int speed = QString(fieldSpeed->text()).toInt();
        clockModel->setSpeed(speed);
    }
    catch(const QString *exc){ mainWindow->showException(exc); }
}

//-------------------------------------------------------------------------------
// kliknutí na zavřít
void ClockDetailView::btnCloseClicked(){

    try{
        mainWindow->closeDetail();
    }
    catch(const QString *exc){ mainWindow->showException(exc); }
}
