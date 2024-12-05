#pragma once
#include <string>
#include <vector>

using namespace std;

// Structure pour r�sumer une partie
struct ResumePartie {
    int id;
    string joueur1;
    string joueur2;
    string etatPartie;
};

// Structure pour l'�tat global de Hive
struct EtatHive {
    vector<ResumePartie> parties;
    int idPartieEnCours = -1;
};