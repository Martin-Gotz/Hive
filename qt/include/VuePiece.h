#pragma once

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QMessageBox>
#include "include/Piece.h"

class VuePiece : public QGraphicsEllipseItem {
public:
    VuePiece(const JeuHive::Piece* piece, QGraphicsItem* parent = nullptr);
    JeuHive::Piece* getPiece() const;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

private:
    const JeuHive::Piece* piece;
};