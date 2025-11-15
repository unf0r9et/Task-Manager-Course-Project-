#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMessageBox>
#include "databaseManager/DatabaseManager.h"
#include "Authorization.h"

#include <QCryptographicHash>

#include "interfaces/WindowOptions.h"
#include "styleloader/StyleLoader.h"


Authorization::Authorization(QWidget *parent) : QWidget(parent) {
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    setObjectName("Authorization");
    setAttribute(Qt::WA_StyledBackground, true);

    const QPixmap pix(":/images/authorization.png");

    loginEdit = new QLineEdit(this);
    loginEdit->setPlaceholderText("LOGIN");
    loginEdit->setFixedWidth(200);

    passwordEdit = new QLineEdit(this);
    passwordEdit->setPlaceholderText("PASSWORD");
    passwordEdit->setFixedWidth(200);
    passwordEdit->setEchoMode(QLineEdit::Password);


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
    loginLayout->addWidget(loginEdit);
    loginLayout->addStretch();

    //---------------------------------------------------PASSWORD
    auto *passwordLayout = new QHBoxLayout();
    passwordLayout->addStretch();
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

void Authorization::setDatabaseManager(DatabaseManager *dbManager) {
    this->dbManager = dbManager;
}

void Authorization::onLoginClicked() {
    if (checkingLoginAndPassword())
        QMessageBox::information(this, "Успех", "Добро пожаловать, admin!");
    else
        QMessageBox::warning(this, "Ошибка", "Неверный логин или пароль.");
}


void Authorization::onRegisterClicked() {
    emit registerRequested();
}

bool Authorization::checkingLoginAndPassword() {
    QString username = loginEdit->text().trimmed();
    QString password = passwordEdit->text();

    if (username.isEmpty() || password.isEmpty()) {
        return false;
    }

    if (!dbManager) {
        return false;
    }

    QString storedHash = dbManager->getPasswordHash(username);

    if (storedHash.isEmpty()) {
        return false;
    }

    QString inputHash = QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex());

    return inputHash == storedHash;
}