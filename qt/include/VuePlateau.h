#pragma once
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QVboxLayout>
#include <QWidget>
#include <unordered_map>
#include "Plateau.h"
#include "Case.h"
#include "VuePiece.h"
#include "VueCase.h"

namespace JeuHive {
    class VuePlateau : public QWidget {
        Q_OBJECT

    private:
        QGraphicsView* graphicsView;
        QGraphicsScene* scene;
        QVBoxLayout* layoutPrincipal;
        const Plateau* plateau;
        const int hexSize = 20;

    public:
        explicit VuePlateau(const Plateau* plateau, QWidget* parent = nullptr) : QWidget(parent), plateau(plateau) {
            graphicsView = new QGraphicsView(this);
            scene = new QGraphicsScene(this);
            graphicsView->setScene(scene);

            graphicsView->setMinimumWidth(600);
            graphicsView->setMinimumHeight(400);

            QVBoxLayout* layoutPrincipal = new QVBoxLayout(this);
            layoutPrincipal->addWidget(graphicsView);

            setLayout(layoutPrincipal);
        }


        void afficherPlateau() {
            scene->clear();
            int containerWidth = graphicsView->width();
            int containerHeight = graphicsView->height();

            // Déterminer le centre du conteneur
            int centerX = containerWidth / 2;
            int centerY = containerHeight / 1.5;

            // Taille d'une case hexagonale
            const int hexSize = 40;

            // Créer un ensemble de coordonnées ajoutées pour éviter les duplications
            QSet<QPair<int, int>> casesAjoutees;
            // Conteneur pour les vues de cases déjà ajoutées
            QMap<QPair<int, int>, VueCase*> casesVue;

            // Ajouter une case vide en 0, 0 si le plateau est vide
            if (plateau->estVide()) {
                ajouterCase(centerX, centerY, 0, 0, casesAjoutees, casesVue, nullptr);
            }

            // Ajouter les cases réelles du plateau
            for (const auto& [coord, caseHive] : plateau->getCases()) {
                ajouterCaseDeCoordonnee(centerX, centerY, coord, casesAjoutees, casesVue, caseHive);

                // Ajouter les cases autour du plateau
                for (const auto& coordAutour : coord.getVoisins()) {
                    ajouterCaseDeCoordonnee(centerX, centerY, coordAutour, casesAjoutees, casesVue, nullptr);
                }
            }
        }

        // Fonction pour ajouter une case à la scène avec une vue correspondante
        void ajouterCaseDeCoordonnee(int centerX, int centerY, const Coordonnee& coord, QSet<QPair<int, int>>& casesAjoutees, QMap<QPair<int, int>, VueCase*>& casesVue, Case* caseHive) {
            double x, y;
            calculerPositionHexagonale(coord.get_q(), coord.get_r(), x, y);

            // Vérification si la case a déjà été ajoutée
            if (!casesAjoutees.contains(qMakePair(coord.get_q(), coord.get_r()))) {
                ajouterCase(centerX, centerY, x, y, casesAjoutees, casesVue, caseHive);
            }
        }

        // Ajouter une case à la scène
        void ajouterCase(int centerX, int centerY, double x, double y, QSet<QPair<int, int>>& casesAjoutees, QMap<QPair<int, int>, VueCase*>& casesVue, Case* caseHive) {
            // Calcul des positions de la vue de la case
            int pixelX = static_cast<int>(x + centerX);
            int pixelY = static_cast<int>(y + centerY);

            // Créer la VueCase
            QPair<int, int> coord = qMakePair(static_cast<int>(x), static_cast<int>(y));
            if (!casesVue.contains(coord)) {
                VueCase* vueCase = new VueCase(this);
                vueCase->setGeometry(pixelX - hexSize, pixelY - hexSize, 2 * hexSize, 2 * hexSize);
                connect(vueCase, &VueCase::caseClicked, this, &VuePlateau::onCaseClicked);
                casesVue.insert(coord, vueCase);
            }

            // Ajouter la pièce si nécessaire
            if (caseHive && caseHive->getDessus()) {
                casesVue[coord]->setPiece(*caseHive->getDessus());
            }

            // Ajouter la coordonnée au set pour éviter la duplication
            casesAjoutees.insert(coord);
        }

        // Calculer la position hexagonale
        void calculerPositionHexagonale(int q, int r, double& x, double& y) {
            // Calcul de la position hexagonale en pixels
            x = hexSize * (3.0 / 2.0 * q);
            y = -hexSize * (std::sqrt(3) * (r + q / 2.0));
        }





        void deplacerPiece(const Coordonnee& origine, const Coordonnee& destination) {
            auto casesMap = plateau->getCases();

            Case* itOrigine = casesMap[origine];
            Case* itDestination = casesMap[destination];

            auto positionOrigine = itOrigine->getCoo();
            QPointF pointOrigine(static_cast<qreal>(positionOrigine.get_q()), static_cast<qreal>(positionOrigine.get_r()));

            auto positionDestination = itDestination->getCoo();
            QPointF pointDestination(static_cast<qreal>(positionDestination.get_q()), static_cast<qreal>(positionDestination.get_r()));

            VueCase* vueOrigine = dynamic_cast<VueCase*>(scene->itemAt(pointOrigine, QTransform()));
            VueCase* vueDestination = dynamic_cast<VueCase*>(scene->itemAt(pointDestination, QTransform()));

            if (vueOrigine && vueOrigine->piecePresente() && vueDestination) {
                const Piece& piece = vueOrigine->getPiece();
                vueOrigine->setNoPiece();
                vueDestination->setPiece(piece);
            }

            afficherPlateau();
            update();
        }



        void placerPiece(const Piece* piece, const Coordonnee& destination) {
            auto casesMap = plateau->getCases();
            Case* it = casesMap[destination];

            Coordonnee position = it->getCoo();
            QPointF pointF(static_cast<qreal>(position.get_q()), static_cast<qreal>(position.get_r()));

            VueCase* vueCase = dynamic_cast<VueCase*>(scene->itemAt(pointF, QTransform()));
            if (vueCase) {
                vueCase->setPiece(*piece);
            }

            afficherPlateau();
            update();
        }

        QGraphicsScene* getScene() const {
            return scene;
        }

        void resizeEvent(QResizeEvent* event) override {
            QWidget::resizeEvent(event);
        }

    private slots:
        void onCaseClicked(VueCase* caseClicked) {
            if (caseClicked->piecePresente()) {
                std::cout << "Pièce cliquée: " << caseClicked->getPiece().getNom() << std::endl;
            }
            else {
                std::cout << "Case vide cliquée." << std::endl;
            }
        }
    };
}