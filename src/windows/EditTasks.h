//
// Created by unf0r9et on 15.11.25.
//

#ifndef EDITTASKS_H
#define EDITTASKS_H
#include <QWidget>

class DatabaseManager;

class EditTasks : public QWidget {
    Q_OBJECT

public:
    explicit EditTasks(QWidget *parent = nullptr);
    void setDatabaseManager(DatabaseManager *dbManager);

    private:
    DatabaseManager *dbManager;
};


#endif //EDITTASKS_H
