#pragma once
#include <iostream>
#include <vector>

using namespace std;
namespace Hive {
	//on définit dans un premier temps une seule cellule
	class Cellule
	{
	private:
		int x;
		int y;
	public :
		int get_X() const { return x; }
		int get_Y() const { return y; }
		Cellule(int coord_x, int coord_y) : x(coord_x), y(coord_y) {}
		vector<Cellule> getVoisins() const;
		void afficherVoisins() const;
	};

	class Plateau
	{
	private:
		int ID;
		int nombre_cellules;
		vector<Cellule> Cellules;
	public:
		vector<Cellule> getCellules() const;
		Plateau() :nombre_cellules(0) {};
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

