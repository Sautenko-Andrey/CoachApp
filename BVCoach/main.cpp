#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    window.setWindowTitle("Beach Volleyball Coach");
    window.setStyleSheet("background-color:gray;");
    window.setAutoFillBackground( true );
    window.show();
    return app.exec();
}
