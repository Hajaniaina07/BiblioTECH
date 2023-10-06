#include "DatabaseManager.h"

bool DatabaseManager::openConnection() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};FIL={MS Access};DBQ=D:\\BiblioTECH\\biblio.accdb");
    return db.open();
}

void DatabaseManager::closeConnection() {
    QSqlDatabase::database().close();
}
