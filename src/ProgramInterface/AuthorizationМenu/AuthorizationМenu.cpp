#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMessageBox>
#include "Interface/AuthorizationMenu.h"

void AuthorizationMenu() {
    QWidget *window = new QWidget();
    window->setWindowTitle("Вход в систему");

    auto *loginEdit = new QLineEdit();
    auto *passwordEdit = new QLineEdit();
    passwordEdit->setEchoMode(QLineEdit::Password);

    auto *loginLabel = new QLabel("Логин:");
    auto *passwordLabel = new QLabel("Пароль:");
    QPushButton *loginButton = new QPushButton("Войти");

    QVBoxLayout *mainLayout = new QVBoxLayout();
    QHBoxLayout *loginLayout = new QHBoxLayout();
    QHBoxLayout *passwordLayout = new QHBoxLayout();

    loginLayout->addWidget(loginLabel);
    loginLayout->addWidget(loginEdit);
    passwordLayout->addWidget(passwordLabel);
    passwordLayout->addWidget(passwordEdit);

    mainLayout->addLayout(loginLayout);
    mainLayout->addLayout(passwordLayout);
    mainLayout->addWidget(loginButton);

    window->setLayout(mainLayout);

    QObject::connect(loginButton, &QPushButton::clicked, [=]() {
        QString login = loginEdit->text();
        QString password = passwordEdit->text();

        if (login == "admin" && password == "1234")
            QMessageBox::information(window, "Успех", "Добро пожаловать, admin!");
        else
            QMessageBox::warning(window, "Ошибка", "Неверный логин или пароль.");
    });

    window->resize(300, 150);
    window->show();
}
