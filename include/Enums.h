#pragma once

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
		EN_PAUSE,
		EN_COURS,
		TERMINEE
	};
}
