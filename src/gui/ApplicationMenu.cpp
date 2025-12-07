//
// Created by unf0r9et on 15.11.25.
//

#include "../windows/ApplicationMenu.h"
#include <QPushButton>
#include <qboxlayout.h>
#include "styleloader/StyleLoader.h"

#include "appController/AppController.h"
#include "interfaces/WindowOptions.h"

ApplicationMenu::ApplicationMenu(QWidget *parent) : QWidget(parent) {
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    setObjectName("ApplicationMenu");
    setAttribute(Qt::WA_StyledBackground, true);

    int sizeBut = 300;
    const QPixmap LOGO(":/icons/LOGO.png");
    auto *logoLayout = new QLabel(this);
    logoLayout->setPixmap(LOGO.scaled(600, 120, Qt::KeepAspectRatioByExpanding,
                                      Qt::SmoothTransformation));
    logoLayout->setAlignment(Qt::AlignCenter);
    logoLayout->setGeometry(700, 100, 600, 120);

    const QPixmap photo(":/images/jpeg.png");


    QTransform transform;
    transform.scale(-1, 1);

    QPixmap stretched = photo.scaled(500, 1250, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPixmap mirrored = stretched.transformed(transform, Qt::SmoothTransformation);

    auto *photoLayout = new QLabel(this);
    photoLayout->setPixmap(stretched.scaled(600, 120, Qt::KeepAspectRatioByExpanding,
                                            Qt::SmoothTransformation));
    photoLayout->setAlignment(Qt::AlignCenter);
    photoLayout->setGeometry(0, 0, 500, 1250);
    auto *photoLayout_2 = new QLabel(this);
    photoLayout_2->setPixmap(mirrored.scaled(600, 120, Qt::KeepAspectRatioByExpanding,
                                             Qt::SmoothTransformation));
    photoLayout_2->setAlignment(Qt::AlignCenter);
    photoLayout_2->setGeometry(1500, 0, 500, 1250);


    editTasksButton = new QPushButton(this);
    editTasksButton->setObjectName("editTasksButton");
    editTasksButton->setText("       Задачи       ");
    editTasksButton->setIcon(QIcon(":/icons/TASKS.png"));
    editTasksButton->setIconSize(QSize(100, 100));
    editTasksButton->setGeometry(650, 450, sizeBut, 200);

    chatBotButton = new QPushButton(this);
    chatBotButton->setObjectName("chatBotButton");
    chatBotButton->setText("    БРАНК       ");
    chatBotButton->setIcon(QIcon(":/icons/AI.png"));
    chatBotButton->setIconSize(QSize(140, 140));
    chatBotButton->setGeometry(1050, 450, sizeBut, 200);

    statisticsButton = new QPushButton(this);
    statisticsButton->setObjectName("statisticsButton");
    statisticsButton->setText("    Статистика    ");
    statisticsButton->setIcon(QIcon(":/icons/STAT.png"));
    statisticsButton->setIconSize(QSize(100, 100));
    statisticsButton->setGeometry(1050, 700, sizeBut, 200);

    calendarButton = new QPushButton(this);
    calendarButton->setObjectName("calendarButton");
    calendarButton->setText("Календарь задач");
    calendarButton->setIcon(QIcon(":/icons/CALENDAR.png"));
    calendarButton->setIconSize(QSize(100, 100));
    calendarButton->setGeometry(650, 700, sizeBut, 200);


    auto logoutButton = new QPushButton(this);
    logoutButton->setText("ВЫЙТИ");
    logoutButton->setObjectName("logoutButton");
    logoutButton->setGeometry(20, 1180, 100, 50);

    connect(editTasksButton, &QPushButton::clicked, this, &ApplicationMenu::editTasksClicked);
    connect(chatBotButton, &QPushButton::clicked, this, &ApplicationMenu::chatBotClicked);
    connect(statisticsButton, &QPushButton::clicked, this, &ApplicationMenu::statisticsClicked);
    connect(calendarButton, &QPushButton::clicked, this, &ApplicationMenu::calendarClicked);
    connect(logoutButton, &QPushButton::clicked, this, &ApplicationMenu::logoutClicked);
    StyleLoader::loadStyleSheet(this, ":/styles/applicationMenu.qss");
}
