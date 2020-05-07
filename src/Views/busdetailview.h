#ifndef BUSDETAILVIEW_H
#define BUSDETAILVIEW_H
#include <QWidget>
#include <QMainWindow>
#include "src/mainwindow.h"
#include "busview.h"

#include <QPushButton>
#include <QHBoxLayout>
#include <QSizePolicy>

using namespace std;

class MainWindow;

class BusDetailView : public QWidget
{
    Q_OBJECT

public:
    BusDetailView(BusView* _streetView, MainWindow* _mainWindow, QWidget *parent = 0);
    ~BusDetailView();
    void paint(QWidget *widget);
    BusView* getBusView();

public slots:
    void btnCloseClicked();


private:
    // model zakladniho okna
    MainWindow *mainWindow;
    // pohled zastávky
    BusView *busView;

    // layout
    QGridLayout *layout = NULL;
    // btn
    QPushButton *btnClose;

};

#endif // BUSDETAILVIEW_H
