#include "../include/Plateau.h"

using namespace Hive;

	vector<Coordonnee> Plateau::getCellules() const
	{
		return Cellules;
	}

	ostream& operator<<(ostream& f, const Plateau& p)
	{
		f << "Les cellules dans le plateau num�ro : " << p.getId() << "\n";
		f << "Nombre de cellules : " << p.getNombreCellules() << "\n";
		int i = 0;
		for (const auto& cell : p.getCellules())
		{
			f << "Case num�ro : " << i++ << " Coordonn�es : (" << cell.get_X() << cell.get_Y() << ")\n";
		}
		return f;
	}