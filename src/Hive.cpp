#include "../include/Hive.h"
using namespace JeuHive;

// Constructeur
Hive::Hive() : partieEnCours(nullptr) {}

// Destructeur
Hive::~Hive() {
    // Lib�ration de toutes les parties stock�es
    for (Partie* partie : parties) {
        delete partie;
    }
    parties.clear();
}




// M�thodes pour g�rer les parties

// Ajouter une partie
void Hive::ajouterPartie(const Partie& partie) {
    parties.push_back(new Partie(partie)); // Copie de la partie dans un nouvel objet
    cout << "Partie " << partie.getId() << " ajoutee a la liste." << endl;
}

// Supprimer une partie
void Hive::supprimerPartie(int idPartie) {
    if (idPartie < 0 || idPartie >= static_cast<int>(parties.size())) {
        throw HiveException("Id de la partie invalide !");
    }

    // Lib�rer la m�moire de la partie � supprimer
    delete parties[idPartie];
    parties.erase(parties.begin() + idPartie);

    cout << "Partie a l'id " << idPartie + 1 << " supprimee." << endl;

    // Si la partie supprim�e �tait en cours, la r�initialiser
    if (partieEnCours && partieEnCours == parties[idPartie]) {
        partieEnCours = nullptr;
    }
}

// Obtenir une partie par index
Partie* Hive::getPartie(int idPartie) {
    if (idPartie < 0 || idPartie >= static_cast<int>(parties.size())) {
        throw HiveException("Id de la partie invalide !");
    }
    return parties[idPartie];
}

// Version const
const Partie* Hive::getPartie(int idPartie) const {
    if (idPartie < 0 || idPartie >= static_cast<int>(parties.size())) {
        throw HiveException("Id de la partie invalide !");
    }
    return parties[idPartie];
}

// Nombre de parties
int Hive::nombreParties() const {
    return static_cast<int>(parties.size());
}

// Gestion de la partie en cours

// D�marrer une partie
void Hive::demarrerPartie(int idPartie) {
    if (idPartie < 0 || idPartie >= static_cast<int>(parties.size())) {
        throw HiveException("Id de la partie invalide !");
    }

    if (partieEnCours != nullptr) {
        cout << "Une partie est d�j� en cours (ID : " << partieEnCours->getId() << ")." << endl;
        return;
    }

    partieEnCours = parties[idPartie];
    partieEnCours->demarrer();
}

// Terminer la partie en cours
void Hive::terminerPartie() {
    if (partieEnCours == nullptr) {
        cout << "Aucune partie n'est en cours." << endl;
        return;
    }

    partieEnCours->terminer();
    partieEnCours = nullptr;
}

// Afficher les informations des parties
void Hive::afficherParties() const {
    if (parties.empty()) {
        cout << "Aucune partie n'est enregistree." << endl << endl;
        return;
    }

    cout << "Liste des parties :" << endl;
    for (size_t i = 0; i < parties.size(); ++i) {
        cout << "Partie " << i + 1 << ":" << endl;
        parties[i]->afficher(cout);
        cout << endl;
    }
}