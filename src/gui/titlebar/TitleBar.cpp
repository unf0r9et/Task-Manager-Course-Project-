//
// Created by unf0r9et on 24.10.25.
//

#include "interfaces/Interfaces.h"
#include "StyleLoader.cpp"
#include <QPushButton>
#include <QDebug>
#include <QHBoxLayout>

TitleBar::TitleBar(QWidget *parent) : QWidget(parent) {
    setWindowFlags(Qt::FramelessWindowHint);
    setObjectName("titleBar");
    setAttribute(Qt::WA_StyledBackground, true);

    setFixedSize(WINDOW_WIDTH, TITLEBAR_HEIGHT);
    closeButton = new QPushButton();
    closeButton->setFixedHeight(TITLEBAR_HEIGHT);

    auto *mainLayout = new QVBoxLayout();
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);

    auto buttonLayout = new QHBoxLayout();

    buttonLayout->addStretch();
    buttonLayout->addWidget(closeButton);

    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);


    StyleLoader::loadStyleSheet(this, ":/styles/titlebar.qss");
}
