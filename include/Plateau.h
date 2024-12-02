#pragma once
#include <iostream>
#include <vector>
#include "Case.h"
#include <unordered_map>
#include "Enums.h"
#include "Exceptions.h"
#include <set>

using namespace std;
namespace Hive {

	class Plateau	// responsable des cases
	{
	private:
		unordered_map<Coordonnee, Case*> Cases;
	public:
		const unordered_map<Coordonnee, Case*> getCases() const { return Cases; }
		Plateau() {}
		//friend ostream& operator<<(ostream& f, Plateau& p); une autre méthode est déjà présente
		size_t getNombreCases() const { return Cases.size(); }
		bool estVide() const { return Cases.empty();}
		
		set<Coordonnee> EnsemblePlacementsPossibles(const Piece& piece, int tour, bool abeillePlacee) const;
		void ajouterPieceSurCoo(const Piece&, const Coordonnee&);
		void retirerPieceDeCoo(const Coordonnee&);
		Case* getCaseDeCoo(const Coordonnee&) const;
		vector<Case*> getVoisinsDeCase(const Case& Case) const;
	};
	ostream& operator<<(ostream& f, const Plateau& p);

}

