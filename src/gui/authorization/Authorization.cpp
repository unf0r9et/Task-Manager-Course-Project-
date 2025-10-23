#include "interfaces/Interfaces.h"
#include <qcoreapplication.h>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QMouseEvent>


Authorization::Authorization(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Вход в систему");
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);


    auto *registrationButton = new QPushButton("Reg", this);
    auto *registrationLayout = new QHBoxLayout();
    registrationLayout->addStretch();
    registrationLayout->addWidget(registrationButton);
    registrationLayout->addStretch();


    auto *photoLabel = new QLabel();
    const QPixmap pix(":/images/authorization.png");
    photoLabel->setPixmap(pix.scaled(WINDOW_WIDTH/2, WINDOW_HEIGHT, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
    photoLabel->setAlignment(Qt::AlignCenter);


    loginEdit = new QLineEdit(this);
    loginEdit->setFixedWidth(200);
    passwordEdit = new QLineEdit(this);
    passwordEdit->setFixedWidth(200);
    passwordEdit->setEchoMode(QLineEdit::Password);

    auto *loginLabel = new QLabel("Логин:", this);
    auto *passwordLabel = new QLabel("Пароль:", this);

    loginButton = new QPushButton("Войти", this);
    loginButton->setObjectName("loginButton");
    loginButton->setFixedWidth(200);


    auto *loginLayout = new QHBoxLayout();
    loginLayout->addStretch();
    loginLayout->addWidget(loginLabel);
    loginLayout->addWidget(loginEdit);
    loginLayout->addStretch();


    auto *passwordLayout = new QHBoxLayout();
    passwordLayout->addStretch();
    passwordLayout->addWidget(passwordLabel);
    passwordLayout->addWidget(passwordEdit);
    passwordLayout->addStretch();

    auto buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(loginButton);
    buttonLayout->addStretch();


    auto *authorizationLayout = new QVBoxLayout();
    authorizationLayout->addStretch();
    authorizationLayout->addLayout(loginLayout);
    authorizationLayout->addLayout(passwordLayout);
    authorizationLayout->addLayout(buttonLayout);
    authorizationLayout->addLayout(registrationLayout);
    authorizationLayout->addStretch();

    auto *mainLayout = new QHBoxLayout();
    mainLayout->addWidget(photoLabel);
    mainLayout->addLayout(authorizationLayout);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    setLayout(mainLayout);

    loadStylesheet(":/styles/authorization.qss");
    connect(loginButton, &QPushButton::clicked, this, &Authorization::onLoginClicked);
    connect(registrationButton, &QPushButton::clicked, this, &Authorization::onRegisterClicked);
}


void Authorization::loadStylesheet(const QString &path) {
    QFile file(path);
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        const QString styleSheet = QLatin1String(file.readAll());
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

void Authorization::onRegisterClicked() {
    emit registerRequested();
}

