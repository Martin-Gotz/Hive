#pragma once
#include "Coup.h"
#include <vector>
#include <iostream>

using namespace std;
namespace JeuHive {
	class HistoriqueCoup
	{
	private:
		vector<Coup*> listeCoups;
	public:
		// Destructeur ?
		bool getEstVide() const { return listeCoups.empty(); }
		size_t getNombreCoups() const { return listeCoups.size(); }
		void ajouterCoup(const Coup& c);
		vector<Coup*> getlisteCoups() const { return listeCoups; }
		void annulerDernierCoup();
	};
}
