#include "interfaces/Interfaces.h"
#include "AppController.h"

AbstractMainWindow::AbstractMainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    stack = new QStackedWidget(this);
    setCentralWidget(stack);

    controller = new AppController(stack, this);

    controller->showAuthorization();

    setMinimumSize(WINDOW_WIDTH, WINDOW_HEIGHT);
}

