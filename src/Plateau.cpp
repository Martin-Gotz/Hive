#include "../include/Plateau.h"

using namespace Hive;

vector<Case> Plateau::getCases() const
	{
		return Cases;
	}

ostream& operator<<(ostream& f, const Plateau& p)
	{
		f << "Les cellules dans le plateau numéro : " << p.getId() << "\n";
		f << "Nombre de cellules : " << p.getNombreCases() << "\n";
		int i = 0;
		for (const auto& cell : p.getCases())
		{
			f << "Case numéro : " << i++ << " Coordonnées : (" << cell.getCoord().get_q() << cell.getCoord().get_r() << ")\n";
		}
		return f;
	}

vector<Case> Plateau::EnsemblePlacementPossibles()
{
	// les placements possibles seront : 
	// ceux qui seront en contact avec une autre case
	// au 5 ème tour, on doit s'assurer que la reine a été placée
	// les cases déjà occupées ne sont pas éligibles
	vector<Case> CaseElligible;
	for (const auto& cell : getCases())
	{
		if (!cell.getOccuppee() && cell.getHasNeighbors())
		{

		}
	}

}