//
// Created by unf0r9et on 27.11.25.
//

#include "AddTaskWidgetMenu.h"
#include "databaseManager/DatabaseManager.h"

#include <QMessageBox>

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
        if (dbManager->addTask(currentUserId, title, description, category, deadline)) {
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
