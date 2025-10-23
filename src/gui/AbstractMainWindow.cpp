#include <qboxlayout.h>

#include "interfaces/Interfaces.h"

AbstractMainWindow::AbstractMainWindow(QWidget *parent)
    : QMainWindow(parent) {

    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    setObjectName("MAINWINDOW");
    setWindowFlags(Qt::FramelessWindowHint);


    QWidget *central = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(central);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);

    TitleBar *titleBar = new TitleBar(this);
    layout->addWidget(titleBar);

    stack = new QStackedWidget(this);
    layout->addWidget(stack);

    central->setLayout(layout);
    setCentralWidget(central);

    controller = new AppController(stack, this);

    controller->showAuthorization();

    this->setStyleSheet(R"(QWidget { background-color: #121212; })");
}
