#include "VuePartie.h"
#include <QApplication>

using namespace std;

namespace JeuHive {
    VuePartie::VuePartie(int partieId, QWidget* parent) : QWidget(parent), partieTerminee(false) {
        // Layout vertical pour les informations
        layoutBarreInfo = new QVBoxLayout();


        labelTour = new QLabel("Tour actuel", this);
        layoutBarreInfo->addWidget(labelTour);

        labelJoueur1 = new QLabel("Joueur 1", this);
        layoutBarreInfo->addWidget(labelJoueur1);

        listPiecesJoueur1 = new QListWidget(this);
        layoutBarreInfo->addWidget(listPiecesJoueur1);

        labelJoueur2 = new QLabel("Joueur 2", this);
        layoutBarreInfo->addWidget(labelJoueur2);

        listPiecesJoueur2 = new QListWidget(this);
        layoutBarreInfo->addWidget(listPiecesJoueur2);

        labelRetoursRestants = new QLabel("Retours restants: 0", this); 
        layoutBarreInfo->addWidget(labelRetoursRestants);


        boutonRetourArriere = new QPushButton("Retour en arri�re", this);
        connect(boutonRetourArriere, &QPushButton::clicked, this, &VuePartie::retourArriere);
        layoutBarreInfo->addWidget(boutonRetourArriere);

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

    void VuePartie::retourArriere() {
        Partie* partie = Hive::getInstance().getPartieEnCours();
        if (partie) {
            if (partie->getPlateau().getNombrePieces() == 0) {
                QMessageBox::information(this, "Information", "Aucun coup � annuler.");
                return;
            }

            try {
                if (!partie->verifierAnnulation())
                {
                    QMessageBox::information(this, "Information", "Vous avez atteint le seuil de coups � annuler !");
                    return;
                }
            }
            catch (HiveException& e) {
                QMessageBox::warning(this, "Erreur", QString::fromStdString(e.getInfo()));
            }

            actualiser();
        }
    }
    void VuePartie::mettreAJourLabelRetoursRestants() {
        Partie* partie = Hive::getInstance().getPartieEnCours();
        if (partie) {
            int retoursRestants = partie->getRegles().getNombreRetours() - partie->getCompteurRegles();
            labelRetoursRestants->setText(QString("Retours restants: %1").arg(retoursRestants));
        }
    }

    void VuePartie::verifierGagnant()
    {
        Partie* partie = Hive::getInstance().getPartieEnCours();
        if (!partie) return;
        Joueur* gagnant = nullptr;
        if (!partie->verifierEtatPartie())
        {
            Couleur couleurGagnante = partie->getPlateau().Gagnant();
            if (couleurGagnante == Couleur::BLANC) {
                gagnant = (partie->getJoueur1().getCouleur() == Couleur::BLANC) ? &partie->getJoueur1() : &partie->getJoueur2();
            }
            else if (couleurGagnante == Couleur::NOIR) {
                gagnant = (partie->getJoueur1().getCouleur() == Couleur::NOIR) ? &partie->getJoueur1() : &partie->getJoueur2();
            }
        }
        if (gagnant) {
            QString message = QString("Le gagnant est %1").arg(QString::fromStdString(gagnant->getNom()));
            QMessageBox::information(this, "Partie terminee", message); 
            partieTerminee = true;
            partie->terminer();
        }
    }


    void VuePartie::afficherInfosJoueurs() {
        const auto* partie = Hive::getInstance().getPartieEnCours();
        if (!partie) {
            cout << "Aucune partie en cours";
            return;
        }

        cout << partie->getJoueur1().getCouleur();
        QString joueur1Info = QString("Joueur 1: %1\nCouleur: %2\nPi�ces: %3")
            .arg(QString::fromStdString(partie->getJoueur1().getNom()))
            .arg(partie->getJoueur1().getCouleur() == Couleur::BLANC ? "Blanc" : "Noir")
            .arg(partie->getJoueur1().getMain().getPieces().size());

        QString joueur2Info = QString("Joueur 2: %1\nCouleur: %2\nPi�ces: %3")
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

        // Utilisation d'une m�thode priv�e pour factoriser la logique
        afficherPiecesJoueur(partie->getJoueur1(), listPiecesJoueur1);
        afficherPiecesJoueur(partie->getJoueur2(), listPiecesJoueur2);
    }

    void VuePartie::afficherPiecesJoueur(const Joueur& joueur, QListWidget* listWidget) {
        vector<Piece*> pieces = joueur.getMain().getPieces();
        
        for (const auto* piece : pieces) {
            QString pieceInfo = QString("%1 : %2")
                .arg(QString::fromStdString(piece->getNom()))
                .arg(QString::fromStdString(piece->getSymbole()));

            listWidget->addItem(pieceInfo);
        }
    }

    void VuePartie::actualiser() {
        afficherInfosJoueurs();
        afficherPiecesJoueurs();
        mettreAJourLabelRetoursRestants();
        vuePlateau->afficherPlateau();
    }



    // Actions
    void VuePartie::placerPiece(int idPiece, const Coordonnee& coord) {

        if (partieTerminee) {
            QMessageBox::warning(this, "Erreur", "La partie est termin�e. Vous ne pouvez plus placer de pi�ces.");
            return;
        }

        Hive& hive = Hive::getInstance();
        Partie* partie = hive.getPartieEnCours();

        if (!partie) return;

        try {
            cout << "Pi�ce " << idPiece << endl;
            cout << "Coord : " << coord.get_q() << " " << coord.get_r() << endl;
            partie->placerPiece(idPiece, coord);

            vector<Piece*> pieces = partie->getJoueurActuel()->getMain().getPieces();
            int index = idPiece - 1;

            // V�rification de l'indice
            if (index < 0 || index >= pieces.size()) {
                qDebug() << "Erreur : Indice invalide : " << index << ", Taille : " << pieces.size();
                actualiser();
                return;
            }

            Piece* piece = pieces[index];

            vuePlateau->placerPiece(piece, coord);
            mettreAJourLabelRetoursRestants();
            cout << "\n" << partie->getPlateau();
        }
        catch (HiveException& e) {
            QMessageBox::warning(this, "Erreur", QString::fromStdString(e.getInfo()));
        }

        actualiser();
        update();
        verifierGagnant();
    }


    void VuePartie::deplacerPiece(const Coordonnee& origine, const Coordonnee& destination) {

        if (partieTerminee) {
            QMessageBox::warning(this, "Erreur", "La partie est termin�e. Vous ne pouvez plus d�placer de pi�ces.");
            return;
        }

        Hive& hive = Hive::getInstance();
        Partie* partie = hive.getPartieEnCours();
        if (!partie) return;

        try {
            partie->deplacerPiece(origine, destination);
            vuePlateau->deplacerPiece(origine, destination);
            cout << "\n" << partie->getPlateau();
            mettreAJourLabelRetoursRestants();
        }
        catch (HiveException& e) {
            QMessageBox::warning(this, "Erreur", QString::fromStdString(e.getInfo()));
        }

        actualiser();
        update();
        verifierGagnant();
    }




    void VuePartie::quitterPartie()
    {
        Hive& hive = Hive::getInstance();
        if (hive.getPartieEnCours() && hive.getPartieEnCours()->getEtatPartie() != TERMINEE)
        {
            hive.mettrePartieEnPause();
        }
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


    void VuePartie::gererPlacementPiece(VueCase* caseCliquee) {
        Partie* partie = Hive::getInstance().getPartieEnCours();

        if (partie->estPremierJoueurActuel()) {
            Joueur* joueur = &partie->getJoueur1();

            QListWidgetItem* currentItem = listPiecesJoueur1->currentItem();
            if (currentItem) {
                int idPiece = listPiecesJoueur1->currentRow() + 1;
                placerPiece(idPiece, caseCliquee->getCoord());
            }
            else {
                gererDeplacementPiece(caseCliquee);
            }
        }
        else {
            Joueur* joueur = &partie->getJoueur2();

            QListWidgetItem* currentItem = listPiecesJoueur2->currentItem();
            if (currentItem) {
                int idPiece = listPiecesJoueur2->currentRow() + 1;
                placerPiece(idPiece, caseCliquee->getCoord());
            }
            else {
                gererDeplacementPiece(caseCliquee);
            }
        }
        listPiecesJoueur1->setCurrentItem(nullptr);
        listPiecesJoueur2->setCurrentItem(nullptr);
    }


    void VuePartie::gererDeplacementPiece(VueCase* caseCliquee)
    {
        Partie* partie = Hive::getInstance().getPartieEnCours();

        if (caseCliquee->piecePresente()) {
            // Si une case est d�j� s�lectionn�e, on tente un d�placement
            if (caseSelectionnee) {
                // D�placement de la pi�ce de la case s�lectionn�e vers la case cliqu�e
                deplacerPiece(caseSelectionnee->getCoord(), caseCliquee->getCoord());
                caseSelectionnee = nullptr;
            }
            else {
                // Si aucune case n'est s�lectionn�e, on s�lectionne la case cliqu�e
                caseSelectionnee = caseCliquee;
                // Effet visuel
                //caseCliquee->mettreEnSelection(true);
            }
        }
        else {
            // Si la case ne contient pas de pi�ce et qu'une case est s�lectionn�e, on essaie de d�placer
            if (caseSelectionnee) {
                deplacerPiece(caseSelectionnee->getCoord(), caseCliquee->getCoord());
                caseSelectionnee = nullptr;
            }
        }
    }



    void VuePartie::gererCaseCliquee(VueCase* caseCliquee) 
    {
        gererPlacementPiece(caseCliquee);
    }

}