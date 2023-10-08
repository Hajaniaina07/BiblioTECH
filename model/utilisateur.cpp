#include "utilisateur.h"
#include "manager/DatabaseManager.h"

Utilisateur::Utilisateur()
{

}

Utilisateur::Utilisateur(const QString& login,const QString& mdp)
    : login(login),mdp(mdp)
{
}

bool Utilisateur::isConnected() {
    bool connected = false;
    if(DatabaseManager::openConnection()){
        QSqlQuery query;
        query.prepare("SELECT * FROM Utilisateur WHERE login = ? AND mdp = ?");
        query.addBindValue(login);
        query.addBindValue(mdp);
        if (query.exec()) {
            connected = query.next();
        } else {
            qDebug() << "Erreur lors de la requête de connexion : " << qPrintable(query.lastError().text());
        }
        DatabaseManager::closeConnection();
    }
    return connected;
}
