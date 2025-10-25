#include <qboxlayout.h>

#include "interfaces/Interfaces.h"

AbstractMainWindow::AbstractMainWindow(QWidget *parent)
    : QMainWindow(parent) {
    resize(WINDOW_WIDTH, WINDOW_HEIGHT);
    setMinimumSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    setMaximumSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Window | Qt::WindowStaysOnTopHint | Qt::X11BypassWindowManagerHint);



    QWidget *central = new QWidget(this);
    auto *layout = new QVBoxLayout();
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);

    auto *titleBar = new TitleBar(nullptr);
    layout->addWidget(titleBar);

    stack = new QStackedWidget(this);
    layout->addWidget(stack);

    central->setLayout(layout);
    setCentralWidget(central);

    controller = new AppController(stack, this);

    controller->showAuthorization();

    this->setStyleSheet(R"(QWidget { background-color: #121212; })");
}
