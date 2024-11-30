#pragma once
#include "Coordonnee.h"
#include "Piece.h"
#include "Hive.h"
#include <vector>
#include <iostream>

using namespace std;
namespace Hive {
	class Case
	{
	private:
		Coordonnee &c;
		vector<Piece>& pieces;
		bool occuppee;
		bool hasNeighbors;
	public:
		Coordonnee getCoord() const { return c; }
		void ajouterPiece(Piece& piece);
		void retirerPiece(Piece& piece);
		bool getOccuppee() const { return occuppee; }
		bool getHasNeighbors() const { return !getNeighbors().empty(); }
		vector<Case> getNeighbors() const;
	}; 
	Case* getCaseByCoord(Coordonnee& c, const Plateau& p);
}
