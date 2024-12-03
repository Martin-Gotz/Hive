#ifndef GESTION_TOUR_JEU_H
#define GESTION_TOUR_JEU_H

#include "Partie.h"
#include <iostream>

namespace JeuHive {

class GestionTourJeu {
private:
    Partie *partie; // Pointeur vers la partie en cours

public:
    // Constructeur
    GestionTourJeu(Partie *p);

    // Gestion du passage au tour suivant
    void tourSuivant();

    // Afficher le joueur actuel
    void afficherJoueurActuel();
};

} // namespace JeuHive

#endif // GESTION_TOUR_JEU_H
