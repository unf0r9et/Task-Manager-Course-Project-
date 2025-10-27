#include <qboxlayout.h>
#include <QWindow>
#include <QMouseEvent>

#include "interfaces/WindowOptions.h"
#include "AbstractMainWindow.h"
#include "titlebar/TitleBar.h"
#include "AppController.h"

AbstractMainWindow::AbstractMainWindow(QWidget *parent)
    : QMainWindow(parent) {
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT + TITLEBAR_HEIGHT);
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    auto *central = new QWidget(this);
    auto *layout = new QVBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    auto *titleBar = new TitleBar(this);
    layout->addWidget(titleBar);

    stack = new QStackedWidget(this);
    layout->addWidget(stack);

    central->setLayout(layout);
    setCentralWidget(central);


    controller = new AppController(stack, this);

    controller->showAuthorization();

    //  this->setStyleSheet(R"(QWidget { background-color: #121212; })");
}

void AbstractMainWindow::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        int clickY = event->pos().y();

        if (clickY >= 0 && clickY <= TITLEBAR_HEIGHT) {
            if (this->windowHandle()) {
                this->windowHandle()->startSystemMove();
            }
        }
    }
    QMainWindow::mousePressEvent(event);
}
