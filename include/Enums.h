#pragma once

namespace Hive {
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
		EN_COURS,
		TERMINEE,
		ANNULEE
	};
}
