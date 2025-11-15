//
// Created by unf0r9et on 15.11.25.
//

#include "ApplicationMenu.h"

#include <qboxlayout.h>

#include "interfaces/WindowOptions.h"

ApplicationMenu::ApplicationMenu(QWidget *parent) : QWidget(parent) {
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    setObjectName("ApplicationMenu");
    setAttribute(Qt::WA_StyledBackground, true);
    auto mainLayout = new QVBoxLayout();

    setLayout(mainLayout);

}
