#include "VuePartie.h"
#include "NouvellePartie.h"

VuePartie::VuePartie(QWidget* parent) : QWidget(parent) {
    initialiserUI();
    chargerPartiesExistantes();
}

void VuePartie::initialiserUI() {
    layout = new QVBoxLayout(this);

    labelTitre = new QLabel("Menu du Jeu Hive", this);
    layout->addWidget(labelTitre);

    btnNouvellePartie = new QPushButton("Cr�er une nouvelle partie", this);
    connect(btnNouvellePartie, &QPushButton::clicked, this, &VuePartie::creerNouvellePartie);
    layout->addWidget(btnNouvellePartie);

    listeParties = new QListWidget(this);
    connect(listeParties, &QListWidget::itemClicked, this, &VuePartie::afficherDetailsPartie);
    layout->addWidget(listeParties);

    labelDetailsPartie = new QLabel(this);
    layout->addWidget(labelDetailsPartie);

    setLayout(layout);
}

void VuePartie::chargerPartiesExistantes() {
    // Vider la liste avant de la remplir � nouveau
    listeParties->clear();

    if (JeuHive::Hive::getInstance().nombreParties() > 0) {
        listeParties->addItem("Listes des autres parties : ");
        for (const auto* parties : JeuHive::Hive::getInstance().getAllParties()) {
            QString itemText = QString("Partie num�ro : %1").arg(parties->getId());
            listeParties->addItem(itemText);
        }
    }
    else {
        listeParties->addItem("Aucune partie cr��e");
    }
}

void VuePartie::creerNouvellePartie() {
   // il faut impl�menter la logique derri�re
    NouvellePartie dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QString nomjoueur1 = dialog.getNomJoueur1();
        QString nomjoueur2 = dialog.getNomJoueur2();
        JeuHive::Hive::getInstance().ajouterPartie(nomjoueur1.toStdString(), JeuHive::TypeJoueur::HUMAIN, nomjoueur2.toStdString(), JeuHive::TypeJoueur::HUMAIN);
        chargerPartiesExistantes();
    }
}

void VuePartie::selectionnerPartieExistante() {

}

void VuePartie::afficherDetailsPartie(QListWidgetItem* item) {
    // R�cup�rer l'ID de la partie � partir du texte de l'�l�ment
    QString itemText = item->text();
    int partieId = itemText.split(" ").last().toInt();

    const auto* partie = JeuHive::Hive::getInstance().getPartie(partieId);
    if (partie) {
        QString details = QString("Partie num�ro : %1\nJoueur 1 : %2\nJoueur 2 : %3")
            .arg(partie->getId())
            .arg(QString::fromStdString(partie->getJoueur1().getNom()))
            .arg(QString::fromStdString(partie->getJoueur2().getNom()))
            .arg(QString::fromStdString(partie->tostringresumer()));
        labelDetailsPartie->setText(details);
    }
    else {
        labelDetailsPartie->setText("D�tails de la partie non disponibles.");
    }
}