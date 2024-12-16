#include "../include/HistoriqueCoup.h"
using namespace JeuHive;

void HistoriqueCoup::ajouterCoup(const Coup& c)
{
	listeCoups.push_back(c.clone());
}

void HistoriqueCoup::annulerDernierCoup()
{
	if (!listeCoups.empty()) {
		listeCoups.pop_back();
	}
}