#include "VuePartie.h"
#include "NouvellePartie.h"
#include "Hexagon.h"
#include "GameWindow.h"
#include <QMessageBox>
#include <QApplication>
#include <cmath>
#include <QGraphicsSceneMouseEvent>

PieceItem::PieceItem(const JeuHive::Piece* piece, QGraphicsItem* parent)
    : QGraphicsEllipseItem(parent), piece(piece) {
    setRect(0, 0, 30, 30); // Set the size of the piece
    setBrush(piece->getCouleur() == JeuHive::Couleur::BLANC ? Qt::white : Qt::black);
}

const JeuHive::Piece* PieceItem::getPiece() const {
    return piece;
}

void GameBoardWindow::placerPiece(const JeuHive::Piece* piece, const QPointF& position) {
    auto* partie = JeuHive::Hive::getInstance().getPartieEnCours();
    if (!partie) {
        return;
    }

    // Check if the current player is allowed to place the piece
    if (partie->getJoueurActuel()->getMain().getPieces().size() == 0) {
        return;
    }

    // Determine if the piece is being placed or moved
    bool isPlacement = !partie->getPlateau().estPlacee(*piece);

    JeuHive::Coordonnee coord(position.x(), position.y());
    JeuHive::Coup* coup = nullptr;

    if (isPlacement) {
        // Create a placement coup
        coup = new JeuHive::CoupPlacement(piece, coord, partie->getCompteurTour());
    }
    else {
        // Create a movement coup
        const JeuHive::Coordonnee& currentCoord = partie->getPlateau().getCaseDePiece(*piece)->getCoo();
        coup = new JeuHive::CoupDeplacement(piece, currentCoord, coord, partie->getCompteurTour());
    }

    // Play the coup
    partie->jouerCoup(coup);

    // Update the piece's position in the scene
    if (isPlacement) {
        PieceItem* pieceItem = new PieceItem(piece);
        pieceItem->setPos(position);
        scene->addItem(pieceItem);

        // Remove the piece from the player's hand
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
            PieceItem* pieceItem = dynamic_cast<PieceItem*>(item);
            if (pieceItem && pieceItem->getPiece() == piece) {
                pieceItem->setPos(position);
                break;
            }
        }
    }
}



void PieceItem::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    if (scene()->views().isEmpty()) {
        return;
    }

    GameBoardWindow* gameBoardWindow = qobject_cast<GameBoardWindow*>(scene()->views().first()->parentWidget());
    if (gameBoardWindow) {
        gameBoardWindow->placerPiece(piece, event->scenePos());
    }
}



GameBoardWindow::GameBoardWindow(int partieId, QWidget* parent) : QWidget(parent) {
    layout = new QVBoxLayout(this);

    labelJoueur1 = new QLabel(this);
    layout->addWidget(labelJoueur1);

    labelJoueur2 = new QLabel(this);
    layout->addWidget(labelJoueur2);

    labelTour = new QLabel(this);
    layout->addWidget(labelTour);

    listPiecesJoueur1 = new QListWidget(this);
    layout->addWidget(listPiecesJoueur1);

    listPiecesJoueur2 = new QListWidget(this);
    layout->addWidget(listPiecesJoueur2);

    graphicsView = new QGraphicsView(this);
    scene = new QGraphicsScene(this);
    graphicsView->setScene(scene);
    layout->addWidget(graphicsView);

    setLayout(layout);

    creerPlateau(partieId);
}

void GameBoardWindow::creerPlateau(int partieId) {
    scene->clear(); // Clear the current board

    const auto* partie = JeuHive::Hive::getInstance().getPartie(partieId);
    if (!partie) {
        return;
    }

    const int nombreCases = static_cast<int>(partie->getPlateau().getNombreCases());
    if (nombreCases == 0) {
        QMessageBox::warning(this, "Attention", "Le plateau ne contient aucune case.");
    }

    const int rows = static_cast<int>(sqrt(nombreCases));
    const int cols = (nombreCases + rows - 1) / (rows +1);

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
            Hexagone* hex = new Hexagone(x, y, hexSize);
            scene->addItem(hex);
        }
    }

    graphicsView->update(); // Force the view to update
    afficherInfosJoueurs(partieId);
    afficherPiecesJoueurs(partieId);
}

void GameBoardWindow::afficherInfosJoueurs(int partieId) {
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
void GameBoardWindow::afficherPiecesJoueurs(int partieId) {
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


VuePartie::VuePartie(QWidget* parent) : QWidget(parent) {
    initialiserUI();
    chargerPartiesExistantes();
}

void VuePartie::initialiserUI() {
    layout = new QVBoxLayout(this);

    labelTitre = new QLabel("Menu du Jeu Hive", this);
    layout->addWidget(labelTitre);

    btnNouvellePartie = new QPushButton("Créer une nouvelle partie", this);
    connect(btnNouvellePartie, &QPushButton::clicked, this, &VuePartie::creerNouvellePartie);
    layout->addWidget(btnNouvellePartie);

    AffichagePartie = new QLabel(this); // Initialisation de AffichagePartie
    layout->addWidget(AffichagePartie); // Ajout de AffichagePartie à la disposition

    listeParties = new QListWidget(this);
    connect(listeParties, &QListWidget::itemClicked, this, &VuePartie::afficherDetailsPartie);
    layout->addWidget(listeParties);

    deleteButton = new QPushButton("Supprimer", this);
    connect(deleteButton, &QPushButton::clicked, this, &VuePartie::supprimerPartie);
    layout->addWidget(deleteButton);

    lancerButton = new QPushButton("Lancer", this); // Initialisation du bouton Lancer
    connect(lancerButton, &QPushButton::clicked, this, &VuePartie::lancerPartie); // Connexion du bouton Lancer
    layout->addWidget(lancerButton);

    terminerButton = new QPushButton("Terminer", this); // Initialisation du bouton Terminer
    connect(terminerButton, &QPushButton::clicked, this, &VuePartie::terminerPartie); // Connexion du bouton Terminer
    layout->addWidget(terminerButton);

    quitterButton = new QPushButton("Quitter", this); // Initialisation du bouton Quitter
    connect(quitterButton, &QPushButton::clicked, this, &VuePartie::quitterApplication); // Connexion du bouton Quitter
    layout->addWidget(quitterButton);

    labelDetailsPartie = new QLabel(this);
    layout->addWidget(labelDetailsPartie);

    setLayout(layout);
}

void VuePartie::chargerPartiesExistantes() {
    listeParties->clear();

    if (JeuHive::Hive::getInstance().nombreParties() > 0) {
        AffichagePartie->setText("Affichage des parties : ");
        for (const auto* parties : JeuHive::Hive::getInstance().getAllParties()) {
            QString itemText = QString("Partie numéro : %1").arg(parties->getId());
            listeParties->addItem(itemText);
        }
    }
    else {
        AffichagePartie->setText("Aucune partie en cours");
    }
}

void VuePartie::creerNouvellePartie() {
    NouvellePartie dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QString nomjoueur1 = dialog.getNomJoueur1();
        QString nomjoueur2 = dialog.getNomJoueur2();
        JeuHive::Hive::getInstance().ajouterPartie(nomjoueur1.toStdString(), JeuHive::TypeJoueur::HUMAIN, nomjoueur2.toStdString(), JeuHive::TypeJoueur::HUMAIN);
        chargerPartiesExistantes();
    }
}

void VuePartie::selectionnerPartieExistante() {
    QListWidgetItem* currentItem = listeParties->currentItem();
    if (currentItem) {
        QString itemText = currentItem->text();
        int partieId = itemText.split(" ").last().toInt();
        lancerPartie();
    }
    else {
        QMessageBox::warning(this, "Erreur", "Aucune partie n'a été sélectionnée pour lancement.");
    }
}

void VuePartie::afficherDetailsPartie(QListWidgetItem* item) {
    QString itemText = item->text();
    int partieId = itemText.split(" ").last().toInt();

    const auto* partie = JeuHive::Hive::getInstance().getPartie(partieId);
    if (partie) {
        QString details = QString("Partie numéro : %1\nJoueur 1 : %2\nJoueur 2 : %3")
            .arg(partie->getId())
            .arg(QString::fromStdString(partie->getJoueur1().getNom()))
            .arg(QString::fromStdString(partie->getJoueur2().getNom()));

        switch (partie->getEtatPartie()) {
        case JeuHive::EtatPartie::NON_COMMENCEE:
            details += "\nÉtat de la partie : Non commencee";
            break;
        case JeuHive::EtatPartie::EN_COURS:
            details += "\nÉtat de la partie : En cours";
            break;
        case JeuHive::EtatPartie::EN_PAUSE:
            details += "\nÉtat de la partie : En pause";
            break;
        case JeuHive::EtatPartie::TERMINEE:
            details += "\nÉtat de la partie : Terminee";
            break;
        }

        labelDetailsPartie->setText(details);
    }
    else {
        labelDetailsPartie->setText("Détails de la partie non disponibles.");
    }
}

void VuePartie::terminerPartie() {
    try {
        const auto* partieEnCours = JeuHive::Hive::getInstance().getPartieEnCours();
        if (partieEnCours) {
            int partieId = partieEnCours->getId();
            JeuHive::Hive::getInstance().terminerPartie();
            chargerPartiesExistantes();
            labelDetailsPartie->clear();
            QMessageBox::information(this, "Partie terminee", "La partie en cours a ete terminee avec succes.");

            // Close the game window if it is open
            if (openGameWindows.contains(partieId)) {
                openGameWindows[partieId]->close();
                openGameWindows.remove(partieId);
            }
        }
        else
        {
            QMessageBox::warning(this, "Erreur", "Impossible de terminer une partie qui n'a pas commencée.");
            return;
        }
    }
    catch (const JeuHive::HiveException& e) {
        QMessageBox::warning(this, "Erreur", QString::fromStdString(e.getInfo()));
    }
}

void VuePartie::supprimerPartie() {
    QListWidgetItem* currentItem = listeParties->currentItem();
    if (currentItem) {
        QString itemText = currentItem->text();
        int partieId = itemText.split(" ").last().toInt();

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Supprimer la partie", "Êtes-vous sûr de vouloir supprimer cette partie?",
            QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            JeuHive::Hive::getInstance().supprimerPartie(partieId);
            chargerPartiesExistantes();
            labelDetailsPartie->clear();

            // Close the game window if it is open
            if (openGameWindows.contains(partieId)) {
                openGameWindows[partieId]->close();
                openGameWindows.remove(partieId);
            }
        }
    }
    else {
        QMessageBox::warning(this, "Erreur", "Aucune partie n'a été sélectionnée pour suppression.");
    }
}

void VuePartie::lancerPartie() {
    const auto* partieEnCours = JeuHive::Hive::getInstance().getPartieEnCours();
    QListWidgetItem* currentItem = listeParties->currentItem();
    if (currentItem) {
        QString itemText = currentItem->text();
        int partieId = itemText.split(" ").last().toInt();
        const auto* partie = JeuHive::Hive::getInstance().getPartie(partieId);
        if (partie->getEtatPartie() == JeuHive::EtatPartie::TERMINEE) {
            QMessageBox::warning(this, "Erreur", "Cette partie est déjà terminée.");
            return;
        }
        if (partieEnCours) {
            if (partieId != partieEnCours->getId()) {
                QMessageBox::warning(this, "Erreur", "Vous ne pouvez lancer que la partie en cours.");
                return;
            }
        }
        JeuHive::Hive::getInstance().demarrerPartie(partieId);
        GameBoardWindow* gameBoardWindow = new GameBoardWindow(partieId);
        openGameWindows[partieId] = gameBoardWindow; // Track the open game window
        gameBoardWindow->show();
    }
    else {
        QMessageBox::warning(this, "Erreur", "Aucune partie n'a été sélectionnée pour lancement.");
    }
}

void VuePartie::quitterApplication() {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Quitter l'application", "Êtes-vous sûr de vouloir quitter l'application?",
        QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        QApplication::quit();
    }
}
