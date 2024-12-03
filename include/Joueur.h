#pragma once
#pragma once
#include "MainPiece.h"
#include "Coup.h"
#include "Piece.h"
#include "Coordonnee.h"
#include "Plateau.h"
#include <string>
#include <vector>

namespace JeuHive {

enum class TypeJoueur { HUMAIN, IA }; // Type du joueur : humain ou IA
enum class Couleur { NOIR, BLANC };  

class Joueur {
private:
    std::string nom;             
    TypeJoueur type;            
    Couleur couleur;            
    std::vector<Piece> main;     

public:
    Joueur(std::string nom, TypeJoueur type, Couleur couleur);
    // Méthodes principales
    void jouerCoup(Coup& coup);
    void placerPiece(Piece& piece, Coordonnee c, Plateau& plateau);
    void prendrePiece(Piece& piece);

    std::string getNom() const { return nom; }
    Couleur getCouleur() const { return couleur; }
    const std::vector<Piece>& getMain() const { return main; }

    // Ajouter une pièce à la main
    void ajouterPieceMain(Piece piece);
};

} // namespace JeuHive
