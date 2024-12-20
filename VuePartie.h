#pragma once

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QListWidget>
#include <QLabel>
#include "include/Hive.h"
#include "include/Piece.h"

class VuePartie : public QWidget {
    Q_OBJECT

public:
    explicit VuePartie(QWidget* parent = nullptr);

private slots:
    void creerNouvellePartie();
    void selectionnerPartieExistante();
    void afficherDetailsPartie(QListWidgetItem* item);
    void terminerPartie();
private:
    QVBoxLayout* layout;
    QPushButton* btnNouvellePartie;
    QListWidget* listeParties;
    QLabel* labelTitre;
    QLabel* labelDetailsPartie;
    QLabel* AffichagePartie;
    QPushButton* deleteButton;
    QPushButton* lancerButton; // Déclaration du bouton Lancer
    QPushButton* terminerButton;
    void initialiserUI();
    void chargerPartiesExistantes();
    void supprimerPartie();
    void lancerPartie(int PartieID);
};