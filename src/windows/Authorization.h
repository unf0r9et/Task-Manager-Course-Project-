#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <QWidget>
#include "databaseManager/dataBaseUser/DataBaseUser.h"

class Registration;
class QLineEdit;
class QPushButton;
class DatabaseManager;

class Authorization : public QWidget, public DataBaseUser {
    Q_OBJECT

public:
    explicit Authorization(QWidget *parent = nullptr);
    QString userLogin;
signals:
    void registerRequested();
    void loginSuccessful();

private slots:
    void onLoginClicked();

    void onRegisterClicked();

private:
    QLineEdit *loginEdit;
    QLineEdit *passwordEdit;
    QPushButton *loginButton;
    bool checkingLoginAndPassword();
};

#endif // AUTHORIZATION_H
