//
// Created by unf0r9et on 24.10.25.
//

#include "interfaces/Interfaces.h"
#include "StyleLoader.cpp"
#include <QPushButton>

TitleBar::TitleBar(QWidget *parent) : QWidget(parent) {
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowTitle("TitleBar");
    setObjectName("titleBar");

    setFixedSize(WINDOW_WIDTH, 30);
    closeButton = new QPushButton();

    StyleLoader::loadStyleSheet(this, ":/styles/titlebar.qss");



    //qDebug() << "Style loaded? " << QFile::exists(":/styles/titlebar.qss");

    //this->setStyleSheet("background-color: #3a3f51;");


}
