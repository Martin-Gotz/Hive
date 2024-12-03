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
		//friend ostream& operator<<(ostream& f, Plateau& p); une autre m�thode est d�j� pr�sente

		size_t getNombreCases() const { return Cases.size(); }
		size_t getNombrePieces() const;
		bool estVide() const { return Cases.empty();}
		
		

		void ajouterPieceSurCoo(const Piece& piece, const Coordonnee& coo);
		void retirerPieceDeCoo(const Coordonnee& coo);


		Case* getCaseDeCoo(const Coordonnee& coo) const;
		// Case* getCaseDePiece(const Piece&) const;

		vector<Case*> getVoisinsDeCase(const Case& Case) const;

		bool estAbeillePlacee(Couleur couleur) const;

		// ------------------ m�thodes li�es au mouvements et aux placements-------------------

		set<Coordonnee> ensemblePlacementsPossibles(const Piece& piece, int tour) const;

		bool deplacementPossible(const Piece& piece, const Coordonnee& coo) const;	
		// v�rifie juste que la ruche ne devienne pas coup�e

		set<Coordonnee> ensembleDeplacementsPossibles(const Piece& piece, const Coordonnee& coo);
		// l'id�e est d'appeler cette m�thode avec les m�me arguments que deplacementPossible uniquement 
		// si ce dernier renvoie true


	};
	ostream& operator<<(ostream& f, const Plateau& p);

}

