#include "../include/Plateau.h"

using namespace Hive;

vector<Case> Plateau::getCases() const
	{
		return Cases;
	}

ostream& operator<<(ostream& f, const Plateau& p)
	{
		f << "Les cellules dans le plateau num�ro : " << p.getId() << "\n";
		f << "Nombre de cellules : " << p.getNombreCases() << "\n";
		int i = 0;
		for (const auto& cell : p.getCases())
		{
			f << "Case num�ro : " << i++ << " Coordonn�es : (" << cell.getCoord().get_q() << cell.getCoord().get_r() << ")\n";
		}
		return f;
	}

vector<Case> Plateau::EnsemblePlacementPossibles()
{
	// les placements possibles seront : 
	// ceux qui seront en contact avec une autre case
	// au 5 �me tour, on doit s'assurer que la reine a �t� plac�e
	// les cases d�j� occup�es ne sont pas �ligibles
	vector<Case> CaseElligible;
	for (const auto& cell : getCases())
	{
		if (!cell.getOccuppee() && cell.getHasNeighbors())
		{

		}
	}

}