#include "VueNouvellePartie.h"

VueNouvellePartie::VueNouvellePartie(QWidget* parent) : QDialog(parent) {
    initialiser();
}

void VueNouvellePartie::initialiser() {
    QVBoxLayout* layout = new QVBoxLayout(this);

    QLabel* labelJoueur1 = new QLabel("Nom du Joueur 1:", this);
    layout->addWidget(labelJoueur1);

    nomJoueur1Edit = new QLineEdit(this);
    layout->addWidget(nomJoueur1Edit);

    QLabel* labelJoueur2 = new QLabel("Nom du Joueur 2:", this);
    layout->addWidget(labelJoueur2);
    
    // Checkbox pour l'IA
    iaCheckBox = new QCheckBox("Joueur 2 est une IA ?", this);

    nomJoueur2Edit = new QLineEdit(this);
    layout->addWidget(nomJoueur2Edit);

    layout->addWidget(iaCheckBox);

    // ComboBox pour le niveau de l'IA
    iaLevelComboBox = new QComboBox(this);
    iaLevelComboBox->addItem("Facile");
    iaLevelComboBox->addItem("Moyen");
    iaLevelComboBox->addItem("Difficile");
    iaLevelComboBox->setEnabled(false);
    layout->addWidget(iaLevelComboBox);

    QLabel* labelRetoursArriere = new QLabel("Nombre de retours en arriere possibles:", this);
    layout->addWidget(labelRetoursArriere);

    retoursArriereEdit = new QLineEdit(this);
    retoursArriereEdit->setValidator(new QIntValidator(0, 5, this)); // Limite de 0 � 100 retours en arri�re
    layout->addWidget(retoursArriereEdit);
    retoursArriereEdit->setText("0");


    boutonOk = new QPushButton("OK", this);
    boutonAnnuler = new QPushButton("Annuler", this);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(boutonOk);
    buttonLayout->addWidget(boutonAnnuler);


    layout->addLayout(buttonLayout);

    connect(iaCheckBox, &QCheckBox::toggled, this, [this](bool checked) {
        if (checked) {
            nomJoueur2Edit->setText("IA");
            nomJoueur2Edit->setEnabled(false);
            iaLevelComboBox->setEnabled(true);
        }
        else {
            nomJoueur2Edit->clear();
            nomJoueur2Edit->setEnabled(true);
            iaLevelComboBox->setEnabled(false);
        }
        });


    connect(boutonOk, &QPushButton::clicked, this, [this]() {
        QString nomJoueur1 = nomJoueur1Edit->text().trimmed();
        QString nomJoueur2 = nomJoueur2Edit->text().trimmed();
        QString retoursArriere = retoursArriereEdit->text().trimmed();

        // V�rifier que les deux noms sont remplis
        if (nomJoueur1.isEmpty() || nomJoueur2.isEmpty() || retoursArriere.isEmpty()) {
            QMessageBox::warning(this, "Erreur", "Les noms des deux joueurs ou le nombre de retours en arriere doivent etre renseignes.");
            return;
        }

        accept();
        });
    connect(boutonAnnuler, &QPushButton::clicked, this, &QDialog::reject);

    setLayout(layout);
}

QString VueNouvellePartie::getNomJoueur1() const {
    return nomJoueur1Edit->text();
}

QString VueNouvellePartie::getNomJoueur2() const {
    return nomJoueur2Edit->text();
}

QString VueNouvellePartie::getIaLevel() const {
    return iaLevelComboBox->currentText();
}

JeuHive::TypeJoueur VueNouvellePartie::getTypeJoueur1() {
    return JeuHive::HUMAIN;
}

JeuHive::TypeJoueur VueNouvellePartie::getTypeJoueur2() {
    return iaCheckBox->isChecked() ? JeuHive::IA : JeuHive::HUMAIN;
}
int VueNouvellePartie::getNombreRetoursArriere() const {
    return retoursArriereEdit->text().toInt();
}


void VueNouvellePartie::supprimerPartie() {
    // Impl�mentation de la suppression de la partie
    // Vous pouvez ajouter ici le code n�cessaire pour supprimer la partie
    // Par exemple, r�initialiser les champs de texte ou effectuer d'autres actions n�cessaires
    nomJoueur1Edit->clear();
    nomJoueur2Edit->clear();
    iaLevelComboBox->setCurrentIndex(0);
    retoursArriereEdit->clear();
    // Vous pouvez �galement �mettre un signal ou appeler une fonction pour notifier la suppression
}