//
// Created by unf0r9et on 15.11.25.
//

#include <QMessageBox>

#include "../windows/EditTasks.h"
#include "databaseManager/DatabaseManager.h"
#include "TaskCardWidget.h"
#include "interfaces/WindowOptions.h"
#include <QVBoxLayout>
#include <QScrollArea>
#include <QMessageBox>
#include "../../windows/widgets/AddTaskWidgetMenu.h"
#include "../../windows/widgets/EditingTaskMenu.h"

void EditTasks::onAddTaskClicked() {
    if (!dbManager) {
        QMessageBox::critical(this, "Error", "Database is not initialized.");
        return;
    }

    if (!addTaskWidget) {
        addTaskWidget = new AddTaskWidgetMenu(dbManager, currentUserId, this);
        addTaskWidget->setGeometry(215, WINDOW_HEIGHT - 900, 550, 800);
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

    QSqlQuery query = dbManager->getTasksByUser(currentUserId);

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
    if (editingTaskWidget) {
        addTaskButton->show();
        editingTaskWidget->hide();
        editingTaskWidget = nullptr;
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
    if (!dbManager) {
        QMessageBox::critical(this, "Error", "Database is not initialized.");
        return;
    }
    addTaskButton->hide();
    if (!editingTaskWidget) {
        editingTaskWidget = new EditingTaskMenu(dbManager, this, taskId);
        editingTaskWidget->setGeometry(215, WINDOW_HEIGHT - 900, 550, 800);

        connect(editingTaskWidget, &EditingTaskMenu::taskWasEdited, this, &EditTasks::changingTask);

        connect(editingTaskWidget, &EditingTaskMenu::taskWasNotEdited, this, &EditTasks::changingTask);

        connect(editingTaskWidget, &EditingTaskMenu::taskWasDeleted, this, &EditTasks::changingTask);
    }

    editingTaskWidget->show();
}

void EditTasks::onCompletedChanged(int taskId, bool completed) {
    if (dbManager && dbManager->updateTaskCompleteness(taskId, completed)) {
        QMessageBox::information(this, "Status", "Task status updated.");
    }
}

void EditTasks::changingTask() {
    addTaskButton->show();
    editingTaskWidget->hide();
    editingTaskWidget = nullptr;
    showAllTasks();
}
