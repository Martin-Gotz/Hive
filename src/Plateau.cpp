#include "../include/Plateau.h"

using namespace Hive;

	vector<Cellule> Plateau::getCellules() const
	{
		return Cellules;
	}

	vector<Cellule> Cellule::getVoisins() const
	{
		vector<Cellule> Voisins;
		vector<pair<int, int>> directions = {
		{ 1, 0 }, { 1, -1 }, { 0, -1 },
		{ -1, 0 }, { -1, 1 }, { 0, 1 }
		};
		for (auto dir : directions)
		{
			Voisins.emplace_back(x + dir.first, y + dir.second);
		}
		return Voisins;
	}

	ostream& operator<<(ostream& f, const Plateau& p)
	{
		f << "Les cellules dans le plateau numéro : " << p.getId() << "\n";
		f << "Nombre de cellules : " << p.getNombreCellules() << "\n";
		int i = 0;
		for (const auto& cell : p.getCellules())
		{
			f << "Case numéro : " << i++ << " Coordonnées : (" << cell.get_X() << cell.get_Y() << ")\n";
		}
		return f;
	}