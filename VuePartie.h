#pragma once

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QLabel>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QMap>
#include "include/Hive.h"
#include "include/Piece.h"
#include "GameWindow.h"

class PieceItem : public QGraphicsEllipseItem {
public:
    PieceItem(const JeuHive::Piece* piece, QGraphicsItem* parent = nullptr);
    const JeuHive::Piece* getPiece() const;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

private:
    const JeuHive::Piece* piece;
};

class GameBoardWindow : public QWidget {
    Q_OBJECT

public:
    explicit GameBoardWindow(int partieId, QWidget* parent = nullptr);
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
};

class VuePartie : public QWidget {
    Q_OBJECT

public:
    explicit VuePartie(QWidget* parent = nullptr);

private slots:
    void creerNouvellePartie();
    void selectionnerPartieExistante();
    void afficherDetailsPartie(QListWidgetItem* item);
    void supprimerPartie();
    void terminerPartie();
    void quitterApplication();
    void lancerPartie();

private:
    QVBoxLayout* layout;
    QPushButton* btnNouvellePartie;
    QListWidget* listeParties;
    QLabel* labelTitre;
    QLabel* labelDetailsPartie;
    QLabel* AffichagePartie;
    QPushButton* deleteButton;
    QPushButton* lancerButton;
    QPushButton* terminerButton;
    QPushButton* quitterButton;
    QMap<int, GameBoardWindow*> openGameWindows; // Map to track open game windows

    void initialiserUI();
    void chargerPartiesExistantes();
    void clearPlateau();
};
