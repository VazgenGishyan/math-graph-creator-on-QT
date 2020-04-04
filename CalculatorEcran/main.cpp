#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{

    try
    {
        QApplication a(argc, argv);
        MainWindow w;
        w.show();
        return a.exec();
    }
    catch (FatalError f)
    {
        QMessageBox::critical(nullptr,"Error",f.what());
    }
    catch (...)
    {
        QMessageBox::critical(nullptr,"Error","something wrong");
    }
    return 0;
}
