#include "AddTaskWidgetMenu.h"

#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>
#include "databaseManager/DatabaseManager.h"

AddTaskWidgetMenu::AddTaskWidgetMenu(DatabaseManager *dbManager, QWidget *parent)
    : QWidget(parent), dbManager(dbManager) {

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
    this->setStyleSheet("background-color: gray;");
}


void AddTaskWidgetMenu::onAcceptClicked() {
    QString title = titleEdit->text().trimmed();
    if (title.isEmpty()) {
        QMessageBox::warning(this, "Error", "Title cannot be empty.");
        return;
    }

    QString description = descriptionEdit->toPlainText();
    QString category = categoryCombo->currentText();
    QDate deadline = deadlineEdit->date();

    if (dbManager) {
        if (dbManager->addTask(title, description, category, deadline)) {
            emit taskWasAdded();
        } else {
            QMessageBox::critical(this, "Error", "Failed to add task.");
        }
    } else {
        QMessageBox::critical(this, "Error", "Database is not initialized.");
    }
}

void AddTaskWidgetMenu::onRejectClicked() {
    emit taskWasNotAdded();
}
