#include "VueNouvellePartie.h"

VueNouvellePartie::VueNouvellePartie(QWidget* parent) : QDialog(parent) {
    setupUI();
}

void VueNouvellePartie::setupUI() {
    QVBoxLayout* layout = new QVBoxLayout(this);

    QLabel* labelJoueur1 = new QLabel("Nom du Joueur 1:", this);
    layout->addWidget(labelJoueur1);

    nomJoueur1Edit = new QLineEdit(this);
    layout->addWidget(nomJoueur1Edit);

    QLabel* labelJoueur2 = new QLabel("Nom du Joueur 2:", this);
    layout->addWidget(labelJoueur2);

    nomJoueur2Edit = new QLineEdit(this);
    layout->addWidget(nomJoueur2Edit);

    okButton = new QPushButton("OK", this);
    cancelButton = new QPushButton("Annuler", this);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);


    layout->addLayout(buttonLayout);

    connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);

    setLayout(layout);
}

QString VueNouvellePartie::getNomJoueur1() const {
    return nomJoueur1Edit->text();
}

QString VueNouvellePartie::getNomJoueur2() const {
    return nomJoueur2Edit->text();
}


void VueNouvellePartie::supprimerPartie() {
    // Implémentation de la suppression de la partie
    // Vous pouvez ajouter ici le code nécessaire pour supprimer la partie
    // Par exemple, réinitialiser les champs de texte ou effectuer d'autres actions nécessaires
    nomJoueur1Edit->clear();
    nomJoueur2Edit->clear();
    // Vous pouvez également émettre un signal ou appeler une fonction pour notifier la suppression
}