#pragma once
#include "Coup.h"
#include <vector>
#include <iostream>

using namespace std;
namespace Hive {
	class HistoriqueCoup
	{
	private:
		vector<Coup*> listeCoups;
		int IndiceCourant;
	public:
		void ajouterCoup(Coup& c);
		void annulerDernierCoup();
	};
}
