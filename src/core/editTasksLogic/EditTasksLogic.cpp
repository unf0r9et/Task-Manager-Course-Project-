//
// Created by unf0r9et on 15.11.25.
//

#include <QMessageBox>

#include "AddTaskDialog.h"
#include "../windows/EditTasks.h"

void EditTasks::setDatabaseManager(DatabaseManager *dbManager) {
    this->dbManager = dbManager;
}

void EditTasks::onAddTaskButtonClicked() {
    if (!dbManager) {
        QMessageBox::critical(this, "Error", "Database is not initialized.");
        return;
    }
    AddTaskDialog dialog(dbManager, this);
    if (dialog.exec() == QDialog::Accepted) {
        showAllTasks();
    }
}

void EditTasks::showAllTasks() {

}
