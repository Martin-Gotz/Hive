#pragma once

#include <QWidget>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QMessageBox>
#include "include/Hive.h"
#include "VuePiece.h"
#include "VueCase.h"

class VuePartie : public QWidget {
    Q_OBJECT

public:
    explicit VuePartie(int partieId, QWidget* parent = nullptr);
    void creerPlateau(int partieId);
    void placerPiece(const JeuHive::Piece* piece, const QPointF& position);

private:
    QVBoxLayout* layout;
    QGraphicsView* graphicsView;
    QGraphicsScene* scene;
    QLabel* labelJoueur1;
    QLabel* labelJoueur2;
    QLabel* labelTour;
    QListWidget* listPiecesJoueur1;
    QListWidget* listPiecesJoueur2;

    void afficherInfosJoueurs(int partieId);
    void afficherPiecesJoueurs(int partieId);

    void closeEvent(QCloseEvent* event) override;

signals:
    void partieFermee(); // Signal émis à la fermeture
};