#include "DatabaseManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QStandardPaths>
#include <QDir>
#include <QCryptographicHash>
#include <QDebug>

DatabaseManager::DatabaseManager(QObject *parent)
    : QObject(parent) {
    db = QSqlDatabase::addDatabase("QSQLITE");
}

bool DatabaseManager::initDatabase() {
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(path);
    db.setDatabaseName(path + "/taskmanager.db");

    if (!db.open()) {
        qDebug() << "Failed to open database:" << db.lastError().text();
        return false;
    }

    QSqlQuery query;
    if (!query.exec("CREATE TABLE IF NOT EXISTS users ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "username TEXT UNIQUE NOT NULL,"
                    "password_hash TEXT NOT NULL,"
                    "created_at DATETIME DEFAULT CURRENT_TIMESTAMP"
                    ")")) {
        qDebug() << "Failed to create table:" << query.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseManager::addUser(const QString &username, const QString &passwordHash) {
    QSqlQuery query;
    query.prepare("INSERT INTO users (username, password_hash) VALUES (?, ?)");
    query.addBindValue(username);
    query.addBindValue(passwordHash);

    if (!query.exec()) {
        qDebug() << "Failed to add user:" << query.lastError().text();
        return false;
    }
    return true;
}

bool DatabaseManager::userExists(const QString &username) {
    QSqlQuery query;
    query.prepare("SELECT 1 FROM users WHERE username = ?");
    query.addBindValue(username);
    query.exec();
    return query.next();
}

QString DatabaseManager::getPasswordHash(const QString &username) {
    QSqlQuery query;
    query.prepare("SELECT password_hash FROM users WHERE username = ?");
    query.addBindValue(username);
    if (query.exec() && query.next()) {
        return query.value(0).toString();
    }
    return QString();
}