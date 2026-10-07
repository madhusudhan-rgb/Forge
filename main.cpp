#include <QApplication>
#include "mainwindow.h" // Include your custom window comp

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();
    //main cpp does almost nothing but exec the thing so
    //dont even bother doin shi here bro
    return QApplication::exec();
}
