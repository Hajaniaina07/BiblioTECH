QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    manager/DatabaseManager.cpp \
    main.cpp \
    model/abonnement.cpp \
    model/abonnementmembre.cpp \
    model/auteur.cpp \
    model/categorie.cpp \
    model/editeur.cpp \
    model/emprunt.cpp \
    model/langue.cpp \
    model/livre.cpp \
    model/membre.cpp \
    model/utilisateur.cpp \
    ui/abonnementwindow.cpp \
    ui/auteurwindow.cpp \
    ui/empruntmenu.cpp \
    ui/livredetail.cpp \
    ui/livrewindow.cpp \
    ui/mainwindow.cpp \
    ui/membreabonnementwindow.cpp \
    ui/newempruntwindow.cpp \
    ui/newmembrewindow.cpp \
    util/boolResult.cpp \
    util/util.cpp

HEADERS += \
    manager/DatabaseManager.h \
    model/abonnement.h \
    model/abonnementmembre.h \
    model/auteur.h \
    model/baseModel.h \
    model/categorie.h \
    model/editeur.h \
    model/emprunt.h \
    model/langue.h \
    model/livre.h \
    model/utilisateur.h \
    ui/abonnementwindow.h \
    ui/auteurwindow.h \
    ui/empruntmenu.h \
    ui/livredetail.h \
    ui/livrewindow.h \
    ui/mainwindow.h \
    model/membre.h \
    ui/membreabonnementwindow.h \
    ui/newempruntwindow.h \
    ui/newmembrewindow.h \
    util/boolResult.h \
    util/util.h

FORMS += \
    ui/abonnementwindow.ui \
    ui/auteurwindow.ui \
    ui/empruntmenu.ui \
    ui/livredetail.ui \
    ui/livrewindow.ui \
    ui/mainwindow.ui \
    ui/membreabonnementwindow.ui \
    ui/newempruntwindow.ui \
    ui/newmembrewindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    qrc/icones.qrc \
    qrc/img.qrc \
    qrc/logo.qrc
