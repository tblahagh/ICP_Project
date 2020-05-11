/*
 * Autoři: Tomáš Blaha, Vojtěch Wawreczka
 * Datum: 9.5.2020
 *
 * Pohled detailu hodin
 * */
#ifndef CLOCKDETAILVIEW_H
#define CLOCKDETAILVIEW_H
#include <QWidget>
#include <QMainWindow>
#include "src/Models/clockmodel.h"
#include "src/mainwindow.h"


#include <QPushButton>
#include <QHBoxLayout>
#include <QSizePolicy>



using namespace std;

class MainWindow;
class ClockModel;
/**
 * @brief Pohled detailu hodin
 */
class ClockDetailView : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Základní konstruktor
     * @param _clockModel Model hodin
     * @param _mainWindow Okno aplikace
     * @param parent Rodič pohledu
     */
    ClockDetailView(ClockModel* _clockModel, MainWindow* _mainWindow, QWidget *parent = 0);
    /**
     * @brief Destruktor
     */
    ~ClockDetailView();
    /**
     * @brief Metoda vykresli pohled do widgetu
     * @param widget Widget, do kterého se má pohled vykreslit
     */
    void paint(QWidget *widget);

public slots:
    /**
     * @brief Metoda se provede při kliknutí na tlačítko inicializace
     */
    void btnInitClicked();
    /**
     * @brief Metoda se provede při kliknutí na tlačítko uložení rychlosti
     */
    void btnSpeedClicked();
    /**
     * @brief Metoda zavření detailu
     */
    void btnCloseClicked();

private:
    /**
     * @brief okno aplikace
     */
    MainWindow *mainWindow;

    /**
     * @brief Model hodin
     */
    ClockModel *clockModel;

    /**
     * @brief Layout
     */
    QGridLayout *layout = NULL;

    /**
     * @brief Textová pole
     */
    QLineEdit *fieldHour;
    QLineEdit *fieldMinute;
    QLineEdit *fieldSecond;
    QLineEdit *fieldSpeed;

    /**
     * @brief Tlačítka
     */
    QPushButton *btnInit;
    QPushButton *btnSpeed;
    QPushButton *btnClose;

};

#endif // CLOCKDETAILVIEW_H
