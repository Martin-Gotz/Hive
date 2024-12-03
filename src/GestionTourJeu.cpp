#include "GestionTourJeu.h"

namespace JeuHive {

// Constructeur
GestionTourJeu::GestionTourJeu(Partie *p) : partie(p) {}

// Gestion du passage au tour suivant
void GestionTourJeu::tourSuivant() {
    Joueur *joueurActuel = partie->getJoueurActuel();

    // Passer au joueur suivant
    partie->changerJoueurActuel();

    // Afficher le joueur actuel
    std::cout << "C'est au tour de " << partie->getJoueurActuel()->getNom() << std::endl;
}

// Afficher le joueur actuel
void GestionTourJeu::afficherJoueurActuel() {
    Joueur *joueurActuel = partie->getJoueurActuel();
    std::cout << "C'est au tour de " << joueurActuel->getNom() << std::endl;
}

} // namespace JeuHive

