#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <QWidget>

class Registration;
class QLineEdit;
class QPushButton;

class Authorization : public QWidget {
    Q_OBJECT

public:
    explicit Authorization(QWidget *parent = nullptr);

signals:
    void registerRequested();

private slots:
    void onLoginClicked();

    void onRegisterClicked();

private:
    QLineEdit *loginEdit;
    QLineEdit *passwordEdit;
    QPushButton *loginButton;
};

#endif // AUTHORIZATION_H
