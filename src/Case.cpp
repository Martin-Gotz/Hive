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

// cette fonction est à revoir
vector<Case> Case::getNeighbors() const
{
	vector<Case> Voisins;
	vector<pair<int, int>> directions = {
	{ 1, 0 }, { 1, -1 }, { 0, -1 },
	{ -1, 0 }, { -1, 1 }, { 0, 1 }
		};
	for (auto dir : directions){
		Voisins.emplace_back(q + dir.first, r + dir.second);
	}
		return Voisins;
}
