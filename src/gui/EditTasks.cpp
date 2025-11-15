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


    addTaskButton = new QPushButton(this);

    auto addTaskButtonLayout = new QHBoxLayout();
    addTaskButtonLayout->addWidget(addTaskButton);


    auto mainLayout = new QVBoxLayout();
    mainLayout->addLayout(addTaskButtonLayout);

    setLayout(mainLayout);

    StyleLoader::loadStyleSheet(this, "");
    connect(addTaskButton, &QPushButton::clicked, this, &EditTasks::onAddTaskButtonClicked);
}

