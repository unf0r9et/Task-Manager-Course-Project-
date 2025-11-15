//
// Created by unf0r9et on 15.11.25.
//

#ifndef EDITTASKS_H
#define EDITTASKS_H
#include <QWidget>

class DatabaseManager;
class QPushButton;

class EditTasks : public QWidget {
    Q_OBJECT

public:
    explicit EditTasks(QWidget *parent = nullptr);
    void setDatabaseManager(DatabaseManager *dbManager);

    private:
    DatabaseManager *dbManager;
    QPushButton *addTaskButton = nullptr;
    void onAddTaskButtonClicked();

    void showAllTasks();
};


#endif //EDITTASKS_H
