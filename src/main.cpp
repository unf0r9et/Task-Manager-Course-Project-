#include <QApplication>
#include "interfaces/Interfaces.h"

int main(int argc, char *argv[]) {

    qputenv("QT_SCALE_FACTOR", QByteArray("1.25"));

    QApplication app(argc, argv);

    // auto *titleBar = new TitleBar();
    //
    // titleBar->show();

    AbstractMainWindow menu;
    menu.show();

    return QApplication::exec();
}