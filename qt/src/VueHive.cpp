#include "VueHive.h"
#include "VueNouvellePartie.h"
#include "VueCase.h"
#include "VuePartie.h"
#include <QMessageBox>
#include <QApplication>

VueHive::VueHive(QWidget* parent) : QWidget(parent) {
    initialiserUI();
    chargerPartiesExistantes();
}

void VueHive::initialiserUI() {
    layout = new QVBoxLayout(this);

    labelTitre = new QLabel("Menu du Jeu Hive", this);
    layout->addWidget(labelTitre);

    // Actions sur la liste des parties
    btnNouvellePartie = new QPushButton("Créer une nouvelle partie", this);
    connect(btnNouvellePartie, &QPushButton::clicked, this, &VueHive::creerNouvellePartie);
    layout->addWidget(btnNouvellePartie);

    affichagePartie = new QLabel(this);
    layout->addWidget(affichagePartie);

    listeParties = new QListWidget(this);
    connect(listeParties, &QListWidget::itemClicked, this, &VueHive::afficherDetailsPartie);
    layout->addWidget(listeParties);




    // Actions sur une partie selectionnée
    lancerButton = new QPushButton("Lancer", this);
    connect(lancerButton, &QPushButton::clicked, this, &VueHive::lancerPartie);
    layout->addWidget(lancerButton);

    supprimerButton = new QPushButton("Supprimer", this);
    connect(supprimerButton, &QPushButton::clicked, this, &VueHive::supprimerPartie);
    layout->addWidget(supprimerButton);




    // Autres affichages
    quitterButton = new QPushButton("Quitter", this);
    connect(quitterButton, &QPushButton::clicked, this, &VueHive::quitterApplication);
    layout->addWidget(quitterButton);

    labelDetailsPartie = new QLabel(this);
    layout->addWidget(labelDetailsPartie);

    graphicsView = new QGraphicsView(this);
    scene = new QGraphicsScene(this);
    graphicsView->setScene(scene);
    layout->addWidget(graphicsView);

    setLayout(layout);
}

void VueHive::creerPlateau(int partieId) {
    clearPlateau();

    const auto* partie = JeuHive::Hive::getInstance().getPartie(partieId);
    if (!partie) {
        return;
    }

    const int nombreCases = partie->getPlateau().getNombreCases();
    const int rows = static_cast<int>(sqrt(nombreCases));
    const int cols = (nombreCases + rows - 1) / rows;

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

            // Optional: Highlight specific cells (e.g., in red)
            if ((row == 3 && col == 3) || (row == 4 && col == 3) || (row == 3 && col == 5)) {
                hex->setBrush(Qt::red);
            }
        }
    }
}

void VueHive::afficherInfosJoueurs(int partieId) {
    const auto* partie = JeuHive::Hive::getInstance().getPartie(partieId);
    if (!partie) {
        return;
    }

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



void VueHive::clearPlateau() {
    scene->clear();
}

void VueHive::chargerPartiesExistantes() {
    listeParties->clear();

    if (JeuHive::Hive::getInstance().nombreParties() > 0) {
        affichagePartie->setText("Affichage des parties : ");
        for (const auto* parties : JeuHive::Hive::getInstance().getAllParties()) {
            QString itemText = QString("Partie numéro : %1").arg(parties->getId());
            listeParties->addItem(itemText);
        }
    }
    else {
        affichagePartie->setText("Aucune partie en cours");
    }
}

void VueHive::creerNouvellePartie() {
    VueNouvellePartie dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QString nomjoueur1 = dialog.getNomJoueur1();
        QString nomjoueur2 = dialog.getNomJoueur2();
        JeuHive::Hive::getInstance().ajouterPartie(nomjoueur1.toStdString(), JeuHive::TypeJoueur::HUMAIN, nomjoueur2.toStdString(), JeuHive::TypeJoueur::HUMAIN);
        chargerPartiesExistantes();
    }
}

void VueHive::selectionnerPartieExistante() {
    QListWidgetItem* currentItem = listeParties->currentItem();
    if (currentItem) {
        QString itemText = currentItem->text();
        int partieId = itemText.split(" ").last().toInt();
        lancerPartie();
        creerPlateau(partieId);
    }
    else {
        QMessageBox::warning(this, "Erreur", "Aucune partie n'a été sélectionnée pour lancement.");
    }
}

void VueHive::afficherDetailsPartie(QListWidgetItem* item) {
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

void VueHive::supprimerPartie() {
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
            if (ouvrirVuePartie.contains(partieId)) {
                ouvrirVuePartie[partieId]->close();
                ouvrirVuePartie.remove(partieId);
            }
        }
    }
    else {
        QMessageBox::warning(this, "Erreur", "Aucune partie n'a été sélectionnée pour suppression.");
    }
}



void VueHive::lancerPartie() {
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
        VuePartie* vuePartie = new VuePartie(partieId);
        ouvrirVuePartie[partieId] = vuePartie;

        this->setEnabled(false); // Désactiver la fenètre lorsqu'une partie se lance

        // Connecter le signal de fermeture de la fenêtre de partie pour réactiver la fenêtre principale
        connect(vuePartie, &QWidget::destroyed, this, [this, partieId]() {
            this->setEnabled(true);
            ouvrirVuePartie.remove(partieId);
            });

        vuePartie->show();
    }
    else {
        QMessageBox::warning(this, "Erreur", "Aucune partie n'a été sélectionnée pour lancement.");
    }
}

void VueHive::quitterApplication() {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Quitter l'application", "Êtes-vous sûr de vouloir quitter l'application?",
        QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        QApplication::quit();
    }
}



