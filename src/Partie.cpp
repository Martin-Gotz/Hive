#include "../include/Partie.h"
#include <random>
using namespace JeuHive;
using namespace std;


// Initialisation du compteur statique
int Partie::prochain_id = 1;


//Constructeurs
Partie::Partie(Joueur& j1, Joueur& j2) :
    id(prochain_id),
    joueur1(j1),
    joueur2(j2),
    plateau(),
    regles(),
    historique(),
    etatPartie(EtatPartie::NON_COMMENCEE),
    joueurActuel(nullptr),
    compteurTour(0)
{
    prochain_id++; // Incrémentation du compteur statique pour suivre le nombre de parties créé
}


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


// Mise en place des éléments la première fois que la partie est lancée
void Partie::initialiser() {
    // 1 : Initialisation des joueurs (et pièces)

    // Génération aléatoire de la couleur
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, 1);

    if (distrib(gen) == 0) {
        joueur1.setCouleur(Couleur::BLANC);
        joueur2.setCouleur(Couleur::NOIR);
        joueurActuel = &joueur1; // Le joueur blanc commence
    }
    else {
        joueur1.setCouleur(Couleur::NOIR);
        joueur2.setCouleur(Couleur::BLANC);
        joueurActuel = &joueur2; // Le joueur blanc commence
    }

    joueur1.remplirMain();
    joueur2.remplirMain();


    // 2 : Initialisation du plateau

    /*
    Abeille* A_b = new Abeille(Couleur::BLANC);
    Abeille* A_n = new Abeille(Couleur::NOIR);
    Araignee* a_b = new Araignee(Couleur::BLANC);
    Sauterelle* s_n = new Sauterelle(Couleur::NOIR);
    Scarabee* S_b = new Scarabee(Couleur::BLANC);
    Fourmi* F_n = new Fourmi(Couleur::NOIR);
    Fourmi* F_b = new Fourmi(Couleur::BLANC);


    plateau.ajouterPieceSurCoo(A_b, Coordonnee(0, 0));
    plateau.ajouterPieceSurCoo(A_n, Coordonnee(0, 1));
    plateau.ajouterPieceSurCoo(a_b, Coordonnee(1, 0));
    plateau.ajouterPieceSurCoo(s_n, Coordonnee(-1, 1));
    plateau.ajouterPieceSurCoo(S_b, Coordonnee(1, -1));
    plateau.ajouterPieceSurCoo(F_n, Coordonnee(-1, 0));
    */
    // 3 : Règles spécifiques de début de partie
    compteurTour = 1;

    EvenementPartie evt(id, TypeEvenement::DEBUT_PARTIE);
    notifierObservers(evt);
}

void Partie::reprendre() {
    EvenementPartie evt(id, TypeEvenement::REPRISE_PARTIE);
    notifierObservers(evt);
}

void Partie::mettreEnPause() {
    if (etatPartie != EtatPartie::EN_COURS) {
        throw HiveException("La partie n'est pas en cours");
    }

    etatPartie = EtatPartie::EN_PAUSE;
    EvenementPartie evt(id, TypeEvenement::PAUSE_PARTIE);
    notifierObservers(evt);
}

void Partie::terminer() {
    if (etatPartie != EtatPartie::EN_COURS) {
        throw HiveException("Impossible de terminer une partie qui n'est pas en cours !");
    }

    etatPartie = EtatPartie::TERMINEE;
    EvenementPartie evt(id, TypeEvenement::FIN_PARTIE);
    notifierObservers(evt);
}




void Partie::jouerCoup(const Coup& coup) {
    /*
    if (!estCoupValide(coup)) {
        throw HiveException("Coup invalide !");
    }
    historique.ajouterCoup(coup);
    */
    joueurSuivant();
}

void Partie::joueurSuivant() {
    if (etatPartie != EtatPartie::EN_COURS) {
        throw HiveException("Impossible de passer le tour d'une partie qui n'est pas en cours !");
    }

    if (joueurActuel->getCouleur() == Couleur::NOIR) {
        compteurTour++;
        EvenementPartie evt(id, TypeEvenement::TOUR_SUIVANT);
        notifierObservers(evt);
    }

    joueurActuel = (joueurActuel->getNom() == joueur1.getNom()) ? &joueur2 : &joueur1; // Le getNom est temporaire en attendant l'opérateur de comparaison

    EvenementPartie evt(id, TypeEvenement::CHANGEMENT_JOUEUR);
    notifierObservers(evt);
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
    os << resume.id << " : " << resume.joueur1.nom << " vs " << resume.joueur2.nom << " - " << resume.etatPartie << endl;
}




// Formatage des données pour l'abstraction de l'affichage
ResumePartie Partie::resumer() const {

    ResumePartie resume;

    resume.id = id;
    resume.joueur1.nom = joueur1.getNom();
    resume.joueur2.nom = joueur2.getNom();
    resume.joueur1.couleur = joueur1.getCouleur();
    resume.joueur2.couleur = joueur2.getCouleur();
    resume.joueur1.main = joueur1.getMain().resumer();
    resume.joueur2.main = joueur2.getMain().resumer();
    if (joueur1.getType() == HUMAIN) resume.joueur1.type = "HUMAIN";
    else resume.joueur1.type = "IA";
    if (joueur2.getType() == HUMAIN) resume.joueur2.type = "HUMAIN";
    else resume.joueur2.type = "IA";

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
