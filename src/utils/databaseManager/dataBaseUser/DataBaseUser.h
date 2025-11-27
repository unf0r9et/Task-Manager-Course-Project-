// DatabaseUser.h
#ifndef DATABASEUSER_H
#define DATABASEUSER_H

class DatabaseManager;

class DataBaseUser {
protected:
    DatabaseManager *dbManager = nullptr;

public:
    virtual ~DataBaseUser() = default;
    void setDatabaseManager(DatabaseManager *dbManager) {
        this->dbManager = dbManager;
    }

    DatabaseManager* getDatabaseManager() const { return dbManager; }
};

#endif // DATABASEUSER_H