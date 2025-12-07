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
        "user_id INTEGER NOT NULL,"
        "title TEXT NOT NULL,"
        "description TEXT,"
        "category TEXT,"
        "deadline DATE,"
        "completed BOOLEAN DEFAULT 0,"
        "created_at DATETIME DEFAULT CURRENT_TIMESTAMP,"
        "FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE CASCADE"
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

bool DatabaseManager::addTask(int userId, const QString &title, const QString &description,
                              const QString &category, const QDate &deadline) {
    QSqlQuery query;
    query.prepare("INSERT INTO tasks (user_id, title, description, category, deadline) VALUES (?, ?, ?, ?, ?)");
    query.addBindValue(userId);
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
    query.prepare("UPDATE tasks SET title = ?, description = ?, category = ?, deadline = ? WHERE id = ?");
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


QSqlQuery DatabaseManager::getTasksByUser(int userId) {
    QSqlQuery query;
    query.prepare("SELECT * FROM tasks WHERE user_id = ? ORDER BY created_at DESC");
    query.addBindValue(userId);
    query.exec();
    return query;
}

QSqlQuery DatabaseManager::getTaskById(int taskId) {
    QSqlQuery query;
    query.prepare("SELECT * FROM tasks WHERE id = ?");
    query.addBindValue(taskId);
    query.exec();
    return query;
}

int DatabaseManager::getUserId(const QString &username) {
    QSqlQuery query;
    query.prepare("SELECT id FROM users WHERE username = ?");
    query.addBindValue(username);
    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    }
    return -1;
}

int DatabaseManager::getTotalTaskCount(int userId) {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM tasks WHERE user_id = ?");
    query.addBindValue(userId);
    query.exec();
    if (query.next()) return query.value(0).toInt();
    return 0;
}

int DatabaseManager::getTaskCountByCategory(int userId, const QString &category, bool completed) {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM tasks WHERE user_id = ? AND category = ? AND completed = ?");
    query.addBindValue(userId);
    query.addBindValue(category);
    query.addBindValue(completed);
    query.exec();
    if (query.next()) return query.value(0).toInt();
    return 0;
}