//
// Created by unf0r9et on 16.11.25.
//

#include "EditingTaskMenu.h"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>


EditingTaskMenu::EditingTaskMenu(DatabaseManager *dbManager, QWidget *parent, int taskId) : QWidget(parent),
    taskId(taskId), dbManager(dbManager) {
    setAttribute(Qt::WA_StyledBackground, true);
    titleEdit = new QLineEdit(this);
    titleEdit->setPlaceholderText("Что будем делать?");

    descriptionEdit = new QTextEdit(this);
    descriptionEdit->setPlaceholderText("Есть идеи?");

    categoryCombo = new QComboBox(this);
    categoryCombo->addItems({"Работа", "Учёба", "Хобби", "Другое"});

    deadlineEdit = new QDateEdit(this);
    deadlineEdit->setDate(QDate::currentDate());
    deadlineEdit->setCalendarPopup(true);

    auto buttonAccept = new QPushButton(this);
    buttonAccept->setText("OK");
    auto buttonReject = new QPushButton(this);
    buttonReject->setText("NO");
    auto buttonDelete = new QPushButton(this);
    buttonDelete->setText("Удалить");

    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(new QLabel("Название"));
    mainLayout->addWidget(titleEdit);
    mainLayout->addWidget(new QLabel("Описание:"));
    mainLayout->addWidget(descriptionEdit);
    mainLayout->addWidget(new QLabel("Категория:"));
    mainLayout->addWidget(categoryCombo);
    mainLayout->addWidget(new QLabel("Дедлайн:"));
    mainLayout->addWidget(deadlineEdit);
    auto buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(buttonReject);
    buttonLayout->addWidget(buttonAccept);
    buttonLayout->addWidget(buttonDelete);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
    connect(buttonAccept, &QPushButton::clicked, this, &EditingTaskMenu::onAcceptClicked);
    connect(buttonReject, &QPushButton::clicked, this, &EditingTaskMenu::onRejectClicked);
    connect(buttonDelete, &QPushButton::clicked, this, &EditingTaskMenu::onDeleteClicked);
}

