#include "../include/Plateau.h"

using namespace Hive;
#include <algorithm>	// pour le set_difference


void Plateau::ajouterPieceSurCoo(Piece& piece, Coordonnee& coo) {

	Case* case_sur_coo = GetCaseDeCoo(coo);
	
	if (case_sur_coo == nullptr) {
		Case* nouv_case = new Case(coo);
		Cases.insert(make_pair(coo, nouv_case));
		nouv_case->ajouterPiece(piece);
	}
	else {
		case_sur_coo->ajouterPiece(piece);
	}
}

void Plateau::retirerPieceDeCoo(Coordonnee& coo) {
	Case* case_sur_coo = GetCaseDeCoo(coo);

	if (case_sur_coo == nullptr) {
		throw HiveException("Aucune pi�ce ne se trouve � ces coordonn�es");
	}
	else {
		case_sur_coo->retirerPiece();

		if (case_sur_coo->estVide()) {
			Cases.erase(coo);
			delete case_sur_coo;
		}
	}
}

Case* Plateau::GetCaseDeCoo(Coordonnee& coo) const {

}

ostream& operator<<(ostream& f, const Plateau& p)
	{
		f << "Nombre de cellules : " << p.getNombreCases() << "\n";
		int i = 0;
		unordered_map<Coordonnee, Case*>::iterator itr;
		for (itr = p.getCases().begin();
			itr != p.getCases().end(); itr++)
		{
			f << "Case num�ro : " << i++ << " Coordonn�es : (" << itr->first.get_q() << itr->first.get_r() << ")\n";
		}
		return f;
	}

set<Coordonnee> Plateau::EnsemblePlacementPossibles(Piece& piece)
{
	// les placements possibles seront : 
	// ceux qui seront en contact avec une autre case
	// En fait non: ne tient pas en compte l'abeille (ce sera g�r� plus haut)
	// pr�c�demment : "au 5 �me tour, on doit s'assurer que la reine a �t� plac�e"
	// les cases d�j� occup�es ne sont pas �ligibles

	// explication de l'algorithme:
	// On cr�e un ensemble de case voisinsBonneCouleur qui repr�sente l'ensembles des voisins de chaque pi�ces 
	// de la m�me couleur que piece.
	// pareil avec voisinsMauvaiseCouleur mais avec la couleur oppos�e
	// Les cases sur lesquelles on peut placer la pi�ce sont les cases voisines d'une pi�ce de la m�me couleur, mais pas
	// voisines d'une pi�ce de la couleur oppos�e. Ce r�sultat s'obtient en prenant la diff�rence des deux ensembles
	// avec set_difference

	set<Coordonnee> voisinsBonneCouleur;		// voisins des pi�ces de la m�me couleur que piece
	set<Coordonnee> voisinsMauvaiseCouleur;	// voisins des pi�ces de la couleur oppos�e piece
	const Case* case_ptr;	
	const Piece* piece_dessus;
	vector<Coordonnee> coo_voisines;
	Coordonnee coo_case;
	unordered_map<Coordonnee, Case*>::iterator itr;

	for (itr = Cases.begin();
		itr != Cases.end(); itr++)
	{
		coo_case = itr->first;
		case_ptr = itr->second;

		coo_voisines = coo_case.getVoisins();
		piece_dessus = case_ptr->getDessus();

		for (auto coo_voisine : coo_voisines) {
			if (piece_dessus->GetCouleur() == piece.GetCouleur()) {
				voisinsBonneCouleur.insert(coo_voisine);
			}
			else {
				voisinsMauvaiseCouleur.insert(coo_voisine);
			}
		}
	}

	set<Coordonnee> difference;

	set_difference(
		voisinsBonneCouleur.begin(), voisinsBonneCouleur.end(), voisinsMauvaiseCouleur.begin(), voisinsMauvaiseCouleur.end(),
		inserter(difference, difference.begin()));

	return difference;
}


vector<const Case*> Plateau::getVoisinsDeCase(Case& case0) const
// on ne peut pas �crire case car c'est un mot cl�
{
	vector<const Case*> voisins;
	vector<Coordonnee> coo_voisines = case0.getCoo().getVoisins();
	const Case* case_voisine;

	for (auto coo_voisine : coo_voisines) {
		case_voisine = GetCaseDeCoo(coo_voisine);// Si une case se trouve sur la coordonnee voisine
		if (case_voisine != nullptr) {
			voisins.push_back(case_voisine);
		}	

	}
	return voisins;

}

