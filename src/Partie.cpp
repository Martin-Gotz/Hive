#include "../include/Partie.h"
using namespace JeuHive;

//Constructeurs
Partie::Partie(int id, Joueur& j1, Joueur& j2) :
    id(id),
    joueur1(j1),
    joueur2(j2),
    plateau(),
    regles(),
    historique(),
    etatPartie(EtatPartie::EN_PAUSE),
    joueurActuel(j1)
{}


// Methodes principales
void Partie::demarrer() {
    if (etatPartie == EtatPartie::EN_COURS) {
        throw HiveException("La partie est deja en cours !");
    }
    etatPartie = EtatPartie::EN_COURS;
    cout << "La partie " << id << " commence !" << endl;
}

void Partie::terminer() {
    if (etatPartie != EtatPartie::EN_COURS) {
        throw HiveException("Impossible de terminer une partie qui n'est pas en cours !");
    }
    etatPartie = EtatPartie::TERMINEE;
    cout << "La partie " << id << " est terminee." << endl;
}

/*
void Partie::jouerCoup(const Coup& coup) {
    if (!estCoupValide(coup)) {
        throw HiveException("Coup invalide !");
    }
    historique.ajouterCoup(coup);
    tourSuivant();
}
*/

void Partie::changerJoueurActuel() {
    joueurActuel = (joueurActuel.getNom() == joueur1.getNom()) ? joueur2 : joueur1; // Le getNom est temporaire en attendant l'opérateur de comparaison
}

void Partie::tourSuivant() {
    if (etatPartie != EtatPartie::EN_COURS) {
        throw HiveException("Impossible de passer le tour d'une partie qui n'est pas en cours !");
    }

    cout << "Tour suivant." << endl;
}

/*
void Partie::annulerDernierCoup() {
    if (historique.estVide()) {
        throw HiveException("Il n'y a aucun coup � annuler.");
    }
    Coup dernierCoup = historique.getDernierCoup();
    plateau.annulerCoup(dernierCoup);
    historique.supprimerDernierCoup();
}
*/

// Methodes utilitaires
void Partie::afficher(ostream& os) const {
    os << id << " : " << joueur1.getNom() << " / " << joueur2.getNom() << " - ";

    os << "Etat : ";
    switch (etatPartie) {
    case EtatPartie::EN_PAUSE:
        os << "En pause";
        break;
    case EtatPartie::EN_COURS:
        os << "En cours";
        break;
    case EtatPartie::TERMINEE:
        os << "Terminee";
        break;
    default:
        os << "Inconnu";
        break;
    }

    os << endl;
}
