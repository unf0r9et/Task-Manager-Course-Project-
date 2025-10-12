#include "interface/AuthorizationMenu.h"
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMessageBox>

AuthorizationMenu::AuthorizationMenu(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Вход в систему");
    setFixedSize(800, 600);


    loginEdit = new QLineEdit(this);
    loginEdit->setFixedWidth(200);
    passwordEdit = new QLineEdit(this);
    passwordEdit->setFixedWidth(200);
    passwordEdit->setEchoMode(QLineEdit::Password);

    auto *loginLabel = new QLabel("Логин:", this);
    auto *passwordLabel = new QLabel("Пароль:", this);
    loginButton = new QPushButton("Войти", this);
    loginButton->setFixedWidth(200);
    loginButton->setStyleSheet("QPushButton {"
                             "    background-color: #2196F3;"
                             "    color: white;"
                             "    border-radius: 5px;"
                             "}"
                             "QPushButton:hover {"
                             "    background-color: #1976D2;"
                             "}"
                             "QPushButton:pressed {"
                             "    background-color: #0D47A1;"
                             "}");

    auto *mainLayout = new QVBoxLayout();

    auto *formWidget = new QWidget(this);
    auto *formLayout = new QVBoxLayout(formWidget);


    auto *loginLayout = new QHBoxLayout();
    auto *passwordLayout = new QHBoxLayout();

    loginLayout->addWidget(loginLabel);
    loginLayout->addSpacing(17);
    loginLayout->addWidget(loginEdit);
    loginLayout->addStretch();



    passwordLayout->addWidget(passwordLabel);
    passwordLayout->addSpacing(8);
    passwordLayout->addWidget(passwordEdit);
    passwordLayout->addStretch();


    formLayout->addLayout(loginLayout);
    formLayout->addSpacing(20);
    formLayout->addLayout(passwordLayout);
    formLayout->addSpacing(20);
    formLayout->addWidget(loginButton, 1, Qt::AlignRight);

    mainLayout->addStretch();
    mainLayout->addWidget(formWidget,0 ,Qt::AlignHCenter);
    mainLayout->addStretch();

    setLayout(mainLayout);

    connect(loginButton, &QPushButton::clicked, this, &AuthorizationMenu::onLoginClicked);
}

void AuthorizationMenu::onLoginClicked() {
    if (loginEdit->text() == "admin" && passwordEdit->text() == "1234")
        QMessageBox::information(this, "Успех", "Добро пожаловать, admin!");
    else
        QMessageBox::warning(this, "Ошибка", "Неверный логин или пароль.");
}
