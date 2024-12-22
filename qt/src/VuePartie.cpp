#include "VuePartie.h"

using namespace std;

namespace JeuHive {
    VuePartie::VuePartie(int partieId, QWidget* parent) : QWidget(parent) {
        // Layout vertical pour les informations
        layoutBarreInfo = new QVBoxLayout();

        labelJoueur1 = new QLabel("Joueur 1", this);
        layoutBarreInfo->addWidget(labelJoueur1);

        listPiecesJoueur1 = new QListWidget(this);
        layoutBarreInfo->addWidget(listPiecesJoueur1);

        labelJoueur2 = new QLabel("Joueur 2", this);
        layoutBarreInfo->addWidget(labelJoueur2);

        listPiecesJoueur2 = new QListWidget(this);
        layoutBarreInfo->addWidget(listPiecesJoueur2);

        labelTour = new QLabel("Tour actuel", this);
        layoutBarreInfo->addWidget(labelTour);

        boutonQuitter = new QPushButton("Quitter", this);
        layoutBarreInfo->addWidget(boutonQuitter);
        connect(boutonQuitter, &QPushButton::clicked, this, &VuePartie::quitterPartie);

        boutonAbandonner = new QPushButton("Abandonner", this);
        layoutBarreInfo->addWidget(boutonAbandonner);
        connect(boutonAbandonner, &QPushButton::clicked, this, &VuePartie::abandonnerPartie);

        const Plateau* plateau = &Hive::getInstance().getPartieEnCours()->getPlateau();
        // VuePlateau pour afficher le plateau
        vuePlateau = new VuePlateau(plateau, this);

        // Layout horizontal principal
        QHBoxLayout* layoutPartie = new QHBoxLayout(this);
        layoutPartie->addWidget(vuePlateau);
        layoutPartie->addLayout(layoutBarreInfo);

        setLayout(layoutPartie);

        // Initialisation des informations de la partie
        creerPlateau(partieId);
        afficherInfosJoueurs(partieId);
        afficherPiecesJoueurs(partieId);

        placerPiece(1, { 0, 0 });
        placerPiece(1, { 0, 1 });
        placerPiece(2, { 1, -1 });
        placerPiece(2, { 1, 1 });
    }


    void VuePartie::creerPlateau(int partieId) {
        const auto* partie = Hive::getInstance().getPartieEnCours();
        if (!partie) {
            cout << "Aucune partie en cours";
            return;
        }
        vuePlateau->afficherPlateau();
    }


    void VuePartie::afficherInfosJoueurs(int partieId) {
        const auto* partie = Hive::getInstance().getPartieEnCours();
        if (!partie) {
            cout << "Aucune partie en cours";
            return;
        }

        cout << partie->getJoueur1().getCouleur();
        QString joueur1Info = QString("Joueur 1: %1\nCouleur: %2\nPièces: %3")
            .arg(QString::fromStdString(partie->getJoueur1().getNom()))
            .arg(partie->getJoueur1().getCouleur() == Couleur::BLANC ? "Blanc" : "Noir")
            .arg(partie->getJoueur1().getMain().getPieces().size());

        QString joueur2Info = QString("Joueur 2: %1\nCouleur: %2\nPièces: %3")
            .arg(QString::fromStdString(partie->getJoueur2().getNom()))
            .arg(partie->getJoueur2().getCouleur() == Couleur::BLANC ? "Blanc" : "Noir")
            .arg(partie->getJoueur2().getMain().getPieces().size());

        QString tourInfo = QString("Tour actuel: %1")
            .arg(QString::fromStdString(partie->getJoueurActuel()->getNom()));

        labelJoueur1->setText(joueur1Info);
        labelJoueur2->setText(joueur2Info);
        labelTour->setText(tourInfo);
    }

    void VuePartie::afficherPiecesJoueurs(int partieId) {
        const auto* partie = Hive::getInstance().getPartieEnCours();
        if (!partie) {
            return;
        }

        listPiecesJoueur1->clear();
        listPiecesJoueur2->clear();

        for (const auto* piece : partie->getJoueur1().getMain().getPieces()) {
            QString pieceInfo = QString("%1 (%2)").arg(QString::fromStdString(piece->getNom())).arg(QString::fromStdString(piece->getSymbole()));
            listPiecesJoueur1->addItem(pieceInfo);
        }

        for (const auto* piece : partie->getJoueur2().getMain().getPieces()) {
            QString pieceInfo = QString("%1 (%2)").arg(QString::fromStdString(piece->getNom())).arg(QString::fromStdString(piece->getSymbole()));
            listPiecesJoueur2->addItem(pieceInfo);
        }
    }




    // Actions
    void VuePartie::placerPiece(int idPiece, const Coordonnee& coord) {
        Hive& hive = Hive::getInstance();
        Partie* partie = hive.getPartieEnCours();

        if (!partie) return;

        partie->placerPiece(idPiece, coord);
        Piece* piece = partie->getJoueurActuel()->getMain().getPieces()[idPiece - 1];
        vuePlateau->placerPiece(piece, coord);
        cout << "Pièce " << idPiece << " placée\n";
        cout << "\n" << partie->getPlateau();
    }


    void VuePartie::deplacerPiece(const Coordonnee& origine, const Coordonnee& destination) {
        Hive& hive = Hive::getInstance();
        Partie* partie = hive.getPartieEnCours();

        if (!partie) return;

        partie->deplacerPiece(origine, destination);
        vuePlateau->deplacerPiece(origine, destination);
        cout << "Pièce déplacée\n";
    }




    void VuePartie::quitterPartie()
    {
        Hive& hive = Hive::getInstance();
        hive.mettrePartieEnPause();
        this->close();
    }

    void VuePartie::abandonnerPartie()
    {
        Hive& hive = Hive::getInstance();
        hive.terminerPartie();
        this->close();
    }

    void VuePartie::closeEvent(QCloseEvent* event) {
        Hive& hive = Hive::getInstance();
        if (hive.getPartieEnCours()) {
            hive.mettrePartieEnPause();
        }
        emit partieFermee();
        QWidget::closeEvent(event);
    }
}