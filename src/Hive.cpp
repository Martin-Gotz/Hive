#include "../include/Hive.h"
using namespace JeuHive;

// Destructeur
Hive::~Hive() {
    // Libération de toutes les parties stockées
    for (Partie* partie : parties) {
        delete partie;
    }
    parties.clear();
}



// Méthodes pour gérer les parties

void Hive::ajouterPartie(Joueur& joueur1, Joueur& joueur2) {
    // Créer une nouvelle partie en utilisant la factory
    int idPartie = parties.size();
    parties.push_back(PartieFactory::creerPartie(idPartie, joueur1, joueur2));

    EvenementHive evenement("Nouvelle partie creee avec l'ID " + to_string(idPartie) +"\n");
    notifierObservers(evenement);
}

// Supprimer une partie
void Hive::supprimerPartie(int idPartie) {
    // Chercher la partie par son identifiant
    auto it = find_if(parties.begin(), parties.end(),
        [idPartie](Partie* p) { return p && p->getId() == idPartie; });

    // Vérifier si la partie existe
    if (it == parties.end()) {
        throw HiveException("Aucune partie trouvee !");
    }

    // Libérer la mémoire et supprimer du vecteur
    if (*it == partieEnCours) {
        partieEnCours = nullptr; // Réinitialiser si c'était la partie en cours
    }

    delete* it;
    parties.erase(it);

    EvenementHive evenement("Partie avec l'ID " + to_string(idPartie) + " supprimee\n");
    notifierObservers(evenement);
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
    return static_cast<int>(parties.size());
}





// Gestion de la partie en cours

// Démarrer une partie
void Hive::demarrerPartie(int idPartie) {
    if (idPartie < 0 || idPartie >= nombreParties()) {
        throw HiveException("Aucune partie trouvee !");
    }

    if (partieEnCours != nullptr) {
        EvenementHive evenement("Une partie est déjà en cours (ID : " + to_string(partieEnCours->getId()) + ").\n");
        notifierObservers(evenement);
        return;
    }

    Partie* partie = getPartie(idPartie);
    if (partie) {
        partieEnCours = partie;
        partie->demarrer();

        EvenementHive evenement("Partie avec l'ID " + to_string(idPartie) + " demarree\n");
        notifierObservers(evenement);
    }
}

//Surcharge (si beoin)
void Hive::demarrerPartie(Partie* partie) {
    if (partie == nullptr) {
        throw HiveException("La partie fournie est invalide !");
    }

    if (partieEnCours != nullptr) {
        EvenementHive evenement("Une partie est déjà en cours (ID : " + to_string(partieEnCours->getId()) + ").\n");
        notifierObservers(evenement);
        return;
    }

    partieEnCours = partie;
    partieEnCours->demarrer();
}

// Terminer la partie en cours
void Hive::terminerPartie() {
    if (partieEnCours == nullptr) {
        EvenementHive evenement("Aucune partie n'est en cours.\n");
        notifierObservers(evenement);
        return;
    }

    partieEnCours->terminer();

    EvenementHive evenement("Partie avec l'ID " + to_string(partieEnCours->getId()) + " terminée\n");
    notifierObservers(evenement);

    partieEnCours = nullptr;
}



// Gestion des observateurs
void Hive::ajouterObserver(Observer* observer) {
    observers.push_back(observer);
}

void Hive::retirerObserver(Observer* observer) {
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

// Notification des observateurs
void Hive::notifierObservers(const Evenement& evenement) {
    for (Observer* observer : observers) {
        observer->notifier(evenement);
    }
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