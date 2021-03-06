#include "streetdetailview.h"

//**************************************************************************
// konstruktory, destruktory
//--------------------------------------------------------------------------

// ---------------------------------------------------------------
// Základní konstruktor
StreetDetailView::StreetDetailView(StreetView* _streetView, MainWindow* _mainWindow, QWidget *parent) : QWidget(parent)
{
    if(_streetView == NULL || _mainWindow == NULL) throw new QString("Nepodařilo se vytvořit detail ulice");

    this->streetView = _streetView;
    this->mainWindow = _mainWindow;

    this->streetView->open();
    this->mainWindow->mapUpdate();

}

//------------------------------------------------------------------
// Destruktor
StreetDetailView::~StreetDetailView(){
    if(layout != NULL) delete layout;
    this->streetView->close();
    this->mainWindow->mapUpdate();
}

//********************************************************************************
// metody pro vykreslení
//--------------------------------------------------------------------------------

//-------------------------------------------------------------------
// Metoda vykreslí objížďku na widget
void StreetDetailView::paint(QWidget *widget){

    if(widget == NULL) throw new QString("Nepodařilo se vykreslit detail ulice");

    if(layout != NULL) delete layout;

    layout = new QGridLayout();

    QLabel *title = new QLabel(QString("Ulice: "+streetView->getStreetModel()->getName()));
    title->setFont(QFont("Tahoma", 12, QFont::Bold));
    layout->addWidget(title, 1, 1, 1, 4);

    QLabel *labelTraffic = new QLabel("Provoz: ");
    btnGreen = new QRadioButton("Plynulý", this);
    btnOrange = new QRadioButton("Střední", this);
    btnRed = new QRadioButton("Hustý", this);
    btnBlack = new QRadioButton("Uzavřeno", this);

    fieldTraffic = new QButtonGroup();

    layout->addWidget(labelTraffic, 2, 1);
    layout->addWidget(btnGreen, 2, 2, 1, 3);
    layout->addWidget(btnOrange, 3, 2, 1, 3);
    layout->addWidget(btnRed, 4, 2, 1, 3);
    layout->addWidget(btnBlack, 5, 2, 1, 3);

    fieldTraffic->addButton(btnGreen, 3);
    fieldTraffic->addButton(btnOrange, 2);
    fieldTraffic->addButton(btnRed, 1);
    fieldTraffic->addButton(btnBlack, 0);

    int i = 6;
    if(streetView->getStreetModel()->GetTraffic() == 0){
        QLabel *labelDetour = new QLabel("Objížďka: ");
        QPushButton *btnDetourDetail = new QPushButton("Detail");

        layout->addWidget(labelDetour, 6, 1);
        layout->addWidget(btnDetourDetail, 6, 2, 1, 3);

        connect(btnDetourDetail, SIGNAL(clicked()), this, SLOT(btnDetourDetailClicked()));
        i = 7;
    }

    btnSave = new QPushButton("Uložit");
    layout->addWidget(btnSave, i, 2, 1, 3);

    btnClose = new QPushButton(tr("Zavřít"));
    layout->addWidget(btnClose, ++i, 2, 1, 3);

    fieldTraffic->button(streetView->getStreetModel()->GetTraffic())->setChecked(true);

    widget->setLayout(layout);


    connect(btnSave, SIGNAL(clicked()), this, SLOT(btnSaveClicked()));
    connect(btnClose, SIGNAL(clicked()), this, SLOT(btnCloseClicked()));
}

//*************************************************************************************
// metody pro interakci s uživatelem
//------------------------------------------------------------------------------------

//------------------------------------------------------------------
// Metoda volaná při stisku tlačítka uloží stav ulice
void StreetDetailView::btnSaveClicked(){
    int traffic = fieldTraffic->checkedId();

    try{
        streetView->getStreetModel()->SetTraffic(traffic);
        this->mainWindow->mapUpdate();
        this->mainWindow->updateDetail();
    }
    catch(const QString *exc){ mainWindow->showException(exc); }
}

//------------------------------------------------------------------
// Metoda volaná při stisku tlačítka zavře detail ulice
void StreetDetailView::btnCloseClicked(){

    try{
        mainWindow->closeDetail();
    }
    catch(const QString *exc){ mainWindow->showException(exc); }
}

//-----------------------------------------------------------------
// Metoda volaná při stisku tlačítka otevře detail objížďky ulice
void StreetDetailView::btnDetourDetailClicked(){

    try{
        mainWindow->openDetourDetail(streetView);
    }
    catch(const QString *exc){ mainWindow->showException(exc); }
}
