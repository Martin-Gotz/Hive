#include "../include/Hive.h"
using namespace JeuHive;

// Constructeur
Hive::Hive() : partieEnCours(nullptr) {}

// Destructeur
Hive::~Hive() {
    // Libération de toutes les parties stockées
    for (Partie* partie : parties) {
        delete partie;
    }
    parties.clear();
}




// Méthodes pour gérer les parties

// Ajouter une partie
void Hive::ajouterPartie(Joueur& joueur1, Joueur& joueur2) {
    // Créer une nouvelle partie avec un identifiant unique
    Partie* nouvellePartie = new Partie(prochainIdPartie++, joueur1, joueur2);

    parties.push_back(nouvellePartie);

    cout << "Nouvelle partie creee avec l'ID : " << nouvellePartie->getId() << endl;
}

// Supprimer une partie
void Hive::supprimerPartie(int idPartie) {
    // Chercher la partie par son identifiant
    auto it = std::find_if(parties.begin(), parties.end(),
        [idPartie](Partie* p) { return p && p->getId() == idPartie; });

    // Vérifier si la partie existe
    if (it == parties.end()) {
        throw HiveException("Aucune partie avec l'identifiant donné !");
    }

    // Libérer la mémoire et supprimer du vecteur
    if (*it == partieEnCours) {
        partieEnCours = nullptr; // Réinitialiser si c'était la partie en cours
    }

    delete* it;
    parties.erase(it);

    cout << "Partie avec l'identifiant " << idPartie << " supprimée." << endl;
}


// Obtenir une partie par index
Partie* Hive::getPartie(int idPartie) {
    if (idPartie < 0 || idPartie >= nombreParties()) {
        throw HiveException("Id de la partie invalide !");
    }
    return parties[idPartie];
}

// Version const
const Partie* Hive::getPartie(int idPartie) const {
    if (idPartie < 0 || idPartie >= nombreParties()) {
        throw HiveException("Id de la partie invalide !");
    }
    return parties[idPartie];
}


// Nombre de parties
int Hive::nombreParties() const {
    return static_cast<int>(parties.size());
}





// Gestion de la partie en cours

// Démarrer une partie
void Hive::demarrerPartie(int idPartie) {
    if (idPartie < 0 || idPartie >= nombreParties()) {
        throw HiveException("Id de la partie invalide !");
    }

    if (partieEnCours != nullptr) {
        cout << "Une partie est déjà en cours (ID : " << partieEnCours->getId() << ")." << endl;
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
        parties[i]->afficher(cout);
        cout << endl;
    }
}