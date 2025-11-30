#include <QHBoxLayout>
#include <QPushButton>

#include "../windows/Registration.h"

#include <QLabel>

#include "interfaces/WindowOptions.h"
#include "styleloader/StyleLoader.h"


Registration::Registration(QWidget *parent) : QWidget(parent) {
    setWindowTitle(tr("Registration"));
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    setAttribute(Qt::WA_StyledBackground, true);

    const QPixmap pix(":/images/authorization.png");

    loginEdit = new QLineEdit(this);
    loginEdit->setPlaceholderText("ВВЕДИТЕ НОВЫЙ ЛОГИН");
    loginEdit->setFixedSize(420, 80);


    passwordEdit = new QLineEdit(this);
    passwordEdit->setPlaceholderText("ВВЕДИТЕ НОВЫЙ ПАРОЛЬ");
    passwordEdit->setFixedSize(420, 80);;

    registrationButton = new QPushButton(this);
    registrationButton->setFixedHeight(50);
    registrationButton->setText("СОЗДАТЬ НОВЫЙ АККАУНТ");


    auto *button = new QPushButton(this);
    button->setText("ВОЙТИ");



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

    //---------------------------------------------------BUTTON_BACK
    auto buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(button);
    buttonLayout->addStretch();

    //---------------------------------------------------BUTTON_REGISTRATION_BUTTON
    auto *registrationLayoutButton = new QHBoxLayout();
    registrationLayoutButton->addStretch();
    registrationLayoutButton->addWidget(registrationButton);
    registrationLayoutButton->addStretch();


    //---------------------------------------------------REGISTRATION
    auto *registrationLayout = new QVBoxLayout();
    registrationLayout->addStretch();
    registrationLayout->addStretch();
    registrationLayout->addStretch();
    registrationLayout->addStretch();
    registrationLayout->addStretch();
    registrationLayout->addStretch();
    registrationLayout->addStretch();
    registrationLayout->addStretch();
    registrationLayout->addStretch();
    registrationLayout->addStretch();
    registrationLayout->addStretch();
    registrationLayout->addStretch();
    registrationLayout->addStretch();
    registrationLayout->addLayout(loginLayout);
    registrationLayout->addStretch();
    registrationLayout->addLayout(passwordLayout);
    registrationLayout->addStretch();
    registrationLayout->addLayout(registrationLayoutButton);
    registrationLayout->addStretch();
    registrationLayout->addStretch();
    registrationLayout->addStretch();
    registrationLayout->addStretch();
    registrationLayout->addStretch();
    registrationLayout->addStretch();
    registrationLayout->addStretch();
    registrationLayout->addStretch();
    registrationLayout->addStretch();
    registrationLayout->addStretch();
    registrationLayout->addStretch();
    registrationLayout->addStretch();
    registrationLayout->addStretch();
    registrationLayout->addStretch();
    registrationLayout->addStretch();
    registrationLayout->addStretch();
    registrationLayout->addLayout(buttonLayout);
    registrationLayout->addStretch();

    //---------------------------------------------------PHOTO
    auto *photoLabel = new QLabel();
    photoLabel->setPixmap(pix.scaled(WINDOW_WIDTH / 2, WINDOW_HEIGHT, Qt::KeepAspectRatioByExpanding,
                                     Qt::SmoothTransformation));
    photoLabel->setAlignment(Qt::AlignCenter);

    //---------------------------------------------------MAINLAYOUT
    auto *mainLayout = new QHBoxLayout();
    mainLayout->addWidget(photoLabel);
    mainLayout->addLayout(registrationLayout);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    setLayout(mainLayout);

    connect(button, &QPushButton::clicked, this, &Registration::backToAuthorization);
    connect(registrationButton, &QPushButton::clicked, this, &Registration::registeringNewAccount);
    StyleLoader::loadStyleSheet(this, ":/styles/registration.qss");
}
