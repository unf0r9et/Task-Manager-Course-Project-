//
// Created by unf0r9et on 15.11.25.
//

#include "../windows/EditTasks.h"

#include <qboxlayout.h>
#include <QLabel>
#include <QPushButton>
#include "interfaces/WindowOptions.h"
#include "styleloader/StyleLoader.h"
#include "../windows/widgets/AddTaskWidgetMenu.h"

EditTasks::EditTasks(QWidget *parent) : QWidget(parent) {
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    setObjectName("EditTasks");
    setAttribute(Qt::WA_StyledBackground, true);

    const QPixmap background(":/images/jpeg.png");
    auto *backgroundLayout = new QLabel(this);
    backgroundLayout->setPixmap(background.scaled(1040, 1250, Qt::KeepAspectRatioByExpanding,
                                      Qt::SmoothTransformation));
    backgroundLayout->setAlignment(Qt::AlignCenter);
    backgroundLayout->setGeometry(960, 0, 1040, 1250);


    addTaskButton = new QPushButton("+", this);
    addTaskButton->setGeometry(400, WINDOW_HEIGHT - 1100, 180, 120);;
    addTaskButton->setObjectName("TaskButton");


    backToMenuButton = new QPushButton("←", this);
    backToMenuButton->setGeometry(10, 10, 100, 50);
    backToMenuButton->setObjectName("BackButton");

    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setObjectName("ScrollArea");
    scrollArea->setGeometry(980, 0, 1000,WINDOW_HEIGHT);
    scrollArea->setContentsMargins(0, 0, 0, 0);
    tasksContainer = new QWidget();
    tasksLayout = new QVBoxLayout(tasksContainer);
    scrollArea->setWidget(tasksContainer);


    connect(addTaskButton, &QPushButton::clicked, this, &EditTasks::onAddTaskClicked);
    connect(backToMenuButton, &QPushButton::clicked, this, &EditTasks::onBackButtonClicked);
    StyleLoader::loadStyleSheet(this, ":/styles/editTasks.qss");
}
