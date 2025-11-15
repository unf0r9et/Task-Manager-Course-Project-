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

private:
    QSqlDatabase db;
};

#endif // DATABASEMANAGER_H