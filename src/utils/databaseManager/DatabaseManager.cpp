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
    db.setDatabaseName("/home/unf0r9et/myProject/CourseProject/TaskManager/data/taskmanager.db");

    if (!db.open()) {
        qDebug() << "Failed to open database:" << db.lastError().text();
        return false;
    }

    QSqlQuery query;

    //---------------------ТАБЛИЦА-ДЛЯ-ПОЛЬЗОВАТЕЛЕЙ---------------------
    if (!query.exec("CREATE TABLE IF NOT EXISTS users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "username TEXT UNIQUE NOT NULL,"
        "password_hash TEXT NOT NULL,"
        "created_at DATETIME DEFAULT CURRENT_TIMESTAMP"
        ")")) {
        qDebug() << "Failed to create table:" << query.lastError().text();
        return false;
    }

    //---------------------ТАБЛИЦА-ДЛЯ-ЗАДАЧ---------------------
    if (!query.exec("CREATE TABLE IF NOT EXISTS tasks ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "title TEXT NOT NULL,"
        "description TEXT,"
        "category TEXT,"
        "deadline DATE,"
        "completed BOOLEAN DEFAULT 0,"
        "created_at DATETIME DEFAULT CURRENT_TIMESTAMP"
        ")")) {
        qDebug() << "Failed to create tasks table:" << query.lastError().text();
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

bool DatabaseManager::addTask(const QString &title, const QString &description, const QString &category,
                              const QDate &deadline) {
    QSqlQuery query;
    query.prepare("INSERT INTO tasks (title, description, category, deadline) VALUES (?, ?, ?, ?)");
    query.addBindValue(title);
    query.addBindValue(description);
    query.addBindValue(category);
    query.addBindValue(deadline);

    if (!query.exec()) {
        qDebug() << "Failed to add task:" << query.lastError().text();
        return false;
    }
    return true;
}

bool DatabaseManager::deleteTask(int taskId) {
    QSqlQuery query;
    query.prepare("DELETE FROM tasks WHERE id = ?");
    query.addBindValue(taskId);

    if (!query.exec()) {
        qDebug() << "Failed to delete task:" << query.lastError().text();
        return false;
    }
    return true;
}

bool DatabaseManager::updateTask(int taskId, const QString &title, const QString &description, const QString &category,
                                 const QDate &deadline) {
    QSqlQuery query;
    query.prepare("UPDATE tasks SET title = ?, description = ?, category = ?, deadline = ?, WHERE id = ?");
    query.addBindValue(title);
    query.addBindValue(description);
    query.addBindValue(category);
    query.addBindValue(deadline);
    query.addBindValue(taskId);

    if (!query.exec()) {
        qDebug() << "Failed to update task:" << query.lastError().text();
        return false;
    }
    return true;
}

bool DatabaseManager::updateTaskCompleteness(const int taskId, const bool completed) {
    QSqlQuery query;
    query.prepare("UPDATE tasks SET completed = ? WHERE id = ?");
    query.addBindValue(completed);
    query.addBindValue(taskId);
    if (!query.exec()) {
        qDebug() << "Failed to update task:" << query.lastError().text();
        return false;
    }
    return true;
}


QSqlQuery DatabaseManager::getAllTasks() {
    QSqlQuery query("SELECT * FROM tasks ORDER BY created_at DESC");
    return query;
}
