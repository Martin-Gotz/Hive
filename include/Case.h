#pragma once

#include "ResumeClasse.h"
#include <iostream>
#include <vector>
#include "Coordonnee.h"
#include "Piece.h"
#include <stack>


using namespace std;


namespace JeuHive {
	class Case
	{
	private:
		Coordonnee coo;
		vector<const Piece*> pieces;
	public:
		const Coordonnee& getCoo() const { return coo; }
		void ajouterPiece(const Piece* piece) { pieces.push_back(piece); }
		void retirerPiece() { pieces.pop_back(); }
		const Piece& getDessus() const {
			const Piece& piece = *pieces.back();
			return piece;
		}
		const vector<const Piece*>& getPieces() const { return pieces; }

		bool estVide() const { return pieces.empty(); }	// très peu pertinent car une case vide devrait être supprimée
		int getNombrePieces() const { return static_cast<int>(pieces.size()); }
		Case(const Coordonnee& coo) : coo(coo) {}

		string toString() const;
		ResumeCase resumer() const;
	};
	ostream& operator<<(ostream& os, const Case& c);
}

