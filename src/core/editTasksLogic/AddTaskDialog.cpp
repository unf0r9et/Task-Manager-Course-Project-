#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QDialogButtonBox>

#include "AddTaskDialog.h"
#include "databaseManager/DatabaseManager.h"

AddTaskDialog::AddTaskDialog(DatabaseManager *dbManager, QWidget *parent)
    : QDialog(parent), dbManager(dbManager) {
    setWindowTitle("Add Task");

    titleEdit = new QLineEdit(this);
    titleEdit->setPlaceholderText("Task title");

    descriptionEdit = new QTextEdit(this);
    descriptionEdit->setPlaceholderText("Description (optional)");

    categoryCombo = new QComboBox(this);
    categoryCombo->addItems({"Work", "Study", "Personal", "Other"});

    deadlineEdit = new QDateEdit(this);
    deadlineEdit->setDate(QDate::currentDate());
    deadlineEdit->setCalendarPopup(true);

    auto *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);

    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(new QLabel("Title:", this));
    mainLayout->addWidget(titleEdit);
    mainLayout->addWidget(new QLabel("Description:", this));
    mainLayout->addWidget(descriptionEdit);
    mainLayout->addWidget(new QLabel("Category:", this));
    mainLayout->addWidget(categoryCombo);
    mainLayout->addWidget(new QLabel("Deadline:", this));
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