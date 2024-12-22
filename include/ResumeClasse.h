#pragma once
#include <string>
#include <vector>

using namespace std;

namespace JeuHive {
    struct ResumePiece {
        string nom;
        string couleur;
        string symbole;
        string symboleCouleur;
    };

    struct ResumeCase {
        int q;
        int r;
        vector<ResumePiece> pieces;
    };

    struct ResumePlateau {
        vector<ResumeCase> cases;
    };

    struct ResumeMain {
        vector<ResumePiece> pieces;
        size_t nombre_pieces_restantes;
        string estVide;
    };

    struct ResumeJoueur {
        string nom;
        string type;
        string couleur;
        ResumeMain main;
    };

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
}