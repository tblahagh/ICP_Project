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

class ClockView : public QWidget
{
    Q_OBJECT

public:
    ClockView(ClockModel* _clockModel, MainWindow* _mainWindow, QWidget *parent = nullptr);
public slots:
    void ticked();

private:
    // model zakladniho okna
    MainWindow *mainWindow;
    // model hodin
    ClockModel *clockModel;
};

#endif // CLOCKVIEW_H
