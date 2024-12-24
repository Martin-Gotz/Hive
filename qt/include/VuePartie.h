#pragma once

#include <QWidget>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QMessageBox>
#include "include/Hive.h"
#include "Coordonnee.h"
#include "VuePlateau.h"
#include "ResumeClasse.h"

namespace JeuHive {
    class VuePartie : public QWidget {
        Q_OBJECT

    public:
        explicit VuePartie(int partieId, QWidget* parent = nullptr);

    private:
        QHBoxLayout* layoutPartie;
        QVBoxLayout* layoutBarreInfo;
        QGraphicsView* graphicsView;
        QGraphicsScene* scene;
        QLabel* labelJoueur1;
        QLabel* labelJoueur2;
        QLabel* labelTour;
        QLabel* labelRetoursRestants;
        QListWidget* listPiecesJoueur1;
        QListWidget* listPiecesJoueur2;
        QPushButton* boutonRetourArriere;
        QPushButton* boutonAbandonner;
        QPushButton* boutonQuitter;

        VuePlateau* vuePlateau;

        VueCase* caseSelectionnee = nullptr;

        void afficherInfosJoueurs();
        void afficherPiecesJoueurs();
        void afficherPiecesJoueur(const Joueur& joueur, QListWidget* listWidget);
        void actualiser();

        void placerPiece(int idPiece, const Coordonnee& coord);
        void deplacerPiece(const Coordonnee& origine, const Coordonnee& destination);
        void retourArriere();
        void mettreAJourLabelRetoursRestants();

        bool partieTerminee;
        void verifierGagnant();
        void quitterPartie();
        void abandonnerPartie();
        void closeEvent(QCloseEvent* event) override;

        void gererPlacementPiece(VueCase* caseCliquee);
        void gererDeplacementPiece(VueCase* caseCliquee);

    signals:
        void partieFermee(); // Signal émis à la fermeture

    public slots:
        void gererCaseCliquee(VueCase* caseCliquee);
    };
}