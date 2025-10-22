#include "interfaces/Interfaces.h"
#include <qcoreapplication.h>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QFile>

Authorization::Authorization(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Вход в систему");
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);


    loginEdit = new QLineEdit(this);
    loginEdit->setFixedWidth(200);
    passwordEdit = new QLineEdit(this);
    passwordEdit->setFixedWidth(200);
    passwordEdit->setEchoMode(QLineEdit::Password);

    auto *loginLabel = new QLabel("Логин:", this);
    auto *passwordLabel = new QLabel("Пароль:", this);
    loginButton = new QPushButton("Войти", this);
    loginButton->setFixedWidth(200);

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
    loadStylesheet(":/styles/authorization.qss");
    connect(loginButton, &QPushButton::clicked, this, &Authorization::onLoginClicked);
}


void Authorization::loadStylesheet(const QString &path) {
    QFile file(path);
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QString styleSheet = QLatin1String(file.readAll());
        this->setStyleSheet(styleSheet);
        file.close();
    }
}


void Authorization::onLoginClicked() {
    if (loginEdit->text() == "admin" && passwordEdit->text() == "1234")
        QMessageBox::information(this, "Успех", "Добро пожаловать, admin!");
    else
        QMessageBox::warning(this, "Ошибка", "Неверный логин или пароль.");
}
