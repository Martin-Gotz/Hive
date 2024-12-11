#pragma once
#ifndef COORDONNE_H
#define COORDONNE_H

#include "ResumeClasse.h"
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <ostream>
#include <iostream>

namespace JeuHive {
	using namespace std;

	class Coordonnee
	{
	private:
		// Si on garde l'interprétation de q et r comme coordonnées horizontale et verticale alors on perd une 
		// propriété importante: le fait que les voisins soit obtenus en additionnant la coo avec avec les constants
		// { 1, 0 }, { 1, -1 }, { 0, -1 }, { -1, 0 }, { -1, 1 }, { 0, 1 }, ce qui serait embêtant.
		// sachant les les cases pourront être empilées de bas en haut, on peut dire que r représente la coordonnée
		// verticale. Pour q, ce sera la direction un peu en haut à droite
		int q; //en haut à droite
		int r; //en haut
	public:
		int get_q() const { return q; }
		int get_r() const { return r; }
		Coordonnee(int coord_x = 0, int coord_y = 0) : q(coord_x), r(coord_y) {}

		vector<Coordonnee> getVoisins() const;

		/*void afficherVoisins() const;*/
		bool operator==(const Coordonnee& c) const { return q == c.q && r == c.r; }
		bool operator<(const Coordonnee& c) const { return (q < c.q) || (q == c.q && r < c.r); }	//inutile je crois
		Coordonnee operator+(const Coordonnee& c) const;

		// Methode utilitaire pour afficher l'etat de la partie
		void afficher(ostream& f) const;
		ResumeCoordonnee resumer() const;
	};

	ostream& operator<<(ostream& f, const Coordonnee& c);

	vector<Coordonnee> getDirections();

}

namespace std {
	//Hash pour permettre la lecture des coordonnées (notamment pour le map)
	template <>
	struct hash<JeuHive::Coordonnee> {
		size_t operator()(const JeuHive::Coordonnee& coord) const {
			return hash<int>()(coord.get_q()) ^ (hash<int>()(coord.get_r()) << 1);
		}
	};
}
#endif 
