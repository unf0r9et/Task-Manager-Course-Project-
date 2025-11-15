#include <QHBoxLayout>
#include <QPushButton>


#include "Registration.h"
#include "databaseManager/DatabaseManager.h"
#include <QCryptographicHash>
#include <QLineEdit>
#include <QMessageBox>

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

    this->setStyleSheet(R"(
QPushButton { color: 000000; })");
    //connect(button, &QPushButton::clicked, this, &Registration::backToAuthorization);
    connect(registrationButton, &QPushButton::clicked, this, &Registration::registeringNewAccount);
}

void Registration::backToAuthorization() {
    emit authorizationRequested();
}

void Registration::setDatabaseManager(DatabaseManager *dbManager) {
    this->dbManager = dbManager;
}

void Registration::registeringNewAccount() {
    if (!dbManager) {
        QMessageBox::critical(this, "Error", "Database manager is not set!");
        return;
    }
    QString username = loginEdit->text().trimmed();
    QString password = passwordEdit->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Error", "Username and password cannot be empty.");
        return;
    }

    if (dbManager) {
        if (dbManager->userExists(username)) {
            QMessageBox::warning(this, "Error", "Username already exists.");
            return;
        }

        QString passwordHash = QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex());
        if (dbManager->addUser(username, passwordHash)) {
            QMessageBox::information(this, "Success", "User registered successfully!");
            emit authorizationRequested();
        } else {
            QMessageBox::critical(this, "Error", "Failed to register user.");
        }
    } else {
        QMessageBox::critical(this, "Error", "Database is not initialized.");
    }
}
