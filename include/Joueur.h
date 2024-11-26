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
		// il faut �galement regarder quelles sont les cases qui sont �lligibles � ce d�placement
		void PrendrePiece(Piece& piece);
	};
}