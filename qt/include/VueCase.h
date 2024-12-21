#pragma once

#include <QGraphicsPolygonItem>
#include <QPolygonF>
#include <QBrush>

class VueCase : public QGraphicsPolygonItem {
public:
    VueCase(qreal x, qreal y, qreal size, QGraphicsItem* parent = nullptr);

private:
    QPolygonF createHexagone(qreal size);
};