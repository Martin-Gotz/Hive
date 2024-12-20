#pragma once
#ifndef NOUVELLEPARTIE_H
#define NOUVELLEPARTIE_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

class NouvellePartie : public QDialog {
    Q_OBJECT

public:
    explicit NouvellePartie(QWidget* parent = nullptr);

    QString getNomJoueur1() const;
    QString getNomJoueur2() const;

private:
    QLineEdit* nomJoueur1Edit;
    QLineEdit* nomJoueur2Edit;
    QPushButton* okButton;
    QPushButton* cancelButton;

    void setupUI();
};

#endif // NOUVELLEPARTIE_H
