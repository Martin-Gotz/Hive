#pragma once

using namespace std;

namespace JeuHive {
	enum TypeJoueur {
		HUMAIN,
		IA
	};

	enum Couleur {
		BLANC,
		NOIR
	};

	enum Action {
		PLACEMENT,
		DEPLACEMENT
	};

	enum EtatPartie {
		NON_COMMENCEE,
		EN_PAUSE,
		EN_COURS,
		TERMINEE
	};


	enum class TypeEvenement {
		DEBUT_PARTIE,
		REPRISE_PARTIE,
		PAUSE_PARTIE,
		FIN_PARTIE,
		CHANGEMENT_JOUEUR,
		TOUR_SUIVANT,
		ANNULER_COUP,
		SAUVEGARDE_PARTIE,
		PIECE_PLACEE,
		ERREUR,
		AUCUN_TYPE
	}; 
}
