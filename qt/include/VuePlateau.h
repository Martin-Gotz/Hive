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
            int centerY = containerHeight / 2;

            // Taille d'une case hexagonale (rayon)
            const int hexSize = 40;

            for (const auto& [coord, caseHive] : plateau->getCases()) {
                VueCase* vueCase = new VueCase(this);

                int q = coord.get_q();
                int r = coord.get_r();

                double x = hexSize * (3.0 / 2.0 * q);
                double y = -hexSize * (std::sqrt(3) * (r + q / 2.0));

                int pixelX = static_cast<int>(x + centerX);
                int pixelY = static_cast<int>(y + centerY);

                vueCase->setGeometry(pixelX - hexSize, pixelY - hexSize, 2 * hexSize, 2 * hexSize);

                if (caseHive->getDessus()) {
                    vueCase->setPiece(*caseHive->getDessus());
                }

                connect(vueCase, &VueCase::caseClicked, this, &VuePlateau::onCaseClicked);
            }
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
            int largeur = this->width();
            int hauteur = this->height();

            qDebug() << "Nouvelle taille - Largeur:" << largeur << "Hauteur:" << hauteur;

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