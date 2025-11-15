#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <QWidget>

class Registration;
class QLineEdit;
class QPushButton;
class DatabaseManager;
class Authorization : public QWidget {
    Q_OBJECT

public:
    explicit Authorization(QWidget *parent = nullptr);
    void setDatabaseManager(DatabaseManager *dbManager);

signals:
    void registerRequested();

private slots:
    void onLoginClicked();

    void onRegisterClicked();

private:
    QLineEdit *loginEdit;
    QLineEdit *passwordEdit;
    QPushButton *loginButton;
    DatabaseManager *dbManager = nullptr;
    bool checkingLoginAndPassword();
};

#endif // AUTHORIZATION_H
