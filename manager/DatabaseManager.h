#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>

class DatabaseManager {
public:
    static bool openConnection();
    static void closeConnection();
};

#endif // DATABASEMANAGER_H
