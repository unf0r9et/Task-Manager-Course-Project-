//
// Created by unf0r9et on 15.11.25.
//

#include <QMessageBox>

#include "../windows/EditTasks.h"
#include "databaseManager/DatabaseManager.h"
#include "taskCardWidget/TaskCardWidget.h"
#include "interfaces/WindowOptions.h"
#include <QVBoxLayout>
#include <QScrollArea>
#include <QMessageBox>
#include "addTaskWidgetMenu/AddTaskWidgetMenu.h"
#include "editingTaskMenu/EditingTaskMenu.h"

void EditTasks::setDatabaseManager(DatabaseManager *dbManager) {
    this->dbManager = dbManager;
}

void EditTasks::onAddTaskClicked() {
    if (!dbManager) {
        QMessageBox::critical(this, "Error", "Database is not initialized.");
        return;
    }

    if (!addTaskWidget) {
        addTaskWidget = new AddTaskWidgetMenu(dbManager, this);
        addTaskWidget->setGeometry(215, WINDOW_HEIGHT-900 , 550, 800);
        connect(addTaskWidget, &AddTaskWidgetMenu::taskWasAdded, this, [this]() {
            showAllTasks();
            addTaskWidget->hide();
            addTaskWidget = nullptr;
        });

        connect(addTaskWidget, &AddTaskWidgetMenu::taskWasNotAdded, this, [this]() {
            addTaskWidget->hide();
            addTaskWidget = nullptr;
        });
    }
    addTaskWidget->show();
}


void EditTasks::showAllTasks() {
    clearTaskCards();

    if (!dbManager) return;

    QSqlQuery query = dbManager->getAllTasks();

    while (query.next()) {
        int id = query.value("id").toInt();
        QString title = query.value("title").toString();
        QString description = query.value("description").toString();
        QString category = query.value("category").toString();
        QDate deadline = query.value("deadline").toDate();
        bool completed = query.value("completed").toBool();

        addTaskCard(id, title, description, category, deadline, completed);
    }
}

void EditTasks::onBackButtonClicked() {
    if (addTaskWidget) {
        addTaskWidget->hide();
        addTaskWidget = nullptr;
    }
    emit backToMenuClicked();
}

void EditTasks::clearTaskCards() {
    if (!tasksLayout) {
        return;
    }

    QLayoutItem *child;
    while ((child = tasksLayout->takeAt(0)) != nullptr) {
        if (child->widget()) {
            child->widget()->deleteLater();
        }
    }
}

void EditTasks::addTaskCard(int taskId, const QString &title, const QString &description,
                            const QString &category, const QDate &deadline, bool completed) {
    auto *card = new TaskCardWidget(taskId, title, description, category, deadline, completed);
    tasksLayout->insertWidget(tasksLayout->count() - 1, card);

    connect(card, &TaskCardWidget::editingRequested, this, &EditTasks::onEditingTask);
    connect(card, &TaskCardWidget::completedChanged, this, &EditTasks::onCompletedChanged);
}

void EditTasks::onEditingTask(int taskId) {

    if (dbManager && dbManager->deleteTask(taskId)) {
        showAllTasks();
    } else {
        QMessageBox::critical(this, "Error", "Failed to delete task.");
    }
}

void EditTasks::onCompletedChanged(int taskId, bool completed) {
    if (dbManager) {
        // Здесь можно обновить задачу в БД
        // dbManager->updateTask(..., completed)
        // Пока просто покажем сообщение
        QMessageBox::information(this, "Status", "Task status updated.");
    }
}
