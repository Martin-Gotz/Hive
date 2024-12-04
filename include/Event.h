#pragma once

#include <string>
#include <vector>

using namespace std;

// Classe de base pour les �v�nements
class Evenement {
public:
    virtual ~Evenement() = default;

    // M�thode virtuelle pure pour r�cup�rer une description de l'�v�nement
    virtual string getDescription() const = 0;
};


// �v�nement pour Hive
class EvenementHive : public Evenement {
private:
    string message; // Exemple : "Nouvelle partie ajout�e"

public:
    EvenementHive(const string& msg) : message(msg) {}

    string getDescription() const override {
        return "Hive: " + message;
    }

    string getMessage() const { return message; }
};


// �v�nement pour une partie
class EvenementPartie : public Evenement {
private:
    int idPartie;
    string typeEvenement; // Exemple : "D�but", "Fin", "Coup jou�"

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
