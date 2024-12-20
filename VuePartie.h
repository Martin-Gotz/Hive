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
private:
    QVBoxLayout* layout;
    QPushButton* btnNouvellePartie;
    QListWidget* listeParties;
    QLabel* labelTitre;
    QLabel* labelDetailsPartie;

    void initialiserUI();
    void chargerPartiesExistantes();
};

