
#include <QApplication>
#include <QMainWindow>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_DontUseNativeDialogs,true);

    QApplication app(argc, argv);

    MainWindow window;
    window.show();
   
    return app.exec();
}
