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
		int IndiceCourant; // à quoi correspond ?
		//bool estVide; de même?
		//int NombreCoups; // sert à rien?
	public:
		bool getEstVide() const { return listeCoups.empty(); }
		size_t getNombreCoups() const { return listeCoups.size(); }
		HistoriqueCoup() : IndiceCourant(0) {}
		void ajouterCoup(Coup& c);
		vector<Coup*> getlisteCoups() const { return listeCoups; }
		void annulerDernierCoup();
	};
}
