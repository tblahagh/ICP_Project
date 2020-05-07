#ifndef STREETDETAILVIEW_H
#define STREETDETAILVIEW_H
#include <QWidget>
#include <QMainWindow>
#include "src/mainwindow.h"
#include "streetview.h"

#include <QPushButton>
#include <QHBoxLayout>
#include <QSizePolicy>

using namespace std;

class MainWindow;

class StreetDetailView : public QWidget
{
    Q_OBJECT

public:
    StreetDetailView(StreetView* _streetView, MainWindow* _mainWindow, QWidget *parent = 0);
    ~StreetDetailView();
    void paint(QWidget *widget);

public slots:
    void btnSaveClicked();
    void btnCloseClicked();
    void btnDetourDetailClicked();

private:
    // model zakladniho okna
    MainWindow *mainWindow;
    // pohled ulice
    StreetView *streetView;

    // layout
    QGridLayout *layout = NULL;
    // radio
    QRadioButton *btnGreen;
    QRadioButton *btnOrange;
    QRadioButton *btnRed;
    QRadioButton *btnBlack;
    QButtonGroup *fieldTraffic;
    // btn
    QPushButton *btnSave;
    QPushButton *btnClose;
    // zavrena ulice
    QPushButton *btnDetourDetail;

};

#endif // STREETDETAILVIEW_H

