#include <QHBoxLayout>
#include <QPushButton>

#include "../windows/Registration.h"
#include "interfaces/WindowOptions.h"
#include "styleloader/StyleLoader.h"


Registration::Registration(QWidget *parent) : QWidget(parent) {
    setWindowTitle(tr("Registration"));
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    loginEdit = new QLineEdit(this);
    loginEdit->setPlaceholderText("ENTER NEW LOGIN");
    loginEdit->setFixedWidth(200);


    passwordEdit = new QLineEdit(this);
    passwordEdit->setPlaceholderText("ENTER NEW PASSWORD");
    passwordEdit->setFixedWidth(200);

    registrationButton = new QPushButton(this);
    registrationButton->setFixedWidth(200);


    // auto *button = new QPushButton(this);
    // button->setText("BACK");
    // button->setFixedWidth(200);
    // button->setFixedHeight(100);

    auto *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();

    //buttonLayout->addWidget(button);
    buttonLayout->addStretch();

    auto *mainLayout = new QVBoxLayout();
    mainLayout->addStretch();
    //mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(loginEdit);
    mainLayout->addWidget(passwordEdit);
    mainLayout->addWidget(registrationButton);
    mainLayout->addStretch();

    setLayout(mainLayout);

    //connect(button, &QPushButton::clicked, this, &Registration::backToAuthorization);
    connect(registrationButton, &QPushButton::clicked, this, &Registration::registeringNewAccount);
 //   StyleLoader::loadStyleSheet(this, "");
}
