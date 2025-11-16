//
// Created by unf0r9et on 15.11.25.
//

#include "../windows/EditTasks.h"

#include <qboxlayout.h>
#include <QPushButton>
#include "interfaces/WindowOptions.h"
#include "styleloader/StyleLoader.h"
#include "styleloader/StyleLoader.h"
#include "/home/unf0r9et/myProject/CourseProject/TaskManager/src/core/editTasksLogic/AddTaskWidgetMenu.h"


EditTasks::EditTasks(QWidget *parent) : QWidget(parent) {
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    setObjectName("EditTasks");

    addTaskButton = new QPushButton("+", this);
    addTaskButton->setGeometry(400, WINDOW_HEIGHT - 1100, 180, 120);;


    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setGeometry(980, 15, 1000,WINDOW_HEIGHT - 30);

    tasksContainer = new QWidget();
    tasksLayout = new QVBoxLayout(tasksContainer);
    scrollArea->setWidget(tasksContainer);


    StyleLoader::loadStyleSheet(this, "");
    connect(addTaskButton, &QPushButton::clicked, this, &EditTasks::onAddTaskClicked);
}
