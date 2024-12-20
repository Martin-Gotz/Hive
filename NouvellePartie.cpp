#include "NouvellePartie.h"

NouvellePartie::NouvellePartie(QWidget* parent) : QDialog(parent) {
    setupUI();
}

void NouvellePartie::setupUI() {
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

QString NouvellePartie::getNomJoueur1() const {
    return nomJoueur1Edit->text();
}

QString NouvellePartie::getNomJoueur2() const {
    return nomJoueur2Edit->text();
}
