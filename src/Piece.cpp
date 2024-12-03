#include "../include/Piece.h"
#include "../include/Plateau.h"

namespace JeuHive{
	set<Coordonnee> Abeille::ensembleDeplacementPossibles(const Plateau& plateau, const Coordonnee& coo) const
	{
		if (!plateau.deplacementPossible(*this, coo)) {
			return set<Coordonnee>();
		}
		return plateau.getCooVoisinesGlissement(coo);
	}

	set<Coordonnee> Scarabee::ensembleDeplacementPossibles(const Plateau& plateau, const Coordonnee& coo) const
	{
		if (!plateau.deplacementPossible(*this, coo)) {
			return set<Coordonnee>();
		}

		vector<Coordonnee> coos_voisines = coo.getVoisins();
		set<Coordonnee> resultat(coos_voisines.begin(), coos_voisines.end());	// convertion de set à vector
	}

	set<Coordonnee> Araignee::ensembleDeplacementPossibles(const Plateau& plateau, const Coordonnee& coo) const
	{
		// l'entier représente le nombre de mouvements d'une case effectués. Agit comme une file
		vector<pair<int,Coordonnee>> coos_intermediaires = { pair<int, Coordonnee>(0, coo)};
		set<Coordonnee> resultat;

		int generation;
		Coordonnee coo_intermediaire;
		set<Coordonnee> nouv_coos;
		while (coos_intermediaires.size()>0){
			generation = coos_intermediaires.front().first;
			coo_intermediaire = coos_intermediaires.front().second;

			nouv_coos = plateau.getCooVoisinesGlissement(coo_intermediaire);

			if (generation == 3) {
				for (Coordonnee nouv_coo : nouv_coos) {
					resultat.insert(nouv_coo);
				}
			}
			else {
				for (Coordonnee nouv_coo : nouv_coos) {
					coos_intermediaires.push_back(pair<int, Coordonnee>(generation+1, nouv_coo));
				}
			}

			coos_intermediaires.erase(coos_intermediaires.begin());
		}
	}



}