#include "VuePiece.h"
#include "VuePartie.h"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

VuePiece::VuePiece(const JeuHive::Piece* piece, QGraphicsItem* parent)
    : QGraphicsEllipseItem(parent), piece(piece) {
    setRect(0, 0, 30, 30); // Set the size of the piece
    setBrush(piece->getCouleur() == JeuHive::Couleur::BLANC ? Qt::white : Qt::black);
}

JeuHive::Piece* VuePiece::getPiece() const {
    return const_cast<JeuHive::Piece*>(piece);
}

void VuePiece::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    if (scene()->views().isEmpty()) {
        return;
    }

    VuePartie* vuePartie = qobject_cast<VuePartie*>(scene()->views().first()->parentWidget());
    if (vuePartie) {
        vuePartie->placerPiece(piece, event->scenePos());
    }
}

