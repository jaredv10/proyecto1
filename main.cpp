#include <QApplication>
#include "Gamewindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    GameWindow gameWindow;
    gameWindow.show();
    return a.exec();
}
