#include "../include/Joueur.h"
#include "../include/Coordonnee.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

namespace JeuHive {


Joueur::Joueur(string nom, TypeJoueur type)
    : nom(nom), type(type), couleur(Couleur::BLANC) {}


void Joueur::remplirMain()
{
    main.getPieces().clear();

    ajouterPieceMain(new Abeille(couleur));
    ajouterPieceMain(new Fourmi(couleur));
    ajouterPieceMain(new Araignee(couleur));
    ajouterPieceMain(new Sauterelle(couleur));
    ajouterPieceMain(new Scarabee(couleur));
}





void Joueur::retirerPiece(Piece* piece)
{
    main.retirerPiece(piece);
}

void Joueur::ajouterPieceMain(Piece* piece)
{
    if (piece->getCouleur() != this->getCouleur()) { // Vérifie la couleur du joueur
        throw runtime_error("La pièce ne correspond pas à la couleur du joueur !");
    }

    main.ajouterPiece(piece); // Ajout en transférant la propriété
}

ResumeJoueur Joueur::resumer() const
{
    ResumeJoueur resumeJoueur;
    resumeJoueur.couleur = (couleur == Couleur::BLANC ? "Blanc" : "Noir");
    resumeJoueur.nom = nom;
    resumeJoueur.type = (type == TypeJoueur::HUMAIN ? "Humain" : "Ordinateur");
    resumeJoueur.main = main.resumer();
    return resumeJoueur;
}


}
