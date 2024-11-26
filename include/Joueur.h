#pragma once
#include "MainPiece.h"

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
		void placerPiece(Piece& piece, Coordonnee c);
		void PrendrePiece(Piece& piece);

	};
}