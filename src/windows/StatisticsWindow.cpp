//
// Created by unf0r9et on 28.11.25.
//

#include "StatisticsWindow.h"

#include <qboxlayout.h>
#include <QPushButton>
#include "interfaces/WindowOptions.h"


StatisticsWindow::StatisticsWindow(QWidget *parent) : QWidget(parent) {
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    setObjectName("StatisticsWindow");
    auto *backToMenuButton = new QPushButton("Back", this);
    backToMenuButton->setGeometry(0, 0, 50, 50);
    connect(backToMenuButton, &QPushButton::clicked, this, &StatisticsWindow::backToMenuClicked);
    // StyleLoader::loadStyleSheet(this, "");
}
