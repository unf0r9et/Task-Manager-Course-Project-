#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QLineEdit>
#include <QWidget>
#include "databaseManager/dataBaseUser/DataBaseUser.h"

class DatabaseManager;

class Registration : public QWidget, public DataBaseUser {
    Q_OBJECT

public:
    explicit Registration(QWidget *parent = nullptr);

signals:
    void authorizationRequested();

private:
    QLineEdit *loginEdit = nullptr;
    QLineEdit *passwordEdit = nullptr;
    QPushButton *registrationButton = nullptr;
    void backToAuthorization();
    void registeringNewAccount();
};


#endif //REGISTRATION_H
