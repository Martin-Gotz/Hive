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
#include "GameWindow.h"

class VuePartie : public QWidget {
    Q_OBJECT

public:
    explicit VuePartie(QWidget* parent = nullptr);

private slots:
    void creerNouvellePartie();
    void selectionnerPartieExistante();
    void afficherDetailsPartie(QListWidgetItem* item);
    void supprimerPartie();
    void terminerPartie();
    void quitterApplication();
    void lancerPartie();

private:
    QVBoxLayout* layout;
    QPushButton* btnNouvellePartie;
    QListWidget* listeParties;
    QLabel* labelTitre;
    QLabel* labelDetailsPartie;
    QLabel* AffichagePartie;
    QLabel* labelJoueur1;
    QLabel* labelJoueur2;
    QLabel* labelTour;
    QPushButton* deleteButton;
    QPushButton* lancerButton;
    QPushButton* terminerButton;
    QPushButton* quitterButton;
    QGraphicsView* graphicsView;
    QGraphicsScene* scene;
    QMap<int, GameWindow*> openGameWindows; // Map to track open game windows
    void initialiserUI();
    void chargerPartiesExistantes();
    void creerPlateau(int partieId);
    void clearPlateau();
    void afficherInfosJoueurs(int partieId);
};


