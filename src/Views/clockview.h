/*
 * Autoři: Tomáš Blaha, Vojtěch Wawreczka
 * Datum: 9.5.2020
 *
 * Pohled hodin
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
 * @brief Pohled hodin
 */
class ClockView : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Základní konstruktor
     * @param _clockModel Model hodin
     * @param _mainWindow Okno aplikace
     * @param parent Rodič pohledu
     */
    ClockView(ClockModel* _clockModel, MainWindow* _mainWindow, QWidget *parent = nullptr);
public slots:
    /**
     * @brief Tiknutí hodin
     */
    void ticked();

private:
    /**
     * @brief Okno aplikace
     */
    MainWindow *mainWindow;
    /**
     * @brief Model hodin
     */
    ClockModel *clockModel;
};

#endif // CLOCKVIEW_H
