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

class ClockDetailView : public QWidget
{
    Q_OBJECT

public:
    ClockDetailView(ClockModel* _clockModel, MainWindow* _mainWindow, QWidget *parent = 0);
    ~ClockDetailView();
    void paint(QWidget *widget);

public slots:
    void btnInitClicked();
    void btnSpeedClicked();
    void btnCloseClicked();

private:
    // model zakladniho okna
    MainWindow *mainWindow;
    // model hodin
    ClockModel *clockModel;

    // layout
    QGridLayout *layout = NULL;
    // fields
    QLineEdit *fieldHour;
    QLineEdit *fieldMinute;
    QLineEdit *fieldSecond;
    QLineEdit *fieldSpeed;
    // btn
    QPushButton *btnInit;
    QPushButton *btnSpeed;
    QPushButton *btnClose;

};

#endif // CLOCKDETAILVIEW_H
