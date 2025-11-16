//
// Created by unf0r9et on 15.11.25.
//

#include "../windows/ApplicationMenu.h"
#include <QPushButton>
#include <qboxlayout.h>

#include "appController/AppController.h"
#include "interfaces/WindowOptions.h"

ApplicationMenu::ApplicationMenu(QWidget *parent) : QWidget(parent) {
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    setObjectName("ApplicationMenu");
    setAttribute(Qt::WA_StyledBackground, true);

    editTasksButton = new QPushButton(this);
    editTasksButton->setObjectName("editTasksButton");
    editTasksButton->setText("Задачи");

    chatBotButton = new QPushButton(this);
    chatBotButton->setObjectName("chatBotButton");
    chatBotButton->setText("Чат-бот");

    statisticsButton = new QPushButton(this);
    statisticsButton->setObjectName("statisticsButton");
    statisticsButton->setText("Статистика");

    calendarButton = new QPushButton(this);
    calendarButton->setObjectName("calendarButton");
    calendarButton->setText("Календарь задач");



    auto firstLineLayout = new QHBoxLayout();
    auto secondLineLayout = new QHBoxLayout();
    firstLineLayout->addStretch();
    firstLineLayout->addWidget(editTasksButton);
    firstLineLayout->addStretch();
    firstLineLayout->addWidget(chatBotButton);
    firstLineLayout->addStretch();
    secondLineLayout->addStretch();
    secondLineLayout->addWidget(statisticsButton);
    secondLineLayout->addStretch();
    secondLineLayout->addWidget(calendarButton);
    secondLineLayout->addStretch();
    secondLineLayout->addStretch();



    auto mainLayout = new QVBoxLayout();
    mainLayout->addStretch();
    mainLayout->addLayout(firstLineLayout);
    mainLayout->addStretch();
    mainLayout->addLayout(secondLineLayout);
    mainLayout->addStretch();

    setLayout(mainLayout);

    connect(editTasksButton, &QPushButton::clicked, this, &ApplicationMenu::editTasksClicked);
    connect(chatBotButton, &QPushButton::clicked, this, &ApplicationMenu::chatBotClicked);
    connect(statisticsButton, &QPushButton::clicked, this, &ApplicationMenu::statisticsClicked);
    connect(calendarButton, &QPushButton::clicked, this, &ApplicationMenu::calendarClicked);
}




