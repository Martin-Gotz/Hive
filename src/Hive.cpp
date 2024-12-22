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

void Hive::ajouterPartie(const string& nomJoueur1, TypeJoueur typeJoueur1, const string& nomJoueur2, TypeJoueur typeJoueur2, int nombreRetours = 0) {
    // Instancier les joueurs
    Joueur joueur1(nomJoueur1, typeJoueur1);
    Joueur joueur2(nomJoueur2, typeJoueur2);

    // Cr�er une nouvelle partie en utilisant la factory
    parties.push_back(FabriquePartie::creerPartie(joueur1, joueur2, nombreRetours));
    EvenementHive evt("Nouvelle partie creee \n");
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

    if (*it) {
        delete* it;
        parties.erase(it);
    }

    EvenementHive evt("Partie " + to_string(idPartie) + " supprimee\n");
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

void Hive::demarrerPartie(int idPartie) {
    // V�rifie si une partie avec l'ID donn� existe
    Partie* partie = getPartie(idPartie);
    if (!partie) {
        throw HiveException("Aucune partie trouv�e !");
    }

    // V�rifie s'il y a d�j� une partie en cours
    if (partieEnCours != nullptr) {
        EvenementHive evt("Une partie est d�j� en cours (ID : " + to_string(partieEnCours->getId()) + ").");
        notifierObservers(evt);
        return;
    }

    // Notifie les observateurs
    EvenementHive evt("Demarrage de la partie " + to_string(idPartie));
    notifierObservers(evt);


    partie->demarrer();
    partieEnCours = partie;
    
}

// Terminer la partie en cours
void Hive::terminerPartie() {
    if (partieEnCours == nullptr) {
        throw HiveException("Aucune partie n'est en cours.");
        return;
    }

    partieEnCours->terminer();

    EvenementHive evt("Abandon de la partie " + to_string(partieEnCours->getId()));
    notifierObservers(evt);

    partieEnCours = nullptr;
}



// Mettre en pause la partie en cours
void Hive::mettrePartieEnPause() {
    if (partieEnCours == nullptr) {
        throw HiveException("Aucune partie n'est en cours.");
        return;
    }

    partieEnCours->mettreEnPause();

    partieEnCours = nullptr;
}





// Formatage des donn�es pour l'abstraction de l'affichage
EtatHive Hive::resumer() const {
    EtatHive etat;
    for (const auto& partie : parties) {
        if (partie) {
            etat.parties.push_back(partie->resumer());
        }
    }
    if (partieEnCours) {
        etat.idPartieEnCours = partieEnCours->getId();
    }
    return etat;
}
