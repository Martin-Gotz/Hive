#pragma once
#include <string>
#include <vector>

using namespace std;

// Structure pour afficher une coordonn�e (check)

// faire case � la place
struct ResumeCoordonnee {
    string q;
    string r;
};

// Structure pour afficher une pi�ce (check)
// faire une concat�nation 

struct ResumePiece {
    string Couleur;
    string symbole;
};

// Structure pour afficher une main (check)

struct ResumeMain {
    vector<ResumePiece> pieces;
    int nombre_pieces_restantes;
    string estVide;
};


// Structure pour afficher un joueur 

struct ResumeJoueur {
    string nom;
    string type;
    string couleur;
    ResumeMain main;
};

// Structure pour r�sumer une partie
struct ResumePartie {
    int id;
    ResumeJoueur joueur1;
    ResumeJoueur joueur2;
    string etatPartie;
};

struct ResumePlateau {

};

// Structure pour l'�tat global de Hive
struct EtatHive {
    vector<ResumePartie> parties;
    int idPartieEnCours = -1;
};

