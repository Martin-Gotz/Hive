#include "VuePartie.h"
#include "QVBoxLayout"

VuePartie::VuePartie(int partieId, QWidget* parent) : QWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout(this);

    graphicsView = new QGraphicsView(this);
    scene = new QGraphicsScene(this);
    graphicsView->setScene(scene);
    layout->addWidget(graphicsView);

    setLayout(layout);

    creerPlateau(partieId);
}

void VuePartie::creerPlateau(int partieId) {
    const int rows = 10;
    const int cols = 10;
    const qreal hexSize = 30.0;
    const qreal hexWidth = 2 * hexSize * cos(M_PI / 6);
    const qreal hexHeight = 1.5 * hexSize;

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            qreal x = col * hexWidth + (row % 2) * (hexWidth / 2);
            qreal y = row * hexHeight;
            VueCase* hex = new VueCase(x, y, hexSize);
            scene->addItem(hex);
        }
    }
}
