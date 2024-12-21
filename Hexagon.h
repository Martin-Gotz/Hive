#pragma once

#include <QGraphicsPolygonItem>
#include <QPolygonF>
#include <QBrush>

class Hexagone : public QGraphicsPolygonItem {
public:
    Hexagone(qreal x, qreal y, qreal size, QGraphicsItem* parent = nullptr);

private:
    QPolygonF createHexagone(qreal size);
};