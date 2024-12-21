#include "../include/MainPiece.h"
#include "../include/Exceptions.h"
using namespace JeuHive;
using namespace std;



void MainPiece::ajouterPiece(Piece* piece) { 
	auto it = find(pieces.begin(), pieces.end(), piece);
	if (it != pieces.end()) {
		throw HiveException("La piece est deja dans la main");
	}
	else {
		pieces.push_back(piece);
	}
};

void MainPiece::retirerPiece(Piece* piece)
	{
	auto it = find(pieces.begin(), pieces.end(), piece);
	if (it == pieces.end()) {
		throw HiveException("La piece est deja dans la main");
	}
	else {
		pieces.erase(remove(pieces.begin(), pieces.end(), piece), pieces.end());
	
	}

}



ResumeMain MainPiece::resumer() const
{
	ResumeMain resume;
	if (estVide()) {
		resume.estVide = "Vide";
	}
	else {
		resume.estVide = "Non-Vide";
	}

	for (auto& p : pieces)
	{
		resume.pieces.push_back(p->resumer());
	}; 
	resume.nombre_pieces_restantes = pieces.size();
	return resume;
}