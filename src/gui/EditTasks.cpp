//
// Created by unf0r9et on 15.11.25.
//

#include "../windows/EditTasks.h"

#include <qboxlayout.h>
#include <QPushButton>
#include "interfaces/WindowOptions.h"
#include "styleloader/StyleLoader.h"

EditTasks::EditTasks(QWidget *parent) : QWidget(parent) {
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    setObjectName("EditTasks");

    addTaskButton = new QPushButton("+", this);
    addTaskButton->setFixedSize(100, 100);
    auto menuLayout = new QVBoxLayout();
    menuLayout->addWidget(addTaskButton);


    addingTasksWidget = new QWidget();
    addingTasksWidget->setFixedWidth(WINDOW_WIDTH/2);
    menuLayout->addWidget(addingTasksWidget);

    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);


    tasksContainer = new QWidget();
    tasksLayout = new QVBoxLayout(tasksContainer);
    scrollArea->setWidget(tasksContainer);
    scrollArea->setFixedWidth(WINDOW_WIDTH/2);

    auto horizontalLayout = new QHBoxLayout();
    horizontalLayout->addLayout(menuLayout);
    horizontalLayout->addWidget(scrollArea);
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(horizontalLayout);

    setLayout(mainLayout);
    StyleLoader::loadStyleSheet(this, "");

    connect(addTaskButton, &QPushButton::clicked, this, &EditTasks::onAddTaskClicked);
}

