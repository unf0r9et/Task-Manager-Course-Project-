#include <qboxlayout.h>

#include "interfaces/Interfaces.h"

AbstractMainWindow::AbstractMainWindow(QWidget *parent)
    : QMainWindow(parent) {
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    //setWindowFlags(Qt::FramelessWindowHint);


    // // QWidget *central = new QWidget(this);
    // auto *layout = new QVBoxLayout();
    // // layout->setContentsMargins(0,0,0,0);
    // // layout->setSpacing(0);
    //
    // auto *titleBar = new TitleBar(this);
    //
    //
    //
    // // layout->addWidget(titleBar);

    stack = new QStackedWidget(this);

    setCentralWidget(stack);

    controller = new AppController(stack, this);

    controller->showAuthorization();

    //this->setStyleSheet(R"(QWidget { background-color: #121212; })");
}
