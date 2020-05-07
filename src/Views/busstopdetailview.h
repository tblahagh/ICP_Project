#ifndef BUSSTOPDETAILVIEW_H
#define BUSSTOPDETAILVIEW_H
#include <QWidget>
#include <QMainWindow>
#include "src/mainwindow.h"
#include "busstopview.h"

#include <QPushButton>
#include <QHBoxLayout>
#include <QSizePolicy>

using namespace std;

class MainWindow;

class BusStopDetailView : public QWidget
{
    Q_OBJECT

public:
    BusStopDetailView(BusStopView* _streetView, MainWindow* _mainWindow, QWidget *parent = 0);
    ~BusStopDetailView();
    void paint(QWidget *widget);

public slots:
    void btnCloseClicked();


private:
    // model zakladniho okna
    MainWindow *mainWindow;
    // pohled zastávky
    BusStopView *busStopView;

    // layout
    QGridLayout *layout = NULL;
    // btn
    QPushButton *btnClose;

};

#endif // BUSSTOPDETAILVIEW_H
