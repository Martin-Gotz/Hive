#include "../include/MainPiece.h"
#include "../include/Exceptions.h"
using namespace JeuHive;
using namespace std;



void MainPiece::AjouterPiece(Piece& piece) { 
	auto it = std::find(Pieces.begin(), Pieces.end(), &piece);
	if (it != Pieces.end()) {
		throw HiveException("La piece est deja dans la main");
		//std::cout << "Pi�ce d�j� dans le deck : " << endl;
	}
	else {
		//std::cout << "Pi�ce " << piece.getName() << "ajout�e � la main" << std::endl;
		Pieces.push_back(&piece);
	}
};

void MainPiece::RetirerPiece(Piece& piece)
	{
	auto it = std::find(Pieces.begin(), Pieces.end(), &piece);
	if (it == Pieces.end()) {
		throw HiveException("La piece est deja dans la main");
		//std::cout << "Pi�ce pas pr�sente dans le deck" << endl;
	}
	else {
		//std::cout << "Pi�ce " << piece.getName() << "supprim�e de la main" << std::endl;
		// chelou mais c'est ce que j'ai trouv� sur internet
		Pieces.erase(remove(Pieces.begin(), Pieces.end(), &piece), Pieces.end());
	
	}

}

void MainPiece::afficher(ostream& f) const
{
	ResumeMain resume = resumer();
	f << "Etat de la main : " << resume.estVide << ", nombre de pi�ces dans la main : " << resume.nombre_pieces_restantes;
	int i = 0;
	for (auto c : resume.pieces)
	{
		f << "Pi�ce num�ro " << i++ << " : " << c.Couleur + c.symbole << "\n";
	}
}

ResumeMain MainPiece::resumer() const
{
	ResumeMain resume;
	switch (estVide)
	{
	case(true):
		resume.estVide = "Vide";
		break;
	case(false):
		resume.estVide = "Non-Vide";
		break;
	}
	for (auto& p : Pieces)
	{
		resume.pieces.push_back(p->resumer());
	}; 
	resume.nombre_pieces_restantes = Pieces.size();
	return resume;
}

ostream& operator<<(ostream& os, const MainPiece& partie)
{
	partie.afficher(os);
	return os;
}