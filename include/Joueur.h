#pragma once
#include "MainPiece.h"
#include "Coup.h"

namespace Hive {

	enum TypeJoueur {IA, humain};
	enum Couleur {Noir, Blanc};

	class Joueur
	{
	private:
		string nom;
		TypeJoueur type;
		Couleur couleur;
		MainPiece& main;
	public:
		void jouerCoup(Coup& coup);
		void placerPiece(Piece& piece, Coordonnee c, Plateau& p);
		// pour placer une piece, il nous faut la position des autres pieces dans le plateau
		// il faut également regarder quelles sont les cases qui sont élligibles à ce déplacement
		void PrendrePiece(Piece& piece);
	};
}