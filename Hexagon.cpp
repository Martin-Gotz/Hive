#include "Hexagon.h"

Hexagone::Hexagone(qreal x, qreal y, qreal size, QGraphicsItem* parent)
    : QGraphicsPolygonItem(parent) {
    setPolygon(createHexagone(size));
    setBrush(QBrush(Qt::lightGray));
    setPos(x, y);
}

QPolygonF Hexagone::createHexagone(qreal size) {
    QPolygonF hexagon;
    for (int i = 0; i < 6; ++i) {
        qreal angle = 2 * M_PI / 6 * i;
        qreal dx = size * cos(angle);
        qreal dy = size * sin(angle);
        hexagon << QPointF(dx, dy);
    }
    return hexagon;
}