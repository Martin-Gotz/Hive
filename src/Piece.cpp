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

		// s'il est sur une autre pièce alors il peut aller partout autour
		Case* case0 = plateau.getCaseDeCoo(coo);
		if (case0->getNombrePieces() > 1) {
			vector<Coordonnee> coo_voisines = coo.getVoisins();
			return set<Coordonnee>(coo_voisines.begin(), coo_voisines.end());
		}

		// union des glissements et des chevauchements
		set<Coordonnee> resultat = plateau.getCooVoisinesGlissement(coo);
		
		for (Case* case_voisine : plateau.getVoisinsDeCoo(coo)) {
			resultat.insert(case_voisine->getCoo());
		}
		return resultat;
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
		return resultat;
	}

	set<Coordonnee> Sauterelle::ensembleDeplacementPossibles(const Plateau& plateau, const Coordonnee& coo) const
	{
		vector<Coordonnee> directions = getDirections();

	}

}