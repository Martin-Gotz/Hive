#pragma once

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QListWidget>
#include <QLabel>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMap>
#include "include/Hive.h"
#include "include/Piece.h"
#include "VuePartie.h"

class VueHive : public QWidget {
    Q_OBJECT

public:
    explicit VueHive(QWidget* parent = nullptr);

private slots:
    void creerNouvellePartie();
    void selectionnerPartieExistante();
    void afficherDetailsPartie(QListWidgetItem* item);
    void supprimerPartie();
    void quitterApplication();
    void lancerPartie();

private:
    QVBoxLayout* layout;
    QPushButton* btnNouvellePartie;
    QListWidget* listeParties;
    QLabel* labelTitre;
    QLabel* labelDetailsPartie;
    QLabel* affichagePartie;
    QLabel* labelJoueur1;
    QLabel* labelJoueur2;
    QLabel* labelTour;
    QPushButton* supprimerButton;
    QPushButton* lancerButton;
    QPushButton* quitterButton;
    QGraphicsView* graphicsView;
    QGraphicsScene* scene;
    QMap<int, VuePartie*> ouvrirVuePartie;
    void initialiserUI();
    void chargerPartiesExistantes();
    void creerPlateau(int partieId);
    void clearPlateau();
    void afficherInfosJoueurs(int partieId);
};


