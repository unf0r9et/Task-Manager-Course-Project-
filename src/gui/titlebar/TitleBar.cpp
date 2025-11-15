//
// Created by unf0r9et on 24.10.25.
//

#include <qcoreapplication.h>
#include <QHBoxLayout>
#include <QPushButton>


#include "TitleBar.h"
#include "interfaces/WindowOptions.h"
#include "styleloader/StyleLoader.h"

TitleBar::TitleBar(QWidget *parent) : QWidget(parent) {
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_StyledBackground, true);
    setObjectName("titleBar");
    setFixedSize(WINDOW_WIDTH, TITLEBAR_HEIGHT);

    closeButton = new QPushButton();
    closeButton->setFixedSize(1.5 * TITLEBAR_HEIGHT, TITLEBAR_HEIGHT);
    closeButton->setText("⨉");
    closeButton->setObjectName("closeButton");


    auto *mainLayout = new QVBoxLayout();
    auto buttonLayout = new QHBoxLayout();

    buttonLayout->addStretch();
    buttonLayout->addWidget(closeButton);

    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);

    connect(closeButton, &QPushButton::clicked, qApp, &QCoreApplication::quit);

    StyleLoader::loadStyleSheet(this, ":/styles/titlebar.qss");
}
