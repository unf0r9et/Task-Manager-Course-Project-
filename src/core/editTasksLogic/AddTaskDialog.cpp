#include "AddTaskWidget.h"
#include "databaseManager/DatabaseManager.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>

AddTaskWidget::AddTaskWidget(DatabaseManager *dbManager, QWidget *parent)
    : QWidget(parent), dbManager(dbManager) {
    setObjectName("AddTaskWidget");

    titleEdit = new QLineEdit(this);
    titleEdit->setPlaceholderText("Task title");

    descriptionEdit = new QTextEdit(this);
    descriptionEdit->setPlaceholderText("Description (optional)");

    categoryCombo = new QComboBox(this);
    categoryCombo->addItems({"Work", "Study", "Personal", "Other"});

    deadlineEdit = new QDateEdit(this);
    deadlineEdit->setDate(QDate::currentDate());
    deadlineEdit->setCalendarPopup(true);

    acceptButton = new QPushButton("Add Task", this);
    cancelButton = new QPushButton("Cancel", this);

    auto *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(acceptButton);
    buttonLayout->addWidget(cancelButton);

    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(new QLabel("Title:", this));
    mainLayout->addWidget(titleEdit);
    mainLayout->addWidget(new QLabel("Description:", this));
    mainLayout->addWidget(descriptionEdit);
    mainLayout->addWidget(new QLabel("Category:", this));
    mainLayout->addWidget(categoryCombo);
    mainLayout->addWidget(new QLabel("Deadline:", this));
    mainLayout->addWidget(deadlineEdit);
    mainLayout->addLayout(buttonLayout);

    connect(acceptButton, &QPushButton::clicked, this, &AddTaskWidget::onAcceptClicked);
    connect(cancelButton, &QPushButton::clicked, this, [this]() {
        emit taskAdded(); // Или просто скрываем
        this->hide();
    });
}

void AddTaskWidget::onAcceptClicked() {
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
            emit taskAdded(); // Сообщаем, что задача добавлена
            // Можно очистить поля
            titleEdit->clear();
            descriptionEdit->clear();
            this->hide(); // Скрываем
        } else {
            QMessageBox::critical(this, "Error", "Failed to add task.");
        }
    } else {
        QMessageBox::critical(this, "Error", "Database is not initialized.");
    }
}