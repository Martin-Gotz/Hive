#include "../include/Hive.h"
using namespace JeuHive;

// Destructeur
Hive::~Hive() {
    // Lib�ration de toutes les parties stock�es
    for (Partie* partie : parties) {
        delete partie;
    }
    parties.clear();
}




// M�thodes pour g�rer les parties

void Hive::ajouterPartie(Joueur& joueur1, Joueur& joueur2) {
    // Cr�er une nouvelle partie en utilisant la factory
    int idPartie = parties.size();
    parties.push_back(PartieFactory::creerPartie(idPartie, joueur1, joueur2));

    cout << "Nouvelle partie creee avec l'ID : " << idPartie << endl;
}

// Supprimer une partie
void Hive::supprimerPartie(int idPartie) {
    // Chercher la partie par son identifiant
    auto it = std::find_if(parties.begin(), parties.end(),
        [idPartie](Partie* p) { return p && p->getId() == idPartie; });

    // V�rifier si la partie existe
    if (it == parties.end()) {
        throw HiveException("Aucune partie trouvee !");
    }

    // Lib�rer la m�moire et supprimer du vecteur
    if (*it == partieEnCours) {
        partieEnCours = nullptr; // R�initialiser si c'�tait la partie en cours
    }

    delete* it;
    parties.erase(it);

    cout << "Partie avec l'identifiant " << idPartie << " supprim�e." << endl;
}


// Obtenir une partie par index
Partie* Hive::getPartie(int idPartie) {
    if (idPartie < 0 || idPartie >= nombreParties()) {
        throw HiveException("Aucune partie trouvee !");
    }
    return parties[idPartie];
}

// Version const
const Partie* Hive::getPartie(int idPartie) const {
    if (idPartie < 0 || idPartie >= nombreParties()) {
        throw HiveException("Aucune partie trouvee !");
    }
    return parties[idPartie];
}


// Nombre de parties
int Hive::nombreParties() const {
    return parties.size();
}





// Gestion de la partie en cours

// D�marrer une partie
void Hive::demarrerPartie(int idPartie) {
    if (idPartie < 0 || idPartie >= nombreParties()) {
        throw HiveException("Aucune partie trouvee !");
    }

    if (partieEnCours != nullptr) {
        cout << "Une partie est d�j� en cours (ID : " << partieEnCours->getId() << ")." << endl;
        return;
    }

    partieEnCours = parties[idPartie];
    partieEnCours->demarrer();
}

//Surcharge (si beoin)
void Hive::demarrerPartie(Partie* partie) {
    if (partie == nullptr) {
        throw HiveException("La partie fournie est invalide !");
    }

    if (partieEnCours != nullptr) {
        cout << "Une partie est d�j� en cours (ID : " << partieEnCours->getId() << ")." << endl;
        return;
    }

    partieEnCours = partie;
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