#include "mainwindow.h"

//********************************************************************************
// kostruktory a destruktory
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
// konstruktor - vykreslení okna
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{

    resize(920,540);
    setWindowTitle("ICP Projekt");

    // umístění do středu
    central = new QWidget(this);
    setCentralWidget(central);

    // hbox
    layout = new QHBoxLayout();
    central->setLayout(layout);

    // vbox pro nastaveni a detaily
    QWidget *w = new QWidget();
    w->setMaximumWidth(300);
    w->setMinimumWidth(300);
    layout->addWidget(w);

    vbox = new QVBoxLayout();
    w->setLayout(vbox);

    // hbox pro hodiny a zoom
    QWidget *w2 = new QWidget();
    vbox->addWidget(w2);

    QHBoxLayout *hbox = new QHBoxLayout();
    w2->setLayout(hbox);

    // scroll area pro mapu
    scroll = new QScrollArea();
    scroll->setWidgetResizable(true);
    scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    layout->addWidget(scroll);

    // načtení a zobrazení mapy
    try{
        creator = new MapCreator();
        mapModel = creator->CreateMap("C:/Qt/projects/icp-project/ICP_Project/karvina.xml", this);

        mapView = new MapView(mapModel, this);

        scrollWidget = new QWidget();
        scrollWidget->setContentsMargins(0,0,0,0);
        scrollWidget->setMinimumSize(mapModel->getWidth()*mapView->getZoom()+2*mapView->getOffset()+20,mapModel->getHeight()*mapView->getZoom()+2*mapView->getOffset()+20);

        QVBoxLayout *vb = new QVBoxLayout;
        scrollWidget->setLayout(vb);

        vb->addWidget(mapView);

        scroll->setWidget(scrollWidget);

    }
    catch(const QString *exc){
        showException(exc);
    }

    // načtení a zobrazení hodin
    try{
        clockModel = new ClockModel();
        clockInitialized();

        clockView = new ClockView(clockModel, this);

        btnClockEdit = new QPushButton(tr("Upravit hodiny"));
        hbox->addWidget(btnClockEdit);
        connect(btnClockEdit, SIGNAL(clicked()), this, SLOT(openClockDetail()));

        labelClock = new QLabel(this);
        labelClock->setText(QString(clockModel->getString()));
        labelClock->setFont(QFont("Arial", 10, QFont::Bold));
        labelClock->setFixedWidth(100);
        hbox->addWidget(labelClock);
    }
    catch(const QString *exc){
        showException(exc);
    }

    // zobrazení tlačítek pro zoom
    btnZoomPlus = new QPushButton(tr("+"));
    btnZoomMinus = new QPushButton(tr("-"));
    btnZoomPlus->setFixedSize(25, 25);
    btnZoomMinus->setFixedSize(25, 25);
    hbox->addWidget(btnZoomPlus);
    hbox->addWidget(btnZoomMinus);

    connect(btnZoomPlus, SIGNAL(clicked()), this, SLOT(increaseMapZoom()));
    connect(btnZoomMinus, SIGNAL(clicked()), this, SLOT(decreaseMapZoom()));

    // prostor pro nastavení
    widget = new QWidget();
    //widget->setSizePolicy(QSizePolicy ::Minimum , QSizePolicy ::Expanding);
    vbox->addWidget(widget);

    // pomocny widget
    QWidget *help = new QWidget();
    help->setSizePolicy(QSizePolicy ::Minimum , QSizePolicy ::Expanding);
    vbox->addWidget(help);


    // widget pro hlašení chyb
    exceptionLabel = new QLabel();
    exceptionLabel->setStyleSheet("color: red;");
    exceptionLabel->setFixedWidth(300);
    vbox->addWidget(exceptionLabel);


}

//---------------------------------------------------------------------------
// destruktor
MainWindow::~MainWindow()
{
        if (central != NULL) { delete central; }
        if (mapModel != NULL) { delete mapModel; }
        if (creator != NULL) { delete creator; }
        if (clockModel != NULL) { delete clockModel; }
        if (clockDetailView != NULL) { delete clockDetailView; }
        if (streetDetailView != NULL) { delete streetDetailView; }
        if (detourDetailView != NULL) { delete detourDetailView; }
        if (busStopDetailView != NULL) { delete busStopDetailView; }
        if (busDetailView != NULL) { delete busDetailView; }
}

//********************************************************************************
// práce s mapou
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
// znovu načte zobrazení mapy
void MainWindow::mapUpdate(){
    mapView->update();
}

//--------------------------------------------------------------------------------
// zvýší zoom
void MainWindow::increaseMapZoom(){
    mapView->increaseZoom();
    mapView->update();
    scrollWidget->setMinimumSize(mapModel->getWidth()*mapView->getZoom()+2*mapView->getOffset()+20,mapModel->getHeight()*mapView->getZoom()+2*mapView->getOffset()+20);
}

//--------------------------------------------------------------------------------
// sníží zoom
void MainWindow::decreaseMapZoom(){
    mapView->decreaseZoom();
    mapView->update();
    scrollWidget->setMinimumSize(mapModel->getWidth()*mapView->getZoom()+2*mapView->getOffset()+20,mapModel->getHeight()*mapView->getZoom()+2*mapView->getOffset()+20);
}

//********************************************************************************
// práce s hodinami
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
// zobrazí nový čas na hodinách po tiknutí
void MainWindow::clockTicked(){
    labelClock->setText(clockModel->getString());
    mapModel->actualizeBuses(clockModel);
    mapView->loadBuses();
    mapUpdate();

    if(busDetailView != NULL) updateDetail();
}

//-------------------------------------------------------------------------------
// provede akce po inicializaci hodin
void MainWindow::clockInitialized(){
    mapModel->loadBuses(clockModel);
    mapView->loadBuses();
    mapUpdate();

    if(busDetailView != NULL) closeDetail();
}


//********************************************************************************
// práce s detaily
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
// otevře detail hodin
void MainWindow::openClockDetail(){

    try{
        closeDetail();
        clockDetailView = new ClockDetailView(clockModel, this);
        clockDetailView->paint(widget);
    }
    catch(const QString *exc){
        showException(exc);
    }
}

//--------------------------------------------------------------------------------
// otevře detail ulice
void MainWindow::openStreetDetail(StreetView *street){

    try{
        closeDetail();
        streetDetailView = new StreetDetailView(street, this);
        streetDetailView->paint(widget);
    }
    catch(const QString *exc){
        showException(exc);
    }
}

//---------------------------------------------------------------------------------
// otevře detail objížďky
void MainWindow::openDetourDetail(StreetView *street){

    try{
        closeDetail();
        detourDetailView = new DetourDetailView(street, this);
        detourDetailView->paint(widget);

        mapView->setMode(1);
        if(street->getStreetModel()->GetDetour() != NULL){
            mapView->selectPath(street->getStreetModel()->GetDetour());
        }
        mapUpdate();
    }
    catch(const QString *exc){
        showException(exc);
    }
}

//---------------------------------------------------------------------------------
// vybere ulici pro objizdku
void MainWindow::selectStreetOnDetour(StreetView *street){

    if(street == NULL) throw new QString("Nebyla vybrána žádná ulice");
    if(detourDetailView == NULL) throw new QString("Není otevřen detail objížďky");

    detourDetailView->addStreet(street->getStreetModel());
    updateDetail();

    street->select();
    mapUpdate();

}

//------------------------------------------------------------------------------
// zruší všechny vybrané ulice u detailu objížďky
void MainWindow::deselectStreetsOnDetour(){

    if(detourDetailView == NULL) throw new QString("Není otevřený detail objížďky");

    detourDetailView->clearStreets();
    updateDetail();

    mapView->setMode(0);
    mapView->setMode(1);

    mapUpdate();


}

//--------------------------------------------------------------------------------
// otevře detail zastávky
void MainWindow::openBusStopDetail(BusStopView *busStop){

    try{
        closeDetail();
        busStopDetailView = new BusStopDetailView(busStop, this);
        busStopDetailView->paint(widget);
    }
    catch(const QString *exc){
        showException(exc);
    }
}

//--------------------------------------------------------------------------------
// otevře detail autobusu
void MainWindow::openBusDetail(BusView *bus){

    try{
        closeDetail();
        busDetailView = new BusDetailView(bus, this);
        busDetailView->paint(widget);

        for(StreetModel* street: bus->getBusModel()->getBusLine()->getPath()->getStreets()){
            mapView->getStreetByModel(street)->open();
        }
    }
    catch(const QString *exc){
        showException(exc);
    }
}

//-----------------------------------------------------------------------------------
// znovu načte zobrazení detailu
void MainWindow::updateDetail(){
    clearWidget();

    try{
        if(clockDetailView != NULL){
            clockDetailView->paint(widget);
        }

        else if(streetDetailView != NULL){
            streetDetailView->paint(widget);
        }

        else if(detourDetailView != NULL){
            detourDetailView->paint(widget);
        }

        else if(busStopDetailView != NULL){
            busStopDetailView->paint(widget);
        }

        else if(busDetailView != NULL){
            busDetailView->paint(widget);
        }
    }
    catch(const QString *exc){
        showException(exc);
    }

}

//------------------------------------------------------------------------------
// zavře detaily
void MainWindow::closeDetail(){

    if(clockDetailView != NULL){
        delete clockDetailView;
        clockDetailView = NULL;
    }

    if(streetDetailView != NULL){
        delete streetDetailView;
        streetDetailView = NULL;
    }

    if(detourDetailView != NULL){
        delete detourDetailView;
        detourDetailView = NULL;

        mapView->setMode(0);
        mapUpdate();
    }

    if(busStopDetailView != NULL){
        delete busStopDetailView;
        busStopDetailView = NULL;
    }

    if(busDetailView != NULL){

        delete busDetailView;
        busDetailView = NULL;
        mapView->closeStreets();
    }

    clearWidget();
}

//----------------------------------------------------------------------------
// zavře detail konkrétního autobusu
void MainWindow::closeBusDetail(BusModel* bus){
    if(busDetailView != NULL && busDetailView->getBusView()->getBusModel() == bus) closeDetail();
}

//--------------------------------------------------------------------------------
// vyčistí plochu detailu
void MainWindow::clearWidget(){
    qDeleteAll(widget->findChildren<QWidget*>("", Qt::FindDirectChildrenOnly));
}

//********************************************************************************
// metody pro ošetření chyb
//--------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
// zobrazi chybove hlaseni
void MainWindow::showException(const QString *text){
    exceptionLabel->setText(text->at(0));
}

