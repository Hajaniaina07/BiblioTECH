#ifndef BASEMODEL_H
#define BASEMODEL_H

#include <QString>
class BaseModel {
public:
    int id;
    QString nom;


    BaseModel() : id(0), nom("") {}

    BaseModel(int _id, const QString& _nom) : id(_id), nom(_nom) {}
};

#endif // BASEMODEL_H
