//
// Created by unf0r9et on 27.11.25.
//

#include "../windows/ChatBotWindow.h"
#include <qboxlayout.h>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>

#include "interfaces/WindowOptions.h"
#include "styleloader/StyleLoader.h"



ChatBotWindow::ChatBotWindow(QWidget *parent) : QWidget(parent) {
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    setObjectName("ChatBotWindow");
    setAttribute(Qt::WA_StyledBackground, true);

    const QPixmap background(":/images/jpeg.png");
    auto *backgroundLayout = new QLabel(this);
    backgroundLayout->setPixmap(background.scaled(900, 1250, Qt::KeepAspectRatioByExpanding,
                                      Qt::SmoothTransformation));
    backgroundLayout->setAlignment(Qt::AlignCenter);
    backgroundLayout->setGeometry(1100, 0, 900, 1250);


    const QPixmap photo(":/images/BRANK.png");
    auto *logoLayout = new QLabel(this);
    logoLayout->setPixmap(photo.scaled(900, 1250, Qt::KeepAspectRatioByExpanding,
                                      Qt::SmoothTransformation));
    logoLayout->setAlignment(Qt::AlignCenter);
    logoLayout->setGeometry(1100, 0, 900, 1250);


    auto *addTaskButton = new QPushButton("ДОБАВИТЬ ЗАДАЧУ", this);
    addTaskButton->setObjectName("addTaskButton");

    addTaskButton->setGeometry(180, 960, 300, 200);

    auto *notAddTaskButton = new QPushButton("НЕ ДОБАВЛЯТЬ ЗАДАЧУ", this);
    notAddTaskButton->setObjectName("notAddTaskButton");

    notAddTaskButton->setGeometry(520, 960, 300, 200);

    auto *backButton = new QPushButton("←", this);
    backButton->setGeometry(10, 10, 100, 50);
    backButton->setObjectName("backButton");

    auto *sendButton = new QPushButton("Отправить", this);
    sendButton->setGeometry(860, 725, 90, 140);


    input = new QTextEdit(this);
    input->setGeometry(150, 650, 700, 300);

    output = new QLabel("Привет! Я БРАНК. Введи краткое описание того,\nчто тебе надо сделать. И я придумаю все остальное =)", this);
    output->setGeometry(150, 100, 800, 500);
    output->setObjectName("output");
    output->setWordWrap(true);
    output->setAlignment(Qt::AlignCenter);

    connect(sendButton, &QPushButton::clicked, this, &ChatBotWindow::sendRequest);
    connect(addTaskButton, &QPushButton::clicked, this, &ChatBotWindow::onAddTaskPressed);
    connect(notAddTaskButton, &QPushButton::clicked, this, &ChatBotWindow::onNotAddTaskPressed);
    connect(backButton, &QPushButton::clicked, this, &ChatBotWindow::onBackButtonClicked);
    StyleLoader::loadStyleSheet(this, ":/styles/chatBotWindow.qss");
}
