#include "../include/HistoriqueCoup.h"
using namespace JeuHive;

void HistoriqueCoup::ajouterCoup(Coup& c)
{
	if (estVide == true) estVide = false;
	listeCoups.push_back(&c);
	NombreCoups++;
}

void HistoriqueCoup::annulerDernierCoup()
{
	if (!listeCoups.empty()) {
		listeCoups.pop_back();
		NombreCoups--;
	}
}