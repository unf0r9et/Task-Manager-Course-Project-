#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include <QObject>
#include <interfaces/Interfaces.h>
#include "databaseManager/DatabaseManager.h"

class AppController : public QObject {
    Q_OBJECT

public:
    explicit AppController(QStackedWidget *stack, QObject *parent = nullptr);

public slots:
    void showAuthorization();

    void showRegistration();

private:
    QStackedWidget *stack;
    Authorization *authorization;
    Registration *registration;
    DatabaseManager dbManager;
};


#endif //APPCONTROLLER_H
