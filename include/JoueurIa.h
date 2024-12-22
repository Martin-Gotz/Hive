#pragma once
#include "Coup.h"
#include <random>
#include "Plateau.h"

namespace JeuHive {
	class JoueurIa {
	private:
		Joueur* joueur;
		Plateau* plateau;

	public:
		JoueurIa(Joueur* joueur) : joueur(joueur), plateau(nullptr) {};

		virtual Coup* choisirCoup() = 0;
		virtual ~JoueurIa() = default;

		Joueur* getJoueur() const {
			return joueur;
		}

		void setPlateau(Plateau* p) {
			plateau = p;
		}

		Plateau* getPlateau() const {
			return plateau;
		}
	};

	class JoueurIaAleatoire : public JoueurIa {
	public:
		JoueurIaAleatoire(Joueur* joueur) : JoueurIa(joueur) {}

		Coup* choisirCoup() override {
			if (getPlateau()) {
				const vector<Coup*> coupsPossibles = getPlateau()->totalCoupsPossibles(3, getJoueur());

				if (coupsPossibles.empty()) {
					throw HiveException("Aucun coup possible pour l'IA !");
				}

				// Choisir un coup aléatoire parmi les coups possibles
				random_device rd;
				mt19937 gen(rd());
				uniform_int_distribution<> distrib(0, coupsPossibles.size() - 1);
				int indexAleatoire = distrib(gen);
				Coup* coupChoisi = coupsPossibles[indexAleatoire];

				return coupChoisi;
			}
			else {
				throw HiveException("Pas de plateau");
			}
		}
	};
}