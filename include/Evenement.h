#pragma once

#include <string>
#include <vector>
#include "Enums.h"
#include "./Exceptions.h"

using namespace std;


// Classe de base pour les événements
namespace JeuHive {

    class Evenement {
    public:
        virtual ~Evenement() = default;

        // Méthode virtuelle pure pour récupérer une description de l'événement
        virtual TypeEvenement getType() const { return TypeEvenement::AUCUN_TYPE; }
        virtual string getDescription() const = 0;
    };


    // Événement pour Hive
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


    // Événement pour une partie
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

        // Méthode générique pour notifier un observateur d'un événement
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