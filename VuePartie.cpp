#include "VuePartie.h"
#include "NouvellePartie.h"
#include <QMessageBox>

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
    connect(lancerButton, &QPushButton::clicked, this, &VuePartie::selectionnerPartieExistante); // Connexion du bouton Lancer
    layout->addWidget(lancerButton);


    terminerButton = new QPushButton("Terminer", this); // Initialisation du bouton Terminer
    connect(terminerButton, &QPushButton::clicked, this, &VuePartie::terminerPartie); // Connexion du bouton Terminer
    layout->addWidget(terminerButton);

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
        lancerPartie(partieId);
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
        JeuHive::Hive::getInstance().terminerPartie();
        chargerPartiesExistantes();
        labelDetailsPartie->clear();
        QMessageBox::information(this, "Partie terminee", "La partie en cours a ete terminee avec succes.");
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
        JeuHive::Hive::getInstance().supprimerPartie(partieId);
        chargerPartiesExistantes();
        labelDetailsPartie->clear();
    }
    else {
        QMessageBox::warning(this, "Erreur", "Aucune partie n'a été sélectionnée pour suppression.");
    }
}

void VuePartie::lancerPartie(int partieId) {
    const auto* partie = JeuHive::Hive::getInstance().getPartie(partieId);
    if (partie) {
        JeuHive::Hive::getInstance().demarrerPartie(partieId);
        // introduire le code pour lancer le plateau
    }
}