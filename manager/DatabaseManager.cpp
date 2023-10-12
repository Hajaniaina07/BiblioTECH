#include "DatabaseManager.h"
#include <QCoreApplication>
#include <QStandardPaths>
#include <QDir>
#include <QStandardPaths>
#include <QMessageBox>



bool DatabaseManager::openConnection() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    QString executableDir = QCoreApplication::applicationDirPath();
    QString dbPath = executableDir + QDir::separator() + "BiblioTECH.accdb";
    db.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};FIL={MS Access};DBQ=" + dbPath);
    if (db.open()) {
        return true;
    } else {
        QString documentsPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
        dbPath = documentsPath + QDir::separator() + "BiblioTECH"+ QDir::separator() + "database" + QDir::separator() + "BiblioTECH.accdb";
        db.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};FIL={MS Access};DBQ=" + dbPath);

        if (db.open()) {
            return true;
        } else {
            QMessageBox::critical(nullptr, "Erreur de connexion à la base", "Veuillez remplacez le fichier BiblioTECH.accdb dans le repertoir du programme\n"
                                                                            "par celui qui est fourni avec le fichier d'installation");
            return false;
        }
    }
}



void DatabaseManager::closeConnection() {
    QSqlDatabase::database().close();
}
