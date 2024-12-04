#include "../include/Event.h"

// Ajouter un observateur
void Observable::ajouterObserver(Observer* observer) {
    if (find(observers.begin(), observers.end(), observer) == observers.end()) {
        observers.push_back(observer);
    }
}

// Retirer un observateur
void Observable::retirerObserver(Observer* observer) {
    observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
}

// Notifier tous les observateurs d'un événement
void Observable::notifierObservers(const Evenement& evenement) {
    for (Observer* observer : observers) {
        if (observer) {
            observer->reagir(evenement);
        }
    }
}