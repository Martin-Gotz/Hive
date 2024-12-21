#pragma once

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "Hexagon.h"

class GameWindow : public QWidget {
    Q_OBJECT

public:
    explicit GameWindow(int partieId, QWidget* parent = nullptr);

private:
    QGraphicsView* graphicsView;
    QGraphicsScene* scene;
    void creerPlateau(int partieId);
};
