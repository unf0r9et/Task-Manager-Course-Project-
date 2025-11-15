//
// Created by unf0r9et on 15.11.25.
//
#include <QCryptographicHash>
#include <QMessageBox>
#include <QPushButton>

#include "databaseManager/DatabaseManager.h"
#include "../../windows/Registration.h"

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
