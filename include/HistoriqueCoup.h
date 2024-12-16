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
		int IndiceCourant;
		bool estVide;
		int NombreCoups;
	public:
		bool getEstVide() const { return estVide; }
		int getNombreCoups() const { return NombreCoups; }
		HistoriqueCoup() : IndiceCourant(0), NombreCoups(0), estVide(true) {}
		void ajouterCoup(const Coup& c);
		void annulerDernierCoup();
	};
}
