#include "../include/Plateau.h"

using namespace Hive;
#include <algorithm>	// pour le set_difference
#include "Exceptions.h"



ostream& operator<<(ostream& f, const Plateau& p)
	{
		f << "Nombre de cellules : " << p.getNombreCases() << "\n";
		int i = 0;
		unordered_map<Coordonnee, Case*>::iterator itr;
		for (itr = p.getCases().begin();
			itr != p.getCases().end(); itr++)
		{
			f << "Case numéro : " << i++ << " Coordonnées : (" << itr->first.get_q() << itr->first.get_r() << ")\n";
		}
		return f;
	}

set<Coordonnee> Plateau::EnsemblePlacementPossibles(Piece& piece)
{
	// les placements possibles seront : 
	// ceux qui seront en contact avec une autre case
	// En fait non: ne tient pas en compte l'abeille (ce sera géré plus haut)
	// précédemment : "au 5 ème tour, on doit s'assurer que la reine a été placée"
	// les cases déjà occupées ne sont pas éligibles

	// explication de l'algorithme:
	// On crée un ensemble de case voisinsBonneCouleur qui représente l'ensembles des voisins de chaque pièces 
	// de la même couleur que piece.
	// pareil avec voisinsMauvaiseCouleur mais avec la couleur opposée
	// Les cases sur lesquelles on peut placer la pièce sont les cases voisines d'une pièce de la même couleur, mais pas
	// voisines d'une pièce de la couleur opposée. Ce résultat s'obtient en prenant la différence des deux ensembles
	// avec set_difference

	set<Coordonnee> voisinsBonneCouleur;		// voisins des pièces de la même couleur que piece
	set<Coordonnee> voisinsMauvaiseCouleur;	// voisins des pièces de la couleur opposée piece
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
// on ne peut pas écrire case car c'est un mot clé
{
	vector<const Case*> voisins;
	vector<Coordonnee> coo_voisines = case0.getCoo().getVoisins();
	const Case* case_voisine;

	for (auto coo_voisine : coo_voisines) {
		try {
			case_voisine = &GetCaseDeCoo(coo_voisine);
			voisins.push_back(case_voisine);
		}
		catch (HiveException& e) {}		// Si aucune case ne se trouve sur la coordonnee voisine

	}
	return voisins;

}

