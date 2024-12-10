#include "../include/Joueur.h"
#include "../include/Coordonnee.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

namespace JeuHive {


Joueur::Joueur(string nom, TypeJoueur type, Couleur couleur)
    : nom(nom), type(type), couleur(couleur) {}


void Joueur::jouerCoup(Coup& coup) {
    cout << nom << " joue un coup." << endl;
}


void Joueur::placerPiece(Piece& piece, Coordonnee c, Plateau& plateau) {
    // Vérifier si la pièce est dans la main
    auto it = find(main.begin(), main.end(), &piece);
    if (it != main.end()) {
        //plateau.placerPiece(piece, c);
        main.getPieces().erase(it); // Retirer la pièce de la main
        cout << nom << " a placé la pièce à (" << c.get_q() << ", " << c.get_r() << ")." << endl;
    } else {
        cout << "Erreur : la pièce n'est pas dans la main de " << nom << "." << endl;
    }
}

void Joueur::afficher(ostream& f) const
{
    ResumeJoueur resumejoueur = resumer();
    f << "Nom du joueur : " << resumejoueur.nom << " , couleur : " << resumejoueur.couleur << " , type : " << resumejoueur.type;
    main.afficher(f);
}

ResumeJoueur Joueur::resumer() const
{
    ResumeJoueur joueur_resume;
    joueur_resume.couleur = couleur;
    joueur_resume.nom = nom;
    joueur_resume.type = type;
    joueur_resume.main = main.resumer();
    return joueur_resume;
}
/*
// Prendre une pièce (par exemple, au début de la partie ou en cas de récupération)
void Joueur::prendrePiece(Piece& piece) {
    main.push_back(piece);
    cout << nom << " a pris une pièce." << endl;
}

// Ajouter une pièce à la main
void Joueur::ajouterPieceMain(Piece piece) {
    main.push_back(piece);
}
*/

} // namespace JeuHive
