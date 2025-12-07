//
// Created by unf0r9et on 27.11.25.
//
#include "EditingTaskMenu.h"
#include "databaseManager/DatabaseManager.h"
#include <QMessageBox>

void EditingTaskMenu::onAcceptClicked() {
    QString title = titleEdit->text().trimmed();
    if (title.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Заголовок не может быть пустым.");
        return;
    }
    QString description = descriptionEdit->toPlainText();
    QString category = categoryCombo->currentText();
    QDate deadline = deadlineEdit->date();
    if (dbManager) {
        if (dbManager->updateTask(taskId, title, description, category, deadline)) {
            emit taskWasEdited();
        } else {
            QMessageBox::critical(this, "Ошибка", "Не удалось изменить задачу.");
        }
    } else {
        QMessageBox::critical(this, "Ошибка", "База данных не инициализирована.");
    }
}

void EditingTaskMenu::onRejectClicked() {
    emit taskWasNotEdited();
}

void EditingTaskMenu::onDeleteClicked() {
    if (dbManager && dbManager->deleteTask(taskId)) {
        emit taskWasDeleted();
    } else {
        QMessageBox::critical(this, "Ошибка", "Не удалось удалить задачу.");
    }
}
