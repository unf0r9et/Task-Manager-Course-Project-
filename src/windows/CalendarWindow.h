//
// Created by unf0r9et on 29.11.25.
//

#ifndef CALENDARWINDOW_H
#define CALENDARWINDOW_H

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

class CalendarWindow : public QWidget, public DataBaseUser {
    Q_OBJECT

public:
    explicit CalendarWindow(QWidget *parent = nullptr);

    int currentUserId = -1;

    signals:
        void backToMenuClicked();

private slots:

    void onBackButtonClicked();

};



#endif //CALENDARWINDOW_H
