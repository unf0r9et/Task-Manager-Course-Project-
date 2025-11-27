//
// Created by unf0r9et on 27.11.25.
//

#include "../windows/ChatBotWindow.h"
#include <qboxlayout.h>
#include <QPushButton>
#include <QLabel>
#include "interfaces/WindowOptions.h"
#include "styleloader/StyleLoader.h"



ChatBotWindow::ChatBotWindow(QWidget *parent) : QWidget(parent) {
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    setObjectName("ChatBotWindow");

    auto *addTaskButton = new QPushButton("Add Task", this);
    addTaskButton->setObjectName("addTaskButton");

    addTaskButton->setGeometry(50, 50, 200, 200);

    auto *notAddTaskButton = new QPushButton("Not Add Task", this);
    notAddTaskButton->setObjectName("notAddTaskButton");

    notAddTaskButton->setGeometry(400, 50, 200, 200);

    auto *backButton = new QPushButton("Back", this);
    backButton->setObjectName("backButton");
    backButton->setGeometry(0, 0, 50, 50);

    input = new QLineEdit(this);
    output = new QLabel("Введите вопрос и нажмите Enter", this);
    input->setGeometry(600, 450, 250, 250);
    output->setGeometry(50, 450, 500, 500);

    connect(input, &QLineEdit::returnPressed, this, &ChatBotWindow::sendRequest);
    connect(addTaskButton, &QPushButton::clicked, this, &ChatBotWindow::onAddTaskPressed);
    connect(notAddTaskButton, &QPushButton::clicked, this, &ChatBotWindow::onNotAddTaskPressed);
    connect(backButton, &QPushButton::clicked, this, &ChatBotWindow::onBackButtonClicked);
}
