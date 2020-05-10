/*
 * Autor: Vojtěch Wawreczka
 * Datum: 9.5.2020
 * */
#include "detourdetailview.h"

//**********************************************************************************
// konstruktory, destruktory, tisk
//------------------------------------------------------------------------------------

//-----------------------------------------------------------
// Základní konstruktor
DetourDetailView::DetourDetailView(StreetView* _streetView, MainWindow* _mainWindow, QWidget *parent) : QWidget(parent)
{
    if(_streetView == NULL || _mainWindow == NULL) throw new QString("Nepodařilo se vytvořit detail objížďky");

    this->streetView = _streetView;
    this->mainWindow = _mainWindow;

    this->streetView->open();
    this->mainWindow->mapUpdate();

    this->path = new PathModel();
    if(streetView->getStreetModel()->GetDetour() != NULL){

        for(StreetModel* model: streetView->getStreetModel()->GetDetour()->getStreets()){
            path->addStreet(model);
        }
    }
}

//------------------------------------------------------------
// Destruktor
DetourDetailView::~DetourDetailView(){
    if(layout != NULL) delete layout;
    if(path != NULL && path != streetView->getStreetModel()->GetDetour()) delete path;
}

//********************************************************************************
// metody get, set add
//-------------------------------------------------------------------------------

//---------------------------------------------------------------
// Metoda přidá ulici do objížďky
void DetourDetailView::addStreet(StreetModel *street){

    if(street == NULL) throw new QString("Nebyl vybrán žádný model ulice");

    path->addStreet(street);
}

//---------------------------------------------------------------
// Metoda smaže všechny ulice z objížďky
void DetourDetailView::clearStreets(){

    if(path != NULL && path != streetView->getStreetModel()->GetDetour()) delete path;
    path = new PathModel();
}

//********************************************************************************
// metody pro vykreslení
//---------------------------------------------------------------------------------

//--------------------------------------------------------------
// Metoda vykreslí objížďku na widget
void DetourDetailView::paint(QWidget *widget){

    if(widget == NULL) throw new QString("Nepodařilo se vykreslit detail objížďky");

    if(layout != NULL) delete layout;

    layout = new QGridLayout();

    QLabel *title = new QLabel(QString("Ulice: "+streetView->getStreetModel()->getName()));
    title->setFont(QFont("Tahoma", 12, QFont::Bold));
    layout->addWidget(title, 1, 1, 1, 5);

    QLabel *labelDelay = new QLabel("Zpoždění: \n(v minutách)");
    fieldDelay = new QLineEdit(QString::number(streetView->getStreetModel()->GetDelay()));
    layout->addWidget(labelDelay, 2, 1);
    layout->addWidget(fieldDelay, 2, 2, 1, 4);

    QLabel *labelPath = new QLabel("Objížďka: ");
    labelPathInfo = new QLabel("Trasa je nekompletní.\nVyberte ulice kliknutím do mapy");
    layout->addWidget(labelPath, 3, 1);
    layout->addWidget(labelPathInfo, 3, 2, 1, 4);

    int i = 4;

    for(StreetModel* street: path->getStreets()){
        QLabel *labelStreet = new QLabel(QString::number(street->getId()));
        if(street->getName().size() > 0) labelStreet->setText(street->getName());
        layout->addWidget(labelStreet, i++, 2, 1, 4);
    }

    if(path->getStreets().size() > 0
            && streetView->getStreetModel()->ContainsEndPoint(path->getStartPosition())
            && streetView->getStreetModel()->ContainsEndPoint(path->getEndPosition())
            && path->getStartPosition() != path->getEndPosition()){
        labelPathInfo->setText("Trasa je kompletní.");
        labelPathInfo->setStyleSheet("color : green;");
    }

    btnSave = new QPushButton("Uložit");
    layout->addWidget(btnSave, i, 2, 1, 2);
    btnClear = new QPushButton("Vyčistit");
    layout->addWidget(btnClear, i++, 4, 1, 2);

    btnClose = new QPushButton("Zavřít");
    layout->addWidget(btnClose, i, 2, 1, 4);


    widget->setLayout(layout);

    connect(btnSave, SIGNAL(clicked()), this, SLOT(btnSaveClicked()));
    connect(btnClear, SIGNAL(clicked()), this, SLOT(btnClearClicked()));
    connect(btnClose, SIGNAL(clicked()), this, SLOT(btnCloseClicked()));

}

//**********************************************************************************
// metody pro interakci s uživatelem
//----------------------------------------------------------------------------------

//-----------------------------------------------------------
// Metoda volaná při stisku tlačítka zavře detail objížďky
void DetourDetailView::btnCloseClicked(){

    try{
        mainWindow->openStreetDetail(streetView);
    }
    catch(const QString *exc){ mainWindow->showException(exc); }
}

//----------------------------------------------------------
// Metoda volaná při stisku tlačítka smaže stav objížďky
void DetourDetailView::btnClearClicked(){

    try{

        mainWindow->deselectStreetsOnDetour();

    }
    catch(const QString *exc){ mainWindow->showException(exc); }
}
//-----------------------------------------------------------
// Metoda volaná při stisku tlačítka uloží stav objížďky
void DetourDetailView::btnSaveClicked(){
    int delay = QString(fieldDelay->text()).toInt();

    try{
        streetView->getStreetModel()->SetDelay(delay);
        streetView->getStreetModel()->SetDetour(path);
    }
    catch(const QString *exc){ mainWindow->showException(exc); }


}
