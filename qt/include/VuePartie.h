#pragma once

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "VueCase.h"

class VuePartie : public QWidget {
    Q_OBJECT

public:
    explicit VuePartie(int partieId, QWidget* parent = nullptr);

private:
    QGraphicsView* graphicsView;
    QGraphicsScene* scene;
    void creerPlateau(int partieId);
};
