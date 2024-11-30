#include "../include/Case.h"

using namespace Hive;
using namespace std;

void Case::ajouterPiece(Piece& piece)
{
	pieces.push_back(piece);
}
void Case::retirerPiece(Piece& piece)
{
    auto it = find(pieces.begin(), pieces.end(), piece);
    if (it != pieces.end()) {
        pieces.erase(it);
    }
}

Case* getCaseByCoord(Coordonnee& c, const Plateau& p)
{
	for (auto& cases : p.getCases())
	{
		if (c == cases.getCoord())
		{
			return &cases;
		}
	}
	throw HiveException("pas de case ayant pour coordonnées celles mentionnées");
}

// cette fonction est à revoir

vector<Case> Case::getNeighbors() const
{
	vector<Case> Voisins;
	vector<Coordonnee> coordonnees;
	vector<pair<int, int>> directions = {
	{ 1, 0 }, { 1, -1 }, { 0, -1 },
	{ -1, 0 }, { -1, 1 }, { 0, 1 }
		};
	for (auto dir : directions){
		coordonnees.emplace_back(c.get_q() + dir.first, c.get_r() + dir.second );
	}
	for (auto cell : coordonnees)
	{
		
	}
	return Voisins;
}
