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
    etatPartie(EtatPartie::NON_COMMENCEE),
    joueurActuel(j1)
{}


// Methodes principales
void Partie::demarrer() {
    if (etatPartie == EtatPartie::EN_COURS) {
        throw HiveException("La partie est déjà en cours !");
    }

    if (etatPartie == EtatPartie::TERMINEE) {
        throw HiveException("La partie est terminée !");
    }


    // Si la partie n'a jamais commencé, il faut la mettre en place. Sinon, on la reprend.
    if (etatPartie == EtatPartie::NON_COMMENCEE) {
        initialiser();
    }
    else {
        reprendre();
    }

    etatPartie = EtatPartie::EN_COURS;
}

void Partie::initialiser() {
    EvenementPartie evt("La partie " + to_string(id) + " commence !", id, TypeEvenement::DEBUT_PARTIE);
    notifierObservers(evt);
}

void Partie::reprendre() {
    EvenementPartie evt("La partie " + to_string(id) + " reprend !", id, TypeEvenement::REPRISE_PARTIE);
    notifierObservers(evt);
}

void Partie::mettreEnPause() {
    if (etatPartie != EtatPartie::EN_COURS) {
        throw HiveException("La partie n'est pas en cours");
    }

    etatPartie = EtatPartie::EN_PAUSE;
    EvenementPartie evt("La partie " + to_string(id) + " est mise en pause !", id, TypeEvenement::PAUSE_PARTIE);
    notifierObservers(evt);
}

void Partie::terminer() {
    if (etatPartie != EtatPartie::EN_COURS) {
        throw HiveException("Impossible de terminer une partie qui n'est pas en cours !");
    }

    etatPartie = EtatPartie::TERMINEE;
    EvenementPartie evt("La partie " + to_string(id) + " est terminée.", id, TypeEvenement::FIN_PARTIE);
    notifierObservers(evt);
}




void Partie::jouerCoup(const Coup& coup) {
    /*
    if (!estCoupValide(coup)) {
        throw HiveException("Coup invalide !");
    }
    historique.ajouterCoup(coup);
    */
    tourSuivant();
}

void Partie::changerJoueurActuel() {
    joueurActuel = (joueurActuel.getNom() == joueur1.getNom()) ? joueur2 : joueur1; // Le getNom est temporaire en attendant l'opérateur de comparaison
    EvenementPartie evt("C'est au tour de " + joueurActuel.getNom() + ".", id, TypeEvenement::CHANGEMENT_JOUEUR);
    notifierObservers(evt);
}

void Partie::tourSuivant() {
    if (etatPartie != EtatPartie::EN_COURS) {
        throw HiveException("Impossible de passer le tour d'une partie qui n'est pas en cours !");
    }

    EvenementPartie evt("Le tour suivant commence.", id, TypeEvenement::TOUR_SUIVANT);
    notifierObservers(evt);

    changerJoueurActuel();
}

/*
void Partie::annulerDernierCoup() {
    if (historique.estVide()) {
        throw HiveException("Il n'y a aucun coup � annuler.");
    }
    Coup dernierCoup = historique.getDernierCoup();
    plateau.annulerCoup(dernierCoup);
    historique.supprimerDernierCoup();
    EvenementPartie evt("Dernier coup annulé : " + dernierCoup.getDescription(), id, EvenementPartie::TypeEvenement::ANNULER_COUP);
    notifierObservers(evt);
}
*/


// Methodes utilitaires
void Partie::afficher(ostream& os) const {
    ResumePartie resume = resumer();  // Récupère un résumé de la partie
    os << resume.id << " : " << resume.joueur1 << " vs " << resume.joueur2 << " - " << resume.etatPartie << endl;
}




// Abstraction de l'affichage
ResumePartie Partie::resumer() const {
    ResumePartie resume;
    resume.id = id;
    resume.joueur1 = joueur1.getNom();
    resume.joueur2 = joueur2.getNom();
    switch (etatPartie) {
    case EtatPartie::NON_COMMENCEE:
        resume.etatPartie = "Non commencee";
        break;
    case EtatPartie::EN_COURS:
        resume.etatPartie = "En cours";
        break;
    case EtatPartie::EN_PAUSE:
        resume.etatPartie = "En pause";
        break;
    case EtatPartie::TERMINEE:
        resume.etatPartie = "Terminée";
        break;
    }
    return resume;
}



ostream& JeuHive::operator<<(ostream& os, const Partie& partie)
{
    partie.afficher(os);
    return os;
}
