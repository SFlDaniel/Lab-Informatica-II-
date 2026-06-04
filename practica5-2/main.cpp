#include <QApplication>

#include "gamewindow.h"

int main(int argc,
         char *argv[])
{
    QApplication a(argc, argv);

    GameWindow ventana;

    ventana.show();

    return a.exec();
}