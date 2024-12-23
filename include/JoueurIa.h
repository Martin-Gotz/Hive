#pragma once
#include "Coup.h"
#include <random>
#include "Plateau.h"

namespace JeuHive {
    class JoueurIa {
    private:
        Joueur* joueur;
        Plateau* plateau;
        int tour;
    public:
        JoueurIa(Joueur* joueur) : joueur(joueur), plateau(nullptr) { tour = 1; }

        virtual Coup* choisirCoup() = 0;
        virtual ~JoueurIa() = default;

        void setJoueur(Joueur* j)
        {
            joueur = j;
        }

        int getTour() const {
            return tour;
        }

        Joueur* getJoueur() const {
            return joueur;
        }

        void setPlateau(Plateau* p) {
            plateau = p;
        }

        Plateau* getPlateau() const {
            return plateau;
        }

        void setTour(int t) {
            tour = t;
        }

        void actualiser(Joueur* j, Plateau *p, int t)
        {
            setJoueur(j);
            setPlateau(p);
            setTour(t);
        }
    };

    class JoueurIaMoyen : public JoueurIa {
    private:

    public:
        JoueurIaMoyen(Joueur* joueur, Plateau* plateau) : JoueurIa(joueur) {
            setPlateau(plateau);
        }

        Coup* choisirCoup() override {
            if (!getPlateau()) {
                throw HiveException("Pas de plateau");
            }

            const vector<Coup*> coupsPossibles = getPlateau()->totalCoupsPossibles(getTour(), *getJoueur());

            if (coupsPossibles.empty()) {
                throw HiveException("Aucun coup possible pour l'IA !");
            }

            // Choisir un coup aléatoire parmi les coups possibles
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> distrib(0, coupsPossibles.size() - 1);

            int indexAleatoire = distrib(gen);
            if (indexAleatoire < 0 || indexAleatoire >= coupsPossibles.size()) {
                throw HiveException("Index aléatoire hors limites");
            }

            Coup* coupChoisi = coupsPossibles[indexAleatoire];

            return coupChoisi;
        }
    };

    class JoueurIaFacile : public JoueurIa {
    private:
   
    public:
        JoueurIaFacile(Joueur* joueur, Plateau* plateau) : JoueurIa(joueur) {
            setPlateau(plateau);
        }

        Coup* choisirCoup() override {
            if (!getPlateau()) {
                throw HiveException("Pas de plateau");
            }

            const vector<Coup*> coupsPossibles = getPlateau()->totalCoupsPossibles(getTour(), *getJoueur());

            if (coupsPossibles.empty()) {
                throw HiveException("Aucun coup possible pour l'IA !");
            }

            // Choisir un coup aléatoire parmi les coups possibles
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> distrib(0, coupsPossibles.size() - 1);

            int indexAleatoire = distrib(gen);
            if (indexAleatoire < 0 || indexAleatoire >= coupsPossibles.size()) {
                throw HiveException("Index aléatoire hors limites");
            }

            Coup* coupChoisi = coupsPossibles[indexAleatoire];

            return coupChoisi;
        }
    };

    class JoueurIaDifficile : public JoueurIa {
    private:
    
    public:
        JoueurIaDifficile(Joueur* joueur, Plateau* plateau) : JoueurIa(joueur) {
            setPlateau(plateau);
        }

        Coup* choisirCoup() override {
            if (!getPlateau()) {
                throw HiveException("Pas de plateau");
            }

            const vector<Coup*> coupsPossibles = getPlateau()->totalCoupsPossibles(getTour(), *getJoueur());

            if (coupsPossibles.empty()) {
                throw HiveException("Aucun coup possible pour l'IA !");
            }

            // Choisir un coup aléatoire parmi les coups possibles
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> distrib(0, coupsPossibles.size() - 1);

            int indexAleatoire = distrib(gen);
            if (indexAleatoire < 0 || indexAleatoire >= coupsPossibles.size()) {
                throw HiveException("Index aléatoire hors limites");
            }

            Coup* coupChoisi = coupsPossibles[indexAleatoire];

            return coupChoisi;
        }

    };
}
