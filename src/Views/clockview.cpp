#include "clockview.h"

//*******************************************************************************
// konstruktory a destruktory
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
// Základní konstruktor
ClockView::ClockView(ClockModel* _clockModel, MainWindow* _mainWindow, QWidget *parent) : QWidget(parent)
{
    if(_clockModel == NULL || _mainWindow == NULL) throw new QString("Nepodařilo se vytvořit hodiny");

    this->clockModel = _clockModel;
    this->mainWindow = _mainWindow;

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &ClockView::ticked);
    timer->start(1000);
}

//********************************************************************************
// akce v závislosti na hodinách
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
// Tiknutí hodin
void ClockView::ticked()
{
    try{
        clockModel->tick();
        mainWindow->clockTicked();
    }
    catch(const QString *exc){ mainWindow->showException(exc); }
}
