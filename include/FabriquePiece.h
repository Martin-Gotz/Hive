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
		// Enregistrement d'un créateur de pièce avec une quantité
		void enregistrerPiece(const string& nom, function<Piece* (Couleur)> createur, int quantite) {
			createurs[nom] = { createur, quantite };
		}

		// Création de toutes les pièces enregistrées avec leur couleur et quantité
		vector<Piece*> creerPieces(Couleur couleur) const {
			vector<Piece*> pieces;
			for (const auto& createur : createurs) {
				// Créer la quantité de pièces spécifiée pour chaque type
				for (int i = 0; i < createur.second.second; ++i) {
					pieces.push_back(createur.second.first(couleur));  // Appel du créateur avec la couleur
				}
			}
			return pieces;
		}
	};

	FabriquePiece initialiserFabriquePiece();
}