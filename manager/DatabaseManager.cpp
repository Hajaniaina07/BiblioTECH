#include "DatabaseManager.h"
#include <QCoreApplication>
#include <QStandardPaths>
#include <QDir>


bool DatabaseManager::openConnection() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    QString documentsPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QString dbPath = documentsPath + QDir::separator() + "BiblioTECH"+ QDir::separator() + "database" + QDir::separator() + "BiblioTECH.accdb";
    db.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};FIL={MS Access};DBQ=" + dbPath);

    if (db.open()) {
        return true;
    } else {
        qDebug() << "Échec de la connexion à la base de données:" << db.lastError().text();
        return false;
    }
}



void DatabaseManager::closeConnection() {
    QSqlDatabase::database().close();
}
