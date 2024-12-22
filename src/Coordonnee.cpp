#include "../include/Coordonnee.h"

using namespace JeuHive;
using namespace std;


// je décommente cette méthode car j'en ai besoin
vector<Coordonnee> Coordonnee::getVoisins() const
{
	vector<Coordonnee> Voisins;
	vector<pair<int, int>> directions = {
	{ 1, 0 }, { 1, -1 }, { 0, -1 },
	{ -1, 0 }, { -1, 1 }, { 0, 1 }
	};
	for (auto dir : directions)
	{
		Voisins.emplace_back(q + dir.first, r + dir.second);
	}
	return Voisins;
}


vector<Coordonnee> JeuHive::getDirections() {
	return vector<Coordonnee>({ Coordonnee(1, 0), Coordonnee(1, -1), Coordonnee(0, -1),
								Coordonnee(-1, 0), Coordonnee(-1, 1), Coordonnee(0, 1) });
}



/*
void Coordonnee::afficherVoisins() const
{
	for (const auto& coord : getVoisins()) {
		//cout << coord << " ";
	}
	cout << endl;
}
*/


ostream& JeuHive::operator<<(ostream& f, const Coordonnee& c)
{
	f << "X : " << c.get_q() << ", Y : " << c.get_r();
	return f;
}


Coordonnee Coordonnee::operator+(const Coordonnee& c) const
{
	return Coordonnee(q + c.q, r + c.r);
}

void Coordonnee::afficher(ostream& f) const {
	f << "q : " << q << " r : " << r << "\n";
}

