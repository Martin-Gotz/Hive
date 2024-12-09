#pragma once
#include <iostream>
#include <vector>
#include "Case.h"
#include <unordered_map>
#include "Enums.h"
#include "Exceptions.h"
#include "Coup.h"
#include <set>
//#include <sstream>

using namespace std;
namespace JeuHive {

	class Plateau	// responsable des cases
	{
	private:
		unordered_map<Coordonnee, Case*> Cases;

		void ajouterPieceSurCoo(const Piece& piece, const Coordonnee& coo);
		void retirerPieceDeCoo(const Coordonnee& coo);
		// dans la partie priv�e car l'utilisation de ces m�thodes n�cessites des v�rifications du respect des r�gles
	public:
		const unordered_map<Coordonnee, Case*> getCases() const { return Cases; }
		Plateau() {}
		//friend ostream& operator<<(ostream& f, Plateau& p); une autre m�thode est d�j� pr�sente

		size_t getNombreCases() const { return Cases.size(); }
		size_t getNombrePieces() const;
		bool estVide() const { return Cases.empty();}
		
		Case* getCaseDeCoo(const Coordonnee& coo) const;
		Case* getCaseDePiece(const Piece& piece) const;
		bool estPlacee(const Piece& piece) const;

		vector<Case*> getVoisinsDeCoo(const Coordonnee& coo) const;

		bool estAbeillePlacee(Couleur couleur) const;

		bool estAbeilleEntouree(Couleur couleur) const;

		bool estPartieFinie() const {
			return (estAbeillePlacee(BLANC) && estAbeilleEntouree(BLANC))
				&& (estAbeillePlacee(NOIR) && estAbeilleEntouree(NOIR));
		}

		// ------------------ m�thodes li�es au mouvements et aux placements-------------------

		set<Coordonnee> ensemblePlacementsPossibles(const Piece& piece, int tour) const;

		bool deplacementPossible(const Piece& piece, const Coordonnee& coo) const;	
		// v�rifie juste que la ruche ne devienne pas coup�e

		set<Coordonnee> getCooVoisinesGlissement(const Coordonnee& coo, const Coordonnee* ignorer_coo=nullptr) const;
		// renvoie les coordonn�es libres que la case peu atteindre un bougeant d'une case en glissant
		// �a rajoute une contrainte en plus que getVoisinsDeCoo car des pi�ces voisines peuvent bloquer un glissement
		// (voir r�gles du jeu)

		ostream& afficher(ostream& f, vector<Coordonnee> coos_surligner, vector<Coordonnee> coos_selectionnees, 
			int marge=1) const;

		// modification du plateau

		void jouerCoup(Coup* coup);
		void jouerPlacement(CoupPlacement* coup);
		void jouerDeplacement(CoupDeplacement* coup);

		void inverserCoup(Coup* coup);
		void inverserPlacement(CoupPlacement* coup);
		void inverserDeplacement(CoupDeplacement* coup);


	};
	ostream& operator<<(ostream& f, const Plateau& p);

}

