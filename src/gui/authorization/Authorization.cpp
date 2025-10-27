#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMessageBox>

#include "Authorization.h"
#include "interfaces/WindowOptions.h"
#include "StyleLoader.cpp"


Authorization::Authorization(QWidget *parent) : QWidget(parent) {
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    setObjectName("Authorization");
    setAttribute(Qt::WA_StyledBackground, true);

    const QPixmap pix(":/images/authorization.png");

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

    auto *registrationButton = new QPushButton("Reg", this);

    /*------------------------------------------------------------------------------------
    * -----------------------------------------------------------------------------------
    ------------------------------------------------------------------------------------*/

    //---------------------------------------------------LOGIN
    auto *loginLayout = new QHBoxLayout();
    loginLayout->addStretch();
    loginLayout->addWidget(loginLabel);
    loginLayout->addWidget(loginEdit);
    loginLayout->addStretch();

    //---------------------------------------------------PASSWORD
    auto *passwordLayout = new QHBoxLayout();
    passwordLayout->addStretch();
    passwordLayout->addWidget(passwordLabel);
    passwordLayout->addWidget(passwordEdit);
    passwordLayout->addStretch();

    //---------------------------------------------------BUTTON_ACCEPT
    auto buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(loginButton);
    buttonLayout->addStretch();

    //---------------------------------------------------BUTTON_REGISTRATION
    auto *registrationLayout = new QHBoxLayout();
    registrationLayout->addStretch();
    registrationLayout->addWidget(registrationButton);
    registrationLayout->addStretch();

    //---------------------------------------------------AUTHORIZATION
    auto *authorizationLayout = new QVBoxLayout();
    authorizationLayout->addStretch();
    authorizationLayout->addLayout(loginLayout);
    authorizationLayout->addLayout(passwordLayout);
    authorizationLayout->addLayout(buttonLayout);
    authorizationLayout->addLayout(registrationLayout);
    authorizationLayout->addStretch();

    //---------------------------------------------------PHOTO
    auto *photoLabel = new QLabel();
    photoLabel->setPixmap(pix.scaled(WINDOW_WIDTH / 2, WINDOW_HEIGHT, Qt::KeepAspectRatioByExpanding,
                                     Qt::SmoothTransformation));
    photoLabel->setAlignment(Qt::AlignCenter);

    //---------------------------------------------------MAINLAYOUT
    auto *mainLayout = new QHBoxLayout();
    mainLayout->addWidget(photoLabel);
    mainLayout->addLayout(authorizationLayout);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    setLayout(mainLayout);

    /*------------------------------------------------------------------------------------
     * -----------------------------------------------------------------------------------
     ------------------------------------------------------------------------------------*/

    connect(loginButton, &QPushButton::clicked, this, &Authorization::onLoginClicked);
    connect(registrationButton, &QPushButton::clicked, this, &Authorization::onRegisterClicked);

    StyleLoader::loadStyleSheet(this, ":/styles/authorization.qss");
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
