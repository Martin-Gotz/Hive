#include "../include/Plateau.h"

using namespace Hive;
#include <algorithm>	// pour le set_difference


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
	set<Coordonnee> voisinsBonneCouleur;		// voisins des pièces de la même couleur que piece
	set<Coordonnee> voisinsMauvaiseCouleur;	// voisins des pièces de la couleur opposée piece
	Case* case_ptr;	
	Piece* piece_dessus;
	vector<Coordonnee> coo_voisines;
	Coordonnee coo;
	unordered_map<Coordonnee, Case*>::iterator itr;

	for (itr = Cases.begin();
		itr != Cases.end(); itr++)
	{
		coo = itr->first;
		case_ptr = itr->second;

		coo_voisines = coo.getVoisins();
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


