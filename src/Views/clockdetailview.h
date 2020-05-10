#ifndef CLOCKDETAILVIEW_H
#define CLOCKDETAILVIEW_H
#include <QWidget>
#include <QMainWindow>
#include "src/Models/clockmodel.h"
#include "src/mainwindow.h"


#include <QPushButton>
#include <QHBoxLayout>
#include <QSizePolicy>
#include <windows.h>


using namespace std;

class MainWindow;
class ClockModel;
/**
 * Pohled detailu hodin
 */
class ClockDetailView : public QWidget
{
    Q_OBJECT

public:
    /**
     * Základní konstruktor
     * @param _clockModel Model hodin
     * @param _mainWindow Okno aplikace
     * @param parent Rodič pohledu
     */
    ClockDetailView(ClockModel* _clockModel, MainWindow* _mainWindow, QWidget *parent = 0);
    /**
     * Destruktor
     */
    ~ClockDetailView();
    /**
     * Metoda vykresli pohled do widgetu
     * @param widget Widget, do kterého se má pohled vykreslit
     */
    void paint(QWidget *widget);

public slots:
    /**
     * Metoda se provede při kliknutí na tlačítko inicializace
     */
    void btnInitClicked();
    /**
     * Metoda se provede při kliknutí na tlačítko uložení rychlosti
     */
    void btnSpeedClicked();
    /**
     * Metoda zavření detailu
     */
    void btnCloseClicked();

private:
    /**
     * okno aplikace
     */
    MainWindow *mainWindow;

    /**
     * Model hodin
     */
    ClockModel *clockModel;

    /**
     * Layout
     */
    QGridLayout *layout = NULL;

    /**
     * Textová pole
     */
    QLineEdit *fieldHour;
    QLineEdit *fieldMinute;
    QLineEdit *fieldSecond;
    QLineEdit *fieldSpeed;

    /**
     * Tlačítka
     */
    QPushButton *btnInit;
    QPushButton *btnSpeed;
    QPushButton *btnClose;

};

#endif // CLOCKDETAILVIEW_H
