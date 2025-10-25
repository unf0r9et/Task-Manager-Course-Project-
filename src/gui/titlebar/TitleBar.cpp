//
// Created by unf0r9et on 24.10.25.
//

#include <qcoreapplication.h>

#include "interfaces/Interfaces.h"
#include "StyleLoader.cpp"
#include <QPushButton>
#include <QDebug>
#include <QHBoxLayout>

#include <QMouseEvent>
#include <QApplication>

TitleBar::TitleBar(QWidget *parent) : QWidget(parent) {
    setWindowFlags(Qt::FramelessWindowHint);
    setObjectName("titleBar");
    setAttribute(Qt::WA_StyledBackground, true);

    setFixedSize(WINDOW_WIDTH, TITLEBAR_HEIGHT);
    closeButton = new QPushButton();
    closeButton->setFixedHeight(TITLEBAR_HEIGHT);
    closeButton->setFixedWidth(1.5*TITLEBAR_HEIGHT);
    closeButton->setText("⨉");
    closeButton->setObjectName("closeButton");


    auto *mainLayout = new QVBoxLayout();
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);

    auto buttonLayout = new QHBoxLayout();

    buttonLayout->addStretch();
    buttonLayout->addWidget(closeButton);

    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);

    connect(closeButton, &QPushButton::clicked, qApp, &QCoreApplication::quit);

    StyleLoader::loadStyleSheet(this, ":/styles/titlebar.qss");
}


// void TitleBar::mousePressEvent(QMouseEvent *event) {
//     if (event->button() == Qt::LeftButton) {
//         m_dragPosition = event->globalPos();
//         m_dragging = true;
//         qDebug() << "Mouse pressed on title bar!";
//     }
// }
// void TitleBar::mouseMoveEvent(QMouseEvent *event) {
//     if (m_dragging) {
//         auto delta = event->globalPos() - m_dragPosition;
//         QWidget *mainWindow = window();
//         if (mainWindow) {
//             qDebug() << "Moving window:" << mainWindow << "to" << mainWindow->pos() + delta;
//             mainWindow->move(mainWindow->pos() + delta);
//             m_dragPosition = event->globalPos();
//         } else {
//             qDebug() << "Main window is null!";
//         }
//     }
// }
// void TitleBar::mouseReleaseEvent(QMouseEvent *event) {
//     if (event->button() == Qt::LeftButton) {
//         m_dragging = false;
//         qDebug() << "Mouse released on title bar!";
//     }
// }