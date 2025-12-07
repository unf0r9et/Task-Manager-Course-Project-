//
// Created by unf0r9et on 15.11.25.
//

#include <QCryptographicHash>
#include <QLineEdit>
#include <QMessageBox>

#include "../windows/Authorization.h"
#include "databaseManager/DatabaseManager.h"

void Authorization::onLoginClicked() {
    if (checkingLoginAndPassword()) {
        loginEdit->setText("");
        passwordEdit->setText("");
        emit loginSuccessful();
    } else
        QMessageBox::warning(this, "Ошибка", "Неверный логин или пароль.");
}


void Authorization::onRegisterClicked() {
    emit registerRequested();
}

bool Authorization::checkingLoginAndPassword() {
    QString username = loginEdit->text().trimmed();
    QString password = passwordEdit->text();
    userLogin = username;
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
