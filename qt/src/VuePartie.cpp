#include "VuePartie.h"

VuePartie::VuePartie(int partieId, QWidget* parent) : QWidget(parent) {
    // Layout vertical pour les informations
    layoutBarreInfo = new QVBoxLayout();

    labelJoueur1 = new QLabel("Joueur 1", this);
    layoutBarreInfo->addWidget(labelJoueur1);

    listPiecesJoueur1 = new QListWidget(this);
    layoutBarreInfo->addWidget(listPiecesJoueur1);

    labelJoueur2 = new QLabel("Joueur 2", this);
    layoutBarreInfo->addWidget(labelJoueur2);

    listPiecesJoueur2 = new QListWidget(this);
    layoutBarreInfo->addWidget(listPiecesJoueur2);

    labelTour = new QLabel("Tour actuel", this);
    layoutBarreInfo->addWidget(labelTour);

    boutonQuitter = new QPushButton("Quitter", this);
    layoutBarreInfo->addWidget(boutonQuitter);
    connect(boutonQuitter, &QPushButton::clicked, this, &QWidget::close);

    graphicsView = new QGraphicsView(this);
    scene = new QGraphicsScene(this);
    graphicsView->setScene(scene);
    graphicsView->setMinimumWidth(600);
    graphicsView->setMinimumHeight(200);

    // Layout horizontal principal
    QHBoxLayout* layoutPartie = new QHBoxLayout(this);
    layoutPartie->addWidget(graphicsView);
    layoutPartie->addLayout(layoutBarreInfo);

    setLayout(layoutPartie);

    creerPlateau(partieId);
    afficherInfosJoueurs(partieId);
    afficherPiecesJoueurs(partieId);
}

void VuePartie::placerPiece(const JeuHive::Piece* piece, const QPointF& position) {
    auto* partie = JeuHive::Hive::getInstance().getPartieEnCours();
    if (!partie) {
        return;
    }

    if (partie->getJoueurActuel()->getMain().getPieces().size() == 0) {
        return;
    }

    bool isPlacement = !partie->getPlateau().estPlacee(*piece);

    JeuHive::Coordonnee coord(position.x(), position.y());
    JeuHive::Coup* coup = nullptr;

    if (isPlacement) {
        coup = new JeuHive::CoupPlacement(piece, coord, partie->getCompteurTour());
    }
    else {
        const JeuHive::Coordonnee& currentCoord = partie->getPlateau().getCaseDePiece(*piece)->getCoo();
        coup = new JeuHive::CoupDeplacement(piece, currentCoord, coord, partie->getCompteurTour());
    }

    partie->jouerCoup(coup);

    if (isPlacement) {
        VuePiece* pieceItem = new VuePiece(piece);
        pieceItem->setPos(position);
        scene->addItem(pieceItem);

        if (partie->getJoueurActuel() == &partie->getJoueur1()) {
            listPiecesJoueur1->clear();
            for (const auto* p : partie->getJoueur1().getMain().getPieces()) {
                if (p != piece) {
                    listPiecesJoueur1->addItem(new QListWidgetItem(QString::fromStdString(p->getNom())));
                }
            }
        }
        else {
            listPiecesJoueur2->clear();
            for (const auto* p : partie->getJoueur2().getMain().getPieces()) {
                if (p != piece) {
                    listPiecesJoueur2->addItem(new QListWidgetItem(QString::fromStdString(p->getNom())));
                }
            }
        }
    }
    else {
        for (auto* item : scene->items()) {
            VuePiece* pieceItem = dynamic_cast<VuePiece*>(item);
            if (pieceItem && pieceItem->getPiece() == piece) {
                pieceItem->setPos(position);
                break;
            }
        }
    }
}

void VuePartie::creerPlateau(int partieId) {
    scene->clear(); // Clear the current board

    const auto* partie = JeuHive::Hive::getInstance().getPartie(partieId);
    if (!partie) {
        return;
    }

    const int nombreCases = static_cast<int>(partie->getPlateau().getNombreCases());
    /*
    if (nombreCases == 0) {
        QMessageBox::warning(this, "Attention", "Le plateau ne contient aucune case.");
    }
    */

    const int rows = static_cast<int>(sqrt(nombreCases));
    const int cols = (nombreCases + rows - 1) / (rows + 1);

    const qreal hexSize = 30.0;
    const qreal hexWidth = 2 * hexSize * cos(M_PI / 6); // Width of each hexagon
    const qreal hexHeight = 1.5 * hexSize; // Height of each hexagon with vertical overlap

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            if (row * cols + col >= nombreCases) {
                break;
            }
            // Calculate position with an offset for every second row
            qreal x = col * hexWidth + (row % 2) * (hexWidth / 2);
            qreal y = row * hexHeight;

            // Create and add the hexagon to the scene
            VueCase* hex = new VueCase(x, y, hexSize);
            scene->addItem(hex);
        }
    }

    graphicsView->update(); // Force the view to update
}

void VuePartie::afficherInfosJoueurs(int partieId) {
    const auto* partie = JeuHive::Hive::getInstance().getPartieEnCours();
    if (!partie) {
        cout << "Aucune partie en cours";
        return;
    }

    cout << partie->getJoueur1().getCouleur();
    QString joueur1Info = QString("Joueur 1: %1\nCouleur: %2\nPièces: %3")
        .arg(QString::fromStdString(partie->getJoueur1().getNom()))
        .arg(partie->getJoueur1().getCouleur() == JeuHive::Couleur::BLANC ? "Blanc" : "Noir")
        .arg(partie->getJoueur1().getMain().getPieces().size());

    QString joueur2Info = QString("Joueur 2: %1\nCouleur: %2\nPièces: %3")
        .arg(QString::fromStdString(partie->getJoueur2().getNom()))
        .arg(partie->getJoueur2().getCouleur() == JeuHive::Couleur::BLANC ? "Blanc" : "Noir")
        .arg(partie->getJoueur2().getMain().getPieces().size());

    QString tourInfo = QString("Tour actuel: %1")
        .arg(QString::fromStdString(partie->getJoueurActuel()->getNom()));

    labelJoueur1->setText(joueur1Info);
    labelJoueur2->setText(joueur2Info);
    labelTour->setText(tourInfo);
}

void VuePartie::afficherPiecesJoueurs(int partieId) {
    const auto* partie = JeuHive::Hive::getInstance().getPartieEnCours();
    if (!partie) {
        return;
    }

    listPiecesJoueur1->clear();
    listPiecesJoueur2->clear();

    for (const auto* piece : partie->getJoueur1().getMain().getPieces()) {
        QString pieceInfo = QString("%1 (%2)").arg(QString::fromStdString(piece->getNom())).arg(QString::fromStdString(piece->getSymbole()));
        listPiecesJoueur1->addItem(pieceInfo);
    }

    for (const auto* piece : partie->getJoueur2().getMain().getPieces()) {
        QString pieceInfo = QString("%1 (%2)").arg(QString::fromStdString(piece->getNom())).arg(QString::fromStdString(piece->getSymbole()));
        listPiecesJoueur2->addItem(pieceInfo);
    }
}

void VuePartie::closeEvent(QCloseEvent* event) {
    emit partieFermee();
    QWidget::closeEvent(event);
}
