//
// Created by unf0r9et on 15.11.25.
//
#include <QCryptographicHash>
#include <QMessageBox>
#include <QPushButton>

#include "databaseManager/DatabaseManager.h"
#include "../windows/Registration.h"

void Registration::backToAuthorization() {
    loginEdit->setText("");
    passwordEdit->setText("");
    emit authorizationRequested();
}

void Registration::registeringNewAccount() {
    if (!dbManager) {
        QMessageBox::critical(this, "Ошибка", "Менеджер базы данных не настроен!");
        return;
    }
    QString username = loginEdit->text().trimmed();
    QString password = passwordEdit->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Имя пользователя и пароль не могут быть пустыми.");
        return;
    }

    if (dbManager) {
        if (dbManager->userExists(username)) {
            QMessageBox::warning(this, "Ошибка", "Имя пользователя уже существует.");
            return;
        }

        QString passwordHash = QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex());
        if (dbManager->addUser(username, passwordHash)) {
            QMessageBox::information(this, "Успех", "Пользователь успешно зарегистрирован!");
            backToAuthorization();
        } else {
            QMessageBox::critical(this, "Ошибка", "Не удалось зарегистрировать пользователя.");
        }
    } else {
        QMessageBox::critical(this, "Ошибка", "База данных не инициализирована.");
    }
}
