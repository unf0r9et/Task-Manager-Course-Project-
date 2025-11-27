#include "AddTaskWidgetMenu.h"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>


AddTaskWidgetMenu::AddTaskWidgetMenu(DatabaseManager *dbManager, int currentUserId, QWidget *parent)
    : QWidget(parent), dbManager(dbManager), currentUserId(currentUserId) {
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
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
    connect(buttonAccept, &QPushButton::clicked, this, &AddTaskWidgetMenu::onAcceptClicked);
    connect(buttonReject, &QPushButton::clicked, this, &AddTaskWidgetMenu::onRejectClicked);
    //  this->setStyleSheet("background-color: gray;");
}
