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
		size_t getNombrePieces() const;
		bool estVide() const { return Cases.empty();}
		
		

		void ajouterPieceSurCoo(const Piece& piece, const Coordonnee& coo);
		void retirerPieceDeCoo(const Coordonnee& coo);


		Case* getCaseDeCoo(const Coordonnee& coo) const;
		// Case* getCaseDePiece(const Piece&) const;

		vector<Case*> getVoisinsDeCase(const Case& Case) const;

		bool estAbeillePlacee(Couleur couleur) const;

		// ------------------ méthodes liées au mouvements et aux placements-------------------

		set<Coordonnee> ensemblePlacementsPossibles(const Piece& piece, int tour) const;

		bool deplacementPossible(const Piece& piece, const Coordonnee& coo) const;	
		// vérifie juste que la ruche ne devienne pas coupée

		set<Coordonnee> ensembleDeplacementsPossibles(const Piece& piece, const Coordonnee& coo);
		// l'idée est d'appeler cette méthode avec les même arguments que deplacementPossible uniquement 
		// si ce dernier renvoie true


	};
	ostream& operator<<(ostream& f, const Plateau& p);

}

