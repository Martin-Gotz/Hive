#pragma once

#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <ostream>
#include "Partie.h"

using namespace std;

namespace Hive {
	class Hive_Game
	{
	private:
		vector<Partie> Parties;
		Partie& PartieEnCours;
	public:
		void CreerNouvellePartie();
		void ChangerPartie();
		void SupprimerPartie();
	};

	class HiveException {
	private:
		string info;
	public:
		HiveException(const string& a): info(a) {}
		string getInfo() const { return info; }
	};
}
