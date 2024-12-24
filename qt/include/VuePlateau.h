#pragma once
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QVboxLayout>
#include <QWidget>
#include <unordered_map>
#include "Plateau.h"
#include "Case.h"
#include "VueCase.h"

namespace JeuHive {
    class VuePlateau : public QWidget {
        Q_OBJECT

    private:
        QGraphicsView* graphicsView;
        QGraphicsScene* scene;
        QVBoxLayout* layoutPrincipal;
        const Plateau* plateau;
        const int hexSize = 25;

    public:
        explicit VuePlateau(const Plateau* plateau, QWidget* parent = nullptr) : QWidget(parent), plateau(plateau) {
            graphicsView = new QGraphicsView(this);
            scene = new QGraphicsScene(this);
            graphicsView->setScene(scene);

            graphicsView->setMinimumWidth(600);
            graphicsView->setMinimumHeight(600);

            layoutPrincipal = new QVBoxLayout(this);
            layoutPrincipal->addWidget(graphicsView);
            setLayout(layoutPrincipal);
        }


        void afficherPlateau() {
            scene->clear();
            int containerWidth = graphicsView->width();
            int containerHeight = graphicsView->height();

            // Déterminer le centre du conteneur
            int centerX = containerWidth / 2;
            int centerY = containerHeight / 2;

            // Créer un ensemble de coordonnées ajoutées pour éviter les duplications
            QSet<QPair<int, int>> casesAjoutees;
            // Conteneur pour les vues de cases déjà ajoutées
            QMap<QPair<int, int>, VueCase*> casesVue;

            // Ajouter une case vide en 0, 0 si le plateau est vide
            if (plateau->estVide()) {
                ajouterCaseDeCoordonnee(centerX, centerY, {0, 0}, casesAjoutees, casesVue, nullptr);
            }

            // Ajouter les cases réelles du plateau
            for (const auto& [coord, caseHive] : plateau->getCases()) {
                ajouterCaseDeCoordonnee(centerX, centerY, coord, casesAjoutees, casesVue, caseHive);

                // Ajouter les cases autour du plateau
                for (const auto& coordAutour : coord.getVoisins()) {
                    ajouterCaseDeCoordonnee(centerX, centerY, coordAutour, casesAjoutees, casesVue, nullptr);
                }
            }
            scene->update();
        }

        // Fonction pour ajouter une case à la scène avec une vue correspondante
        void ajouterCaseDeCoordonnee(int centerX, int centerY, const Coordonnee& coord, QSet<QPair<int, int>>& casesAjoutees, QMap<QPair<int, int>, VueCase*>& casesVue, const Case* caseHive) {
            double x, y;
            calculerPositionHexagonale(coord.get_q(), coord.get_r(), x, y);

            // Vérification si la case a déjà été ajoutée
            if (!casesAjoutees.contains(qMakePair(coord.get_q(), coord.get_r())) || casesAjoutees.contains(qMakePair(0, 0))) {
                // Calcul des positions de la vue de la case
                int pixelX = static_cast<int>(x + centerX);
                int pixelY = static_cast<int>(y + centerY);

                // Créer la VueCase
                QPair<int, int> coordPair = qMakePair(static_cast<int>(x), static_cast<int>(y));
                if (!casesVue.contains(coordPair)) {
                    VueCase* vueCase = new VueCase(coord);

                    // Ajouter la VueCase à la scène graphique (pas à un layout ou widget)
                    scene->addItem(vueCase);

                    // Définir la position de la VueCase dans la scène
                    vueCase->setPos(pixelX - hexSize, pixelY - hexSize);  // Ajuster selon votre taille d'hexagone

                    // Connecter le signal de clic de la VueCase
                    connect(vueCase, &VueCase::caseClicked, this, &VuePlateau::onCaseClicked);
                    casesVue.insert(coordPair, vueCase);
                }

                // Ajouter la pièce si nécessaire
                if (caseHive) {
                    casesVue[coordPair]->setPiece(*caseHive->getDessus());
                }

                // Ajouter la coordonnée au set pour éviter la duplication
                casesAjoutees.insert(coordPair);
            }
        }

        // Calculer la position hexagonale
        void calculerPositionHexagonale(int q, int r, double& x, double& y) const {
            // Calcul de la position hexagonale en pixels
            x = hexSize * (3.0 / 2.0 * q);
            y = -hexSize * (sqrt(3) * (r + q / 2.0));
        }





        void deplacerPiece(const Coordonnee& origine, const Coordonnee& destination) {
            auto casesMap = plateau->getCases();

            if (casesMap.find(origine) == casesMap.end() || casesMap[origine] == nullptr) {
                qDebug() << "Erreur : la case d'origine est invalide ou inexistante.";
                return;
            }

            Case* caseOrigine = casesMap[origine];
            if (caseOrigine->estVide()) {
                qDebug() << "Erreur : la case d'origine ne contient pas de pièce.";
                return;
            }

            if (casesMap.find(destination) == casesMap.end() || casesMap[destination] == nullptr) {
                qDebug() << "Erreur : la destination est invalide ou inexistante.";
                return;
            }


            caseOrigine->retirerPiece();


            Case* caseDestination = casesMap[destination];
            const Coordonnee& positionDest = caseDestination->getCoo();
            QPointF pointF(static_cast<qreal>(positionDest.get_q()), static_cast<qreal>(positionDest.get_r()));

            VueCase* vueCaseDestination = dynamic_cast<VueCase*>(scene->itemAt(pointF, QTransform()));
            if (vueCaseDestination) {
                vueCaseDestination->setPiece(*caseOrigine->getDessus());
            }

            afficherPlateau();
            scene->update();
        }



        void placerPiece(const Piece* piece, const Coordonnee& destination) {
            auto casesMap = plateau->getCases();


            if (casesMap.find(destination) == casesMap.end() || casesMap[destination] == nullptr) {
                qDebug() << "Erreur : la destination est invalide ou inexistante.";
                return;
            }

            Case* it = casesMap[destination];
            if (!it) {
                qDebug() << "Erreur : la case est un pointeur nul.";
                return;
            }

            const Coordonnee& position = it->getCoo();
            QPointF pointF(static_cast<qreal>(position.get_q()), static_cast<qreal>(position.get_r()));

            VueCase* vueCase = dynamic_cast<VueCase*>(scene->itemAt(pointF, QTransform()));
            if (vueCase) {
                vueCase->setPiece(*piece);
            }
            afficherPlateau();
            scene->update();
        }

        QGraphicsScene* getScene() const {
            return scene;
        }


    signals:
        void caseClickedSignal(VueCase* caseCliquee);

    private slots:
        void onCaseClicked(VueCase* vueCase) {
            emit caseClickedSignal(vueCase);
        }
    };
}