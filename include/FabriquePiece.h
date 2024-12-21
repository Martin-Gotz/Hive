#pragma once

#include "Piece.h"
#include <vector>
#include <map>
#include <functional>

namespace JeuHive {
	class FabriquePiece {
	private:
		map<string, pair<function<Piece* (Couleur)>, int>> createurs;

	public:
		// Enregistrement d'un cr�ateur de pi�ce avec une quantit�
		void enregistrerPiece(const string& nom, function<Piece* (Couleur)> createur, int quantite) {
			createurs[nom] = { createur, quantite };
		}

		// Cr�ation de toutes les pi�ces enregistr�es avec leur couleur et quantit�
		vector<Piece*> creerPieces(Couleur couleur) const {
			vector<Piece*> pieces;
			for (const auto& createur : createurs) {
				// Cr�er la quantit� de pi�ces sp�cifi�e pour chaque type
				for (int i = 0; i < createur.second.second; ++i) {
					pieces.push_back(createur.second.first(couleur));  // Appel du cr�ateur avec la couleur
				}
			}
			return pieces;
		}
	};

	FabriquePiece initialiserFabriquePiece();
}