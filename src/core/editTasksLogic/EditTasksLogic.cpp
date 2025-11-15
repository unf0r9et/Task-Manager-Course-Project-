//
// Created by unf0r9et on 15.11.25.
//

#include <QMessageBox>

#include "../windows/EditTasks.h"

void EditTasks::setDatabaseManager(DatabaseManager *dbManager) {
    this->dbManager = dbManager;
}

void EditTasks::onAddTaskButtonClicked() {
    if (!dbManager) {
        QMessageBox::critical(this, "Error", "Database is not initialized.");
        return;
    }
}

void EditTasks::showAllTasks() {

}
