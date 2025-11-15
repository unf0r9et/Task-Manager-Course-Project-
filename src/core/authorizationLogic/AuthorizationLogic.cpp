//
// Created by unf0r9et on 15.11.25.
//

#include <QCryptographicHash>
#include <QLineEdit>
#include <QMessageBox>

#include "../../windows/Authorization.h"
#include "databaseManager/DatabaseManager.h"

void Authorization::setDatabaseManager(DatabaseManager *dbManager) {
    this->dbManager = dbManager;
}

void Authorization::onLoginClicked() {
    if (checkingLoginAndPassword())
        emit loginSuccessful();
    else
        QMessageBox::warning(this, "Error", "Incorrect login or password.");
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