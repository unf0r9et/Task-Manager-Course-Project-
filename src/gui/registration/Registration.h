#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QLineEdit>
#include <QWidget>

class DatabaseManager;

class Registration : public QWidget {
    Q_OBJECT

public:
    explicit Registration(QWidget *parent = nullptr);
    void setDatabaseManager(DatabaseManager *dbManager);
signals:
    void authorizationRequested();

private:
    QLineEdit *loginEdit = nullptr;
    QLineEdit *passwordEdit = nullptr;
    QPushButton *registrationButton = nullptr;
    DatabaseManager *dbManager = nullptr;
    void backToAuthorization();
    void registeringNewAccount();
};


#endif //REGISTRATION_H
