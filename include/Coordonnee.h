#pragma once
#ifndef COORDONNE_H
#define COORDONNE_H

#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <ostream>
#include <iostream>

namespace Hive {
	using namespace std;

	class Coordonnee
	{
	private:
		int q; //ligne 
		int r; //colonne
	public:
		int get_q() const { return q; }
		int get_r() const { return r; }
		Coordonnee(int coord_x = 0, int coord_y = 0) : q(coord_x), r(coord_y) {}
		vector<Coordonnee> getVoisins() const;
		void afficherVoisins() const;
		bool operator==(const Coordonnee& c) { return q == c.q && r == c.r; }
		Coordonnee operator+(const Coordonnee& c);
	};

	ostream& operator<<(ostream& f, const Coordonnee& c);
}

#endif 
