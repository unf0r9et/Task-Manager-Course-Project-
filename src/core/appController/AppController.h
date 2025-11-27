#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include <QObject>
#include <interfaces/Interfaces.h>
#include "databaseManager/DatabaseManager.h"

class AppController : public QObject {
    Q_OBJECT

public:
    explicit AppController(QStackedWidget *stack, QObject *parent = nullptr);
    int currentUserId = -1;
public slots:
    void showAuthorization();

    void showRegistration();

    void showApplicationMenu();

    void showEditTasks();

    void showChatBotWindow();

private:
    QStackedWidget *stack;
    Authorization *authorization;
    Registration *registration;
    ApplicationMenu *applicationMenu;
    EditTasks *editTasks;
    DatabaseManager dbManager;
    ChatBotWindow *chatBotWindow;
};


#endif //APPCONTROLLER_H
