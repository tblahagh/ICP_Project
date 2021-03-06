#include "busstopdetailview.h"

//**************************************************************************
// konstruktory, destruktory
//--------------------------------------------------------------------------

// ---------------------------------------------------------------
// Základní konstruktor
BusStopDetailView::BusStopDetailView(BusStopView* _busStopView, MainWindow* _mainWindow, QWidget *parent) : QWidget(parent)
{
    if(_busStopView == NULL || _mainWindow == NULL) throw new QString("Nepodařilo se vytvořit detail zastávky");

    this->busStopView = _busStopView;
    this->mainWindow = _mainWindow;

    this->busStopView->open();
    this->mainWindow->mapUpdate();

}

//------------------------------------------------------------------
// Destruktor
BusStopDetailView::~BusStopDetailView(){
    if(layout != NULL) delete layout;
    this->busStopView->close();
    this->mainWindow->mapUpdate();
}

//********************************************************************************
// metody pro vykreslení
//--------------------------------------------------------------------------------

//-------------------------------------------------------------------
// Metoda vykreslí detail do widgetu
void BusStopDetailView::paint(QWidget *widget){

    if(widget == NULL) throw new QString("Nepodařilo se vykreslit detail zastávky");

    if(layout != NULL) delete layout;

    layout = new QGridLayout();

    QLabel *title = new QLabel(QString("Zastávka: "+busStopView->getBusStopModel()->getName()));
    title->setFont(QFont("Tahoma", 12, QFont::Bold));
    layout->addWidget(title, 1, 1, 1, 4);

    btnClose = new QPushButton(tr("Zavřít"));
    layout->addWidget(btnClose, 2, 2, 1, 3);

    widget->setLayout(layout);


    connect(btnClose, SIGNAL(clicked()), this, SLOT(btnCloseClicked()));
}

//*************************************************************************************
// metody pro interakci s uživatelem
//------------------------------------------------------------------------------------

//------------------------------------------------------------------
// Metoda zavření detailu
void BusStopDetailView::btnCloseClicked(){

    try{
        mainWindow->closeDetail();
    }
    catch(const QString *exc){ mainWindow->showException(exc); }
}
