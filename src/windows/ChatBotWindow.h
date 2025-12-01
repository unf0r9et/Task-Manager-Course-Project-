//
// Created by unf0r9et on 27.11.25.
//

#ifndef CHATBOTWINDOW_H
#define CHATBOTWINDOW_H

#include <QLabel>
#include <QTextEdit>
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


class ChatBotWindow : public QWidget, public DataBaseUser {
    Q_OBJECT

public:
    explicit ChatBotWindow(QWidget *parent = nullptr);

    int currentUserId = -1;

signals:
    void backToMenuClicked();

private:
    void sendRequest();

    void onAddTaskPressed();

    void onNotAddTaskPressed();

    void onBackButtonClicked();

    void resetWidget();

    QString lastResponse;
    QTextEdit *input;
    QLabel *output;
};


#endif //CHATBOTWINDOW_H
