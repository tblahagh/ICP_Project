#include "busdetailview.h"
#include "src/TimeLib.h"

//**************************************************************************
// konstruktory, destruktory a tisk
//--------------------------------------------------------------------------

// ---------------------------------------------------------------
// konstruktor
BusDetailView::BusDetailView(BusView* _busView, MainWindow* _mainWindow, QWidget *parent) : QWidget(parent)
{
    if(_busView == NULL || _mainWindow == NULL) throw new QString("Nepodařilo se vytvořit detail autobusu");

    this->busView = _busView;
    this->mainWindow = _mainWindow;

    this->busView->open();
    this->mainWindow->mapUpdate();


}

//------------------------------------------------------------------
// destruktor
BusDetailView::~BusDetailView(){
    if(layout != NULL) delete layout;
    this->busView->close();
    this->mainWindow->mapUpdate();
}

BusView* BusDetailView::getBusView(){
    return this->busView;
}

//********************************************************************************
// metody pro vykreslení
//--------------------------------------------------------------------------------

//-------------------------------------------------------------------
// vykreslení
void BusDetailView::paint(QWidget *widget){

    if(widget == NULL) throw new QString("Nepodařilo se vykreslit detail autobusu");

    if(layout != NULL) delete layout;

    layout = new QGridLayout();

    QLabel *title = new QLabel(QString("Linka: "+busView->getBusModel()->getBusLine()->getName()));
    title->setFont(QFont("Tahoma", 12, QFont::Bold));
    layout->addWidget(title, 1, 1, 1, 4);

    int i = 0;
    int sec = TimeToSeconds(busView->getBusModel()->getStartTime());
    bool crossed = true;

    for(BusStopModel* busStop: busView->getBusModel()->getBusLine()->getBusStops()){

        sec += busView->getBusModel()->getBusLine()->getTimes().at(i)*60;
        tm time = SecondsToTime(sec);

        QLabel *arrive = new QLabel(QString(timeNumberToStr(time.tm_hour)) + ":" + QString(timeNumberToStr(time.tm_min)));
        layout->addWidget(arrive, i+2, 1);

        QLabel *stop = new QLabel(QString(busStop->getName()));
        layout->addWidget(stop, i+2, 2, 1, 3);

        if(!crossed){}
        else if(i == busView->getBusModel()->getNextStopIndex()){
            crossed = false;
            arrive->setStyleSheet("font-weight: bold;");
            stop->setStyleSheet("font-weight: bold;");

        }
        else{
            arrive->setStyleSheet("color: grey;");
            stop->setStyleSheet("color: grey;");
        }


        i++;
    }

    btnClose = new QPushButton(tr("Zavřít"));
    layout->addWidget(btnClose, i+2, 2, 1, 3);

    widget->setLayout(layout);


    connect(btnClose, SIGNAL(clicked()), this, SLOT(btnCloseClicked()));
}

//*************************************************************************************
// metody pro interakci s uživatelem
//------------------------------------------------------------------------------------

//------------------------------------------------------------------
// kliknutí na tlačítko zavřít
void BusDetailView::btnCloseClicked(){

    try{
        mainWindow->closeDetail();
    }
    catch(const QString *exc){ mainWindow->showException(exc); }
}
