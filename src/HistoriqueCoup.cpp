#include "../include/HistoriqueCoup.h"
using namespace Hive;

void HistoriqueCoup::ajouterCoup(Coup& c)
{
	listeCoups.push_back(&c);
}

void HistoriqueCoup::annulerDernierCoup()
{
	if (!listeCoups.empty()) {
		listeCoups.pop_back();
	}
}