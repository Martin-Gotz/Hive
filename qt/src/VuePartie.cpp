#include "VuePartie.h"
#include <QApplication>

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
        connect(vuePlateau, &VuePlateau::caseClickedSignal, this, &VuePartie::gererCaseCliquee);

        // Layout horizontal principal
        QHBoxLayout* layoutPartie = new QHBoxLayout(this);
        layoutPartie->addWidget(vuePlateau);
        layoutPartie->addLayout(layoutBarreInfo);

        setLayout(layoutPartie);

        // Initialisation des informations de la partie
        actualiser();
    }


    void VuePartie::afficherInfosJoueurs() {
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

    void VuePartie::afficherPiecesJoueurs() {
        const auto* partie = Hive::getInstance().getPartieEnCours();
        if (!partie) {
            return;
        }

        listPiecesJoueur1->clear();
        listPiecesJoueur2->clear();

        // Utilisation d'une méthode privée pour factoriser la logique
        afficherPiecesJoueur(partie->getJoueur1(), listPiecesJoueur1);
        afficherPiecesJoueur(partie->getJoueur2(), listPiecesJoueur2);
    }

    void VuePartie::afficherPiecesJoueur(const Joueur& joueur, QListWidget* listWidget) {
        int idCounter = 1;

        vector<Piece*> pieces = joueur.getMain().getPieces();
        
        for (const auto* piece : pieces) {
            QString pieceInfo = QString("%1 - %2 : %3")
                .arg(idCounter++) // Ajoute un identifiant unique
                .arg(QString::fromStdString(piece->getNom()))
                .arg(QString::fromStdString(piece->getSymbole()));

            listWidget->addItem(pieceInfo);
        }
    }

    void VuePartie::actualiser() {
        afficherInfosJoueurs();
        afficherPiecesJoueurs();
        vuePlateau->afficherPlateau();
    }



    // Actions
    void VuePartie::placerPiece(int idPiece, const Coordonnee& coord) {
        Hive& hive = Hive::getInstance();
        Partie* partie = hive.getPartieEnCours();

        if (!partie) return;

        try {
            cout << "Pièce " << idPiece << endl;
            cout << "Coord : " << coord.get_q() << " " << coord.get_r() << endl;
            partie->placerPiece(idPiece, coord);
            update();

            vector<Piece*> pieces = partie->getJoueurActuel()->getMain().getPieces();
            int index = idPiece - 1;

            // Vérification de l'indice
            if (index < 0 || index >= pieces.size()) {
                qDebug() << "Erreur : Indice invalide : " << index << ", Taille : " << pieces.size();
                actualiser();
                return;
            }

            // Accès sécurisé à l'élément
            Piece* piece = pieces[index];

            // Place la pièce
            vuePlateau->placerPiece(piece, coord);

            cout << "\n" << partie->getPlateau();
        }
        catch (HiveException& e) {
            QMessageBox::warning(this, "Erreur", QString::fromStdString(e.getInfo()));
        }
        catch (...) {
            qDebug() << "Exception inconnue capturée.";
        }

        actualiser();
        update();
    }


    void VuePartie::deplacerPiece(const Coordonnee& origine, const Coordonnee& destination) {
        Hive& hive = Hive::getInstance();
        Partie* partie = hive.getPartieEnCours();

        if (!partie) return;

        partie->deplacerPiece(origine, destination);
        vuePlateau->deplacerPiece(origine, destination);
        cout << "Pièce déplacée\n";

        update();
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

    void VuePartie::gererCaseCliquee(VueCase* caseCliquee) {
        Partie* partie = Hive::getInstance().getPartieEnCours();

        if (partie->estPremierJoueurActuel()) {
            Joueur* joueur = &partie->getJoueur1();

            QListWidgetItem* currentItem = listPiecesJoueur1->currentItem();
            if (currentItem) {
                int idPiece = listPiecesJoueur1->currentRow() + 1;
                placerPiece(idPiece, caseCliquee->getCoord());
            }
        }
        else {
            Joueur* joueur = &partie->getJoueur2();

            QListWidgetItem* currentItem = listPiecesJoueur2->currentItem();
            if (currentItem) {
                int idPiece = listPiecesJoueur2->currentRow() + 1;
                placerPiece(idPiece, caseCliquee->getCoord());
            }
        }
        listPiecesJoueur1->setCurrentItem(nullptr);
        listPiecesJoueur2->setCurrentItem(nullptr);
    }
}