#ifndef EDITTASKS_H
#define EDITTASKS_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QSqlQuery>

class DatabaseManager;
class TaskCardWidget;

class EditTasks : public QWidget {
    Q_OBJECT

public:
    explicit EditTasks(QWidget *parent = nullptr);
    void setDatabaseManager(DatabaseManager *dbManager);

private slots:
    void onAddTaskClicked();
    void onDeleteTask(int taskId);
    void onCompletedChanged(int taskId, bool completed);

private:
    DatabaseManager *dbManager = nullptr;
    QPushButton *addTaskButton = nullptr;
    QScrollArea *scrollArea = nullptr;
    QWidget *tasksContainer = nullptr;
    QVBoxLayout *tasksLayout = nullptr;

    void showAllTasks();
    void clearTaskCards();
    void addTaskCard(int taskId, const QString &title, const QString &description,
                     const QString &category, const QDate &deadline, bool completed);
};

#endif // EDITTASKS_H