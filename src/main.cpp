#include "mainwindow.h"
#include "src/mapcreator.h"
#include "src/Models/mapmodel.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    MapCreator creator = MapCreator();
    MapModel map = creator.CreateMap("file.xml");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
