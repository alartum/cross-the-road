#include <QApplication>
#include "testwidget.h"
#include "mainwindow.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
//    TestWidget *w = new TestWidget;
    MainWindow *window = new MainWindow;
    window->show();
    window->start();
//    w->show();
    return app.exec();
}
