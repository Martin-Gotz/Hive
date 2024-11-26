#pragma once
#include <iostream>
#include <vector>
#include "Coordonnee.h"

using namespace std;
namespace Hive {

	class Plateau
	{
	private:
		int ID;
		int nombre_cellules;
		vector<Coordonnee> Cellules;
	public:
		vector<Coordonnee> getCellules() const;
		Plateau() : nombre_cellules(0) {};
		friend ostream& operator<<(ostream& f, Plateau& p);
		int getId() const { return ID; }
		int getNombreCellules() const { return nombre_cellules; }
	};
	ostream& operator<<(ostream& f, const Plateau& p);

	class Ensemble_Plateaux
	{
	private:
		vector<Plateau> plateau;
		int nombre;
	public:
		Ensemble_Plateaux();
		~Ensemble_Plateaux();
		Plateau getPlateau(int ID);
		int getNombrePlateau() const;
	};
}

