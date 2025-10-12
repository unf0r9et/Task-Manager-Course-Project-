#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <QWidget>

class QLineEdit;
class QPushButton;

class AuthorizationMenu : public QWidget {
    Q_OBJECT

public:
    explicit AuthorizationMenu(QWidget *parent = nullptr);
private slots:
    void onLoginClicked();

private:
    QLineEdit *loginEdit;
    QLineEdit *passwordEdit;
    QPushButton *loginButton;
};

#endif // AUTHORIZATION_H