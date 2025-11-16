#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QDialogButtonBox>

#include "AddTaskDialog.h"
#include "databaseManager/DatabaseManager.h"

AddTaskDialog::AddTaskDialog(DatabaseManager *dbManager, QWidget *parent)
    : QDialog(parent), dbManager(dbManager) {
    setWindowTitle("Добавить задачу");
    setFixedSize(400, 700);
    setAttribute(Qt::WA_StyledBackground, true);
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    titleEdit = new QLineEdit(this);
    titleEdit->setPlaceholderText("Что будем делать?");

    descriptionEdit = new QTextEdit(this);
    descriptionEdit->setPlaceholderText("Есть идеи?");

    categoryCombo = new QComboBox(this);
    categoryCombo->addItems({"Работа", "Учёба", "Хобби", "Другое"});

    deadlineEdit = new QDateEdit(this);
    deadlineEdit->setDate(QDate::currentDate());
    deadlineEdit->setCalendarPopup(true);

    auto *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);

    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(new QLabel("Название:", this));
    mainLayout->addWidget(titleEdit);
    mainLayout->addWidget(new QLabel("Описание:", this));
    mainLayout->addWidget(descriptionEdit);
    mainLayout->addWidget(new QLabel("Категория:", this));
    mainLayout->addWidget(categoryCombo);
    mainLayout->addWidget(new QLabel("Дедлайн:", this));
    mainLayout->addWidget(deadlineEdit);
    mainLayout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &AddTaskDialog::onAcceptClicked);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &AddTaskDialog::reject);
}

void AddTaskDialog::onAcceptClicked() {
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
            accept();
        } else {
            QMessageBox::critical(this, "Error", "Failed to add task.");
        }
    } else {
        QMessageBox::critical(this, "Error", "Database is not initialized.");
    }
}
