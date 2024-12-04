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
    parties.push_back(PartieFactory::creerPartie(prochainIdPartie, joueur1, joueur2));

    EvenementHive evt("Nouvelle partie creee avec l'ID " + to_string(prochainIdPartie) +"\n");
    prochainIdPartie++;
    notifierObservers(evt);
}

// Supprimer une partie
void Hive::supprimerPartie(int idPartie) {
    // Chercher la partie par son identifiant
    auto it = find_if(parties.begin(), parties.end(),
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

    EvenementHive evt("Partie avec l'ID " + to_string(idPartie) + " supprimee\n");
    notifierObservers(evt);
}


// Obtenir une partie par index
Partie* Hive::getPartie(int idPartie) {
    for (Partie* partie : parties) {
        if (partie != nullptr && partie->getId() == idPartie) {
            return partie;
        }
    }
    return nullptr;
}

// Version const
const Partie* Hive::getPartie(int idPartie) const {
    for (const Partie* partie : parties) {
        if (partie != nullptr && partie->getId() == idPartie) {
            return partie;
        }
    }
    return nullptr;
}



// Nombre de parties
int Hive::nombreParties() const {
    return static_cast<int>(parties.size());
}





// Gestion de la partie en cours

// D�marrer une partie
void Hive::demarrerPartie(int idPartie) {
    if (idPartie < 0 || idPartie >= nombreParties() + 1) {
        throw HiveException("Aucune partie trouvee !");
    }

    if (partieEnCours != nullptr) {
        EvenementHive evt("Une partie est d�j� en cours (ID : " + to_string(partieEnCours->getId()) + ").\n");
        notifierObservers(evt);
        return;
    }

    Partie* partie = getPartie(idPartie);

    if (partie) {
        partieEnCours = partie;
        partie->demarrer();

        EvenementHive evt("Partie avec l'ID " + to_string(idPartie) + " demarree\n");
        notifierObservers(evt);
    }
}

//Surcharge (si besoin)
void Hive::demarrerPartie(Partie* partie) {
    if (partie == nullptr) {
        throw HiveException("La partie fournie est invalide !");
    }

    if (partieEnCours != nullptr) {
        EvenementHive evt("Une partie est d�j� en cours (ID : " + to_string(partieEnCours->getId()) + ").\n");
        notifierObservers(evt);
        return;
    }

    partieEnCours = partie;
    partieEnCours->demarrer();
}

// Terminer la partie en cours
void Hive::terminerPartie() {
    if (partieEnCours == nullptr) {
        EvenementHive evt("Aucune partie n'est en cours.\n");
        notifierObservers(evt);
        return;
    }

    partieEnCours->terminer();

    EvenementHive evt("Partie avec l'ID " + to_string(partieEnCours->getId()) + " termin�e\n");
    notifierObservers(evt);

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
    }
}