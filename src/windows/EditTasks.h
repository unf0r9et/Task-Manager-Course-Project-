#ifndef EDITTASKS_H
#define EDITTASKS_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QSqlQuery>
#include "databaseManager/dataBaseUser/DataBaseUser.h"

class DatabaseManager;
class TaskCardWidget;
class AddTaskWidgetMenu;
class EditingTaskMenu;

class EditTasks : public QWidget, public DataBaseUser {
    Q_OBJECT

public:
    explicit EditTasks(QWidget *parent = nullptr);

    void showAllTasks();

    int currentUserId = -1;

signals:
    void backToMenuClicked();

private slots:
    void onAddTaskClicked();

    void onBackButtonClicked();

    void onEditingTask(int taskId);

    void onCompletedChanged(int taskId, bool completed);

    void changingTask();

private:
    QPushButton *addTaskButton = nullptr;
    QPushButton *backToMenuButton = nullptr;
    QScrollArea *scrollArea = nullptr;
    QWidget *tasksContainer = nullptr;
    QVBoxLayout *tasksLayout = nullptr;
    AddTaskWidgetMenu *addTaskWidget = nullptr;
    EditingTaskMenu *editingTaskWidget = nullptr;

    void clearTaskCards();

    void addTaskCard(int taskId, const QString &title, const QString &description,
                     const QString &category, const QDate &deadline, bool completed);
};

#endif // EDITTASKS_H
