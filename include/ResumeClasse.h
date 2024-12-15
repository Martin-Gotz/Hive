#pragma once
#include <string>
#include <vector>

using namespace std;

// Structure pour afficher une coordonnée (check)

// faire case à la place
struct ResumeCoordonnee {
    string q;
    string r;
};

// Structure pour afficher une pièce (check)
// faire une concaténation 

struct ResumePiece {
    string nom;
    string couleur;
    string symbole;
};

// Structure pour afficher une main (check)

struct ResumeMain {
    vector<ResumePiece> pieces;
    int nombre_pieces_restantes;
    string estVide;
};


// Structure pour afficher un joueur (check)

struct ResumeJoueur {
    string nom;
    string type;
    string couleur;
    ResumeMain main;
};

// Structure pour résumer une partie (check)
struct ResumePartie {
    int id;
    ResumeJoueur joueur1;
    ResumeJoueur joueur2;
    string etatPartie;
};

// Structure pour l'état global de Hive
struct EtatHive {
    vector<ResumePartie> parties;
    int idPartieEnCours = -1;
};

