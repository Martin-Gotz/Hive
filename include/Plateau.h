#pragma once
#include <iostream>
#include <vector>
#include "Coordonnee.h"
#include "Case.h"
#include <unordered_map>
#include "Enums.h"
#include <set>

using namespace std;
namespace Hive {

	class Plateau
	{
	private:
		unordered_map<Coordonnee, Case*> Cases;
	public:
		unordered_map<Coordonnee, Case*> getCases() const { return Cases; }
		Plateau() : Cases({}) {}
		//friend ostream& operator<<(ostream& f, Plateau& p); une autre méthode est déjà présente
		int getNombreCases() const { return Cases.size(); }
		
		set<Coordonnee> EnsemblePlacementPossibles(Piece& p);	// c'est quoi?
		void ajouterPieceSurCoo(Piece&, Coordonnee&);
		void retirerPieceDeCoo(Coordonnee&);
	};
	ostream& operator<<(ostream& f, const Plateau& p);

}

