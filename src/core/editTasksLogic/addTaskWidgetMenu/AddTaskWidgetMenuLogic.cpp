//
// Created by unf0r9et on 27.11.25.
//

#include "AddTaskWidgetMenu.h"
#include "databaseManager/DatabaseManager.h"

#include <QMessageBox>

void AddTaskWidgetMenu::onAcceptClicked() {
    QString title = titleEdit->text().trimmed();
    if (title.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Заголовок не может быть пустым.");
        return;
    }

    QString description = descriptionEdit->toPlainText();
    QString category = categoryCombo->currentText();
    QDate deadline = deadlineEdit->date();

    if (dbManager) {
        if (dbManager->addTask(currentUserId, title, description, category, deadline)) {
            emit taskWasAdded();
        } else {
            QMessageBox::critical(this, "Ошибка", "Не удалось добавить задачу.");
        }
    } else {
        QMessageBox::critical(this, "Ошибка", "База данных не инициализирована.");
    }
}

void AddTaskWidgetMenu::onRejectClicked() {
    emit taskWasNotAdded();
}
