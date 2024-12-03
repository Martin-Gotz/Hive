#include "../include/Joueur.h"
#include "../include/Coordonnee.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

namespace JeuHive {


Joueur::Joueur(std::string nom, TypeJoueur type, Couleur couleur)
    : nom(nom), type(type), couleur(couleur) {}


void Joueur::jouerCoup(Coup& coup) {
    std::cout << nom << " joue un coup." << std::endl;
}

void Joueur::placerPiece(Piece& piece, Coordonnee c, Plateau& plateau) {
    // Vérifier si la pièce est dans la main
    auto it = std::find(main.begin(), main.end(), piece);
    if (it != main.end()) {
        plateau.placerPiece(piece, c);
        main.erase(it); // Retirer la pièce de la main
        std::cout << nom << " a placé la pièce à (" << c.get_q() << ", " << c.get_r() << ")." << std::endl;
    } else {
        std::cout << "Erreur : la pièce n'est pas dans la main de " << nom << "." << std::endl;
    }
}

// Prendre une pièce (par exemple, au début de la partie ou en cas de récupération)
void Joueur::prendrePiece(Piece& piece) {
    main.push_back(piece);
    std::cout << nom << " a pris une pièce." << std::endl;
}

// Ajouter une pièce à la main
void Joueur::ajouterPieceMain(Piece piece) {
    main.push_back(piece);
}

} // namespace JeuHive
