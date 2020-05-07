#ifndef DETOURDETAILVIEW_H
#define DETOURDETAILVIEW_H
#include <QWidget>
#include <QMainWindow>
#include "src/mainwindow.h"
#include "streetview.h"

#include <QPushButton>
#include <QHBoxLayout>
#include <QSizePolicy>

using namespace std;

class MainWindow;

class DetourDetailView : public QWidget
{
    Q_OBJECT

public:
    DetourDetailView(StreetView* _streetView, MainWindow* _mainWindow, QWidget *parent = 0);
    ~DetourDetailView();
    void paint(QWidget *widget);
    void addStreet(StreetModel *street);
    void clearStreets();

public slots:
    void btnSaveClicked();
    void btnClearClicked();
    void btnCloseClicked();

private:
    // model zakladniho okna
    MainWindow *mainWindow;
    // pohled ulice
    StreetView *streetView;

    // layout
    QGridLayout *layout = NULL;
    // fields
    QLineEdit *fieldDelay;
    // labels
    QLabel *labelPathInfo;
    // btn
    QPushButton *btnSave;
    QPushButton *btnClear;
    QPushButton *btnClose;

    // zadana cesta
    PathModel* path = NULL;

};

#endif // DETOURDETAILVIEW_H
