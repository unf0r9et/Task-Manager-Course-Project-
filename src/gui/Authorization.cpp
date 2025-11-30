#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>

#include "../windows/Authorization.h"
#include "interfaces/WindowOptions.h"
#include "styleloader/StyleLoader.h"


Authorization::Authorization(QWidget *parent) : QWidget(parent) {
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    setObjectName("Authorization");
    setAttribute(Qt::WA_StyledBackground, true);


    const QPixmap pix(":/images/authorization.png");
    const QPixmap LOGO(":/icons/LOGO.png");
    const QPixmap man(":/icons/man.png");
    const QPixmap lock(":/icons/lock.png");

    auto *manLayout = new QLabel();
    manLayout->setPixmap(man.scaled(40, 40, Qt::KeepAspectRatioByExpanding,
                                    Qt::SmoothTransformation));
    manLayout->setAlignment(Qt::AlignCenter);

    auto *lockLayout = new QLabel();
    lockLayout->setPixmap(lock.scaled(40, 40, Qt::KeepAspectRatioByExpanding,
                                      Qt::SmoothTransformation));
    lockLayout->setAlignment(Qt::AlignCenter);


    loginEdit = new QLineEdit(this);
    loginEdit->setPlaceholderText("ВВЕДИТЕ ЛОГИН");
    loginEdit->setFixedSize(420, 80);

    passwordEdit = new QLineEdit(this);
    passwordEdit->setPlaceholderText("ВВЕДИТЕ ПАРОЛЬ");
    passwordEdit->setFixedSize(420, 80);
    passwordEdit->setEchoMode(QLineEdit::Password);


    loginButton = new QPushButton("ВОЙТИ", this);
    loginButton->setObjectName("loginButton");
    loginButton->setFixedSize(150, 50);

    auto *registrationButton = new QPushButton("РЕГИСТРАЦИЯ", this);

    /*------------------------------------------------------------------------------------
    * -----------------------------------------------------------------------------------
    ------------------------------------------------------------------------------------*/

    //---------------------------------------------------LOGIN
    auto *loginLayout = new QHBoxLayout();
    loginLayout->addStretch();
    loginLayout->addWidget(manLayout);
    loginLayout->addWidget(loginEdit);
    loginLayout->addStretch();
    loginLayout->setSpacing(15);


    //---------------------------------------------------PASSWORD
    auto *passwordLayout = new QHBoxLayout();
    passwordLayout->addStretch();
    passwordLayout->addWidget(lockLayout);
    passwordLayout->addWidget(passwordEdit);
    passwordLayout->addStretch();
    passwordLayout->setSpacing(15);

    //---------------------------------------------------BUTTON_ACCEPT
    auto buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addSpacing(325);
    buttonLayout->addWidget(loginButton);
    buttonLayout->addStretch();

    //---------------------------------------------------BUTTON_REGISTRATION
    auto *registrationLayout = new QHBoxLayout();
    registrationLayout->addStretch();
    registrationLayout->addWidget(registrationButton);
    registrationLayout->addStretch();

    //---------------------------------------------------LOGO_LAYOUT

    auto *logoLayout = new QLabel();
    logoLayout->setPixmap(LOGO.scaled(600, 120, Qt::KeepAspectRatioByExpanding,
                                      Qt::SmoothTransformation));
    logoLayout->setAlignment(Qt::AlignCenter);

    //---------------------------------------------------AUTHORIZATION
    auto *authorizationLayout = new QVBoxLayout();
    authorizationLayout->addStretch();
    authorizationLayout->addStretch();
    authorizationLayout->addStretch();
    authorizationLayout->addStretch();
    authorizationLayout->addWidget(logoLayout);
    authorizationLayout->addStretch();
    authorizationLayout->addStretch();
    authorizationLayout->addStretch();
    authorizationLayout->addStretch();
    authorizationLayout->addStretch();
    authorizationLayout->addStretch();
    authorizationLayout->addStretch();
    authorizationLayout->addStretch();
    authorizationLayout->addStretch();
    authorizationLayout->addLayout(loginLayout);
    authorizationLayout->addStretch();
    authorizationLayout->addLayout(passwordLayout);
    authorizationLayout->addStretch();
    authorizationLayout->addLayout(buttonLayout);
    authorizationLayout->addStretch();
    authorizationLayout->addStretch();
    authorizationLayout->addStretch();
    authorizationLayout->addStretch();
    authorizationLayout->addStretch();
    authorizationLayout->addStretch();
    authorizationLayout->addStretch();
    authorizationLayout->addStretch();
    authorizationLayout->addStretch();
    authorizationLayout->addStretch();
    authorizationLayout->addStretch();
    authorizationLayout->addStretch();
    authorizationLayout->addStretch();
    authorizationLayout->addStretch();
    authorizationLayout->addStretch();
    authorizationLayout->addStretch();
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
