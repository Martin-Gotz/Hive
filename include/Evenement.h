#pragma once

#include <string>
#include <vector>
#include "Enums.h"
#include "./Exceptions.h"

using namespace std;


// Classe de base pour les �v�nements
namespace JeuHive {

    class Evenement {
    public:
        virtual ~Evenement() = default;

        // M�thode virtuelle pure pour r�cup�rer une description de l'�v�nement
        virtual TypeEvenement getType() const { return TypeEvenement::AUCUN_TYPE; }
        virtual string getDescription() const = 0;
    };


    // �v�nement pour Hive
    class EvenementHive : public Evenement {
    private:
        string message;
    public:
        EvenementHive() {}
        EvenementHive(const string& msg) : message(msg) {}

        string getDescription() const override {
            return message;
        }
    };


    // �v�nement pour une partie
    class EvenementPartie : public EvenementHive {
    private:
        int idPartie;
        TypeEvenement type;

    public:
        EvenementPartie(int id, TypeEvenement type)
            : idPartie(id), type(type) {}
        EvenementPartie(const string& msg, int id, TypeEvenement type)
            : EvenementHive(msg), idPartie(id), type(type) {}

        int getIdPartie() const { return idPartie; }
        TypeEvenement getType() const { return type; }
    };





    // Interface Observer
    class Observer {
    public:
        virtual ~Observer() = default;

        // M�thode g�n�rique pour notifier un observateur d'un �v�nement
        virtual void reagir(const Evenement& evenement) = 0;
    };

    class Observable {
    protected:
        // Liste des observateurs
        vector<Observer*> observers;

    public:
        virtual ~Observable() = default;

        void ajouterObserver(Observer* observer);
        void retirerObserver(Observer* observer);
        void notifierObservers(const Evenement& evenement);
    };
}