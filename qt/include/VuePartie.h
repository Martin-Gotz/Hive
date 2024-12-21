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
#include "VuePiece.h"
#include "VueCase.h"

class VuePartie : public QWidget {
    Q_OBJECT

public:
    explicit VuePartie(int partieId, QWidget* parent = nullptr);
    void creerPlateau(int partieId);
    void placerPiece(const JeuHive::Piece* piece, const QPointF& position);

private:
    QHBoxLayout* layoutPartie;
    QVBoxLayout* layoutBarreInfo;
    QGraphicsView* graphicsView;
    QGraphicsScene* scene;
    QLabel* labelJoueur1;
    QLabel* labelJoueur2;
    QLabel* labelTour;
    QListWidget* listPiecesJoueur1;
    QListWidget* listPiecesJoueur2;
    QPushButton* boutonQuitter;

    void afficherInfosJoueurs(int partieId);
    void afficherPiecesJoueurs(int partieId);

    void closeEvent(QCloseEvent* event) override;
    //void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
signals:
    void partieFermee(); // Signal émis à la fermeture
};