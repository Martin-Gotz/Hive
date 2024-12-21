#include "VueHive.h"

VueHive::VueHive(QWidget* parent) : QWidget(parent) {
    initialiserUI();
    chargerPartiesExistantes();
}

void VueHive::initialiserUI() {
    layout = new QVBoxLayout(this);

    labelTitre = new QLabel("Menu du Jeu Hive", this);
    layout->addWidget(labelTitre);

    // Actions sur la liste des parties
    btnNouvellePartie = new QPushButton("Creer une nouvelle partie", this);
    connect(btnNouvellePartie, &QPushButton::clicked, this, &VueHive::creerNouvellePartie);
    layout->addWidget(btnNouvellePartie);

    affichagePartie = new QLabel(this);
    layout->addWidget(affichagePartie);

    listeParties = new QListWidget(this);
    connect(listeParties, &QListWidget::itemClicked, this, &VueHive::afficherDetailsPartie);
    layout->addWidget(listeParties);




    // Actions sur une partie selectionnée
    boutonLancer = new QPushButton("Lancer", this);
    connect(boutonLancer, &QPushButton::clicked, this, &VueHive::lancerPartie);
    layout->addWidget(boutonLancer);

    boutonSupprimer = new QPushButton("Supprimer", this);
    connect(boutonSupprimer, &QPushButton::clicked, this, &VueHive::supprimerPartie);
    layout->addWidget(boutonSupprimer);




    // Autres affichages
    boutonQuitter = new QPushButton("Quitter", this);
    connect(boutonQuitter, &QPushButton::clicked, this, &VueHive::quitterApplication);
    layout->addWidget(boutonQuitter);

    labelDetailsPartie = new QLabel(this);
    layout->addWidget(labelDetailsPartie);

    setLayout(layout);
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
        JeuHive::TypeJoueur typeJoueur1 = dialog.getTypeJoueur1();
        JeuHive::TypeJoueur typeJoueur2 = dialog.getTypeJoueur2();
        JeuHive::Hive::getInstance().ajouterPartie(nomjoueur1.toStdString(), typeJoueur1, nomjoueur2.toStdString(), typeJoueur2);
        chargerPartiesExistantes();
    }
}

void VueHive::selectionnerPartieExistante() {
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

void VueHive::afficherDetailsPartie(QListWidgetItem* item) {
    QString itemText = item->text();
    int partieId = itemText.split(" ").last().toInt();


    const auto* partie = JeuHive::Hive::getInstance().getPartie(partieId);

    ResumePartie resumePartie = partie->resumer();

    if (partie) {
        QString details = QString("Partie numéro : %1\nJoueur 1 : %2\nJoueur 2 : %3")
            .arg(resumePartie.id)
            .arg(QString::fromStdString(resumePartie.joueur1.nom))
            .arg(QString::fromStdString(resumePartie.joueur2.nom));
        
        details += "\nEtat : ";

        details += resumePartie.etatPartie;

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
        connect(vuePartie, &VuePartie::partieFermee, this, [this, partieId]() {
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
