/*
 * Autoři: Tomáš Blaha, Vojtěch Wawreczka
 * Datum: 9.5.2020
 * */
#ifndef CLOCKVIEW_H
#define CLOCKVIEW_H
#include <QWidget>
#include <QMainWindow>
#include <QTimer>
#include "src/Models/clockmodel.h"
#include "src/mainwindow.h"


using namespace std;

class MainWindow;
class ClockModel;
/**
 * Pohled hodin
 */
class ClockView : public QWidget
{
    Q_OBJECT

public:
    /**
     * Základní konstruktor
     * @param _clockModel Model hodin
     * @param _mainWindow Okno aplikace
     * @param parent Rodič pohledu
     */
    ClockView(ClockModel* _clockModel, MainWindow* _mainWindow, QWidget *parent = nullptr);
public slots:
    /**
     * Tiknutí hodin
     */
    void ticked();

private:
    /**
     * Okno aplikace
     */
    MainWindow *mainWindow;
    /**
     * Model hodin
     */
    ClockModel *clockModel;
};

#endif // CLOCKVIEW_H
