#include "interfaces/Interfaces.h"

AbstractMainWindow::AbstractMainWindow(QWidget *parent)
    : QMainWindow(parent) {
    //setWindowFlags(Qt::FramelessWindowHint);
    stack = new QStackedWidget(this);
    setCentralWidget(stack);

    controller = new AppController(stack, this);

    controller->showAuthorization();
    this->setStyleSheet(R"(QWidget { background-color: #121212; })");

    setMinimumSize(WINDOW_WIDTH, WINDOW_HEIGHT);
}
