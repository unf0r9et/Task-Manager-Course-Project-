#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>

class DatabaseManager : public QObject {
    Q_OBJECT

public:
    explicit DatabaseManager(QObject *parent = nullptr);
    bool initDatabase();
    bool addUser(const QString &username, const QString &passwordHash);
    bool userExists(const QString &username);
    QString getPasswordHash(const QString &username);
    bool addTask(const QString &title, const QString &description, const QString &category, const QDate &deadline);
    bool deleteTask(int taskId);
    bool updateTask(int taskId, const QString &title, const QString &description, const QString &category, const QDate &deadline, bool completed);
    QSqlQuery getAllTasks();  // Возвращает все задачи

private:
    QSqlDatabase db;
};

#endif // DATABASEMANAGER_H