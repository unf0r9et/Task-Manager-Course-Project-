#include <QApplication>
#include "Interface/Menu.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    AuthorizationMenu();

    return QApplication::exec();
}
