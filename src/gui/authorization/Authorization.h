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
private slots:
    void onLoginClicked();
    void onRegisterClicked();

private:
    void loadStylesheet(const QString &path);
    QLineEdit *loginEdit;
    QLineEdit *passwordEdit;
    QPushButton *loginButton;
};

#endif // AUTHORIZATION_H