#include <QApplication>
#include "interfaces/Interfaces.h"


int main(int argc, char *argv[]) {


    QApplication app(argc, argv);
    AbstractMainWindow menu;
    menu.show();

    return QApplication::exec();
}