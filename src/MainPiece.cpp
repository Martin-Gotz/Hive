#include "../include/MainPiece.h"
#include "../include/Exceptions.h"
using namespace JeuHive;
using namespace std;



void MainPiece::AjouterPiece(Piece& piece) { 
	auto it = std::find(Pieces.begin(), Pieces.end(), &piece);
	if (it != Pieces.end()) {
		throw HiveException("La piece est deja dans la main");
		//std::cout << "Pièce déjà dans le deck : " << endl;
	}
	else {
		//std::cout << "Pièce " << piece.getName() << "ajoutée à la main" << std::endl;
		Pieces.push_back(&piece);
	}
};

void MainPiece::RetirerPiece(Piece& piece)
	{
	auto it = std::find(Pieces.begin(), Pieces.end(), &piece);
	if (it == Pieces.end()) {
		throw HiveException("La piece est deja dans la main");
		//std::cout << "Pièce pas présente dans le deck" << endl;
	}
	else {
		//std::cout << "Pièce " << piece.getName() << "supprimée de la main" << std::endl;
		// chelou mais c'est ce que j'ai trouvé sur internet
		Pieces.erase(remove(Pieces.begin(), Pieces.end(), &piece), Pieces.end());
	
	}

}
