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
        virtual string getDescription() const = 0;
    };


    // Événement pour Hive
    class EvenementHive : public Evenement {
    private:
        string message;

    public:
        EvenementHive(const string& msg) : message(msg) {}

        string getDescription() const override {
            return "Hive: " + message;
        }

        string getMessage() const { return message; }
    };


    // Événement pour une partie
    class EvenementPartie : public EvenementHive {
    private:
        int idPartie;
        TypeEvenement typeEvenement;

    public:
        EvenementPartie(const string& msg, int id, TypeEvenement type)
            : EvenementHive(msg), idPartie(id), typeEvenement(type) {}

        const string typeEvenementToString(TypeEvenement type) const {
            switch (type) {
            case TypeEvenement::DEBUT_PARTIE: return "Début de la Partie";
            case TypeEvenement::REPRISE_PARTIE: return "Reprise de la Partie";
            case TypeEvenement::PAUSE_PARTIE: return "Partie en pause";
            case TypeEvenement::FIN_PARTIE: return "Fin de la Partie";
            case TypeEvenement::CHANGEMENT_JOUEUR: return "Changement de Joueur";
            case TypeEvenement::TOUR_SUIVANT: return "Tour Suivant";
            case TypeEvenement::ANNULER_COUP: return "Annulation de Coup";
            case TypeEvenement::SAUVEGARDE_PARTIE: return "Sauvegarde de la Partie";
            case TypeEvenement::PIECE_PLACEE: return "Pièce Placée";
            case TypeEvenement::ERREUR_PARTIE: return "Erreur dans la Partie";
            default: throw HiveException("Type d'événement inconnu");
            }
        };

        string getDescription() const override {
            return "Partie " + to_string(idPartie) + " : " + typeEvenementToString(typeEvenement) + " - " + getMessage();
        }

        int getIdPartie() const { return idPartie; }
        TypeEvenement getTypeEvenement() const { return typeEvenement; }
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