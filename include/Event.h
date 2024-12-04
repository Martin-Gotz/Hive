#pragma once

#include <string>
#include <vector>

using namespace std;

// Classe de base pour les événements
class Evenement {
public:
    virtual ~Evenement() = default;

    // Méthode virtuelle pure pour récupérer une description de l'événement
    virtual string getDescription() const = 0;
};


// Événement pour Hive
class EvenementHive : public Evenement {
private:
    string message; // Exemple : "Nouvelle partie ajoutée"

public:
    EvenementHive(const string& msg) : message(msg) {}

    string getDescription() const override {
        return "Hive: " + message;
    }

    string getMessage() const { return message; }
};


// Événement pour une partie
class EvenementPartie : public Evenement {
private:
    int idPartie;
    string typeEvenement; // Exemple : "Début", "Fin", "Coup joué"

public:
    EvenementPartie(int id, const string& type)
        : idPartie(id), typeEvenement(type) {}

    string getDescription() const override {
        return "Partie ID " + to_string(idPartie) + ": " + typeEvenement;
    }

    int getIdPartie() const { return idPartie; }
    string getTypeEvenement() const { return typeEvenement; }
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
