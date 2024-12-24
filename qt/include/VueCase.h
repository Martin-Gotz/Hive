#pragma once

#include "Case.h"
#include "Enums.h"
#include <QPushButton>
#include <QPainter>
#include <QPolygonF>
#include <QPen>
#include <QBrush>
#include <cmath>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QFont>
#include <QStyleOptionGraphicsItem>

namespace JeuHive {
    class VueCase : public QObject, public QGraphicsItem {
        Q_OBJECT

    public:
        explicit VueCase(const Coordonnee& coord) : coord(coord), piece(nullptr), couleur(BLANC) {
            pen = QPen(Qt::black);
            brush = QBrush(Qt::white);
            setFlag(QGraphicsItem::ItemIsSelectable);
            setAcceptHoverEvents(true);
            updateHexagon();
        }

        // D�finir la forme de l'hexagone
        QRectF boundingRect() const override {
            return QRectF(0, 0, 50, 50);
        }

        // Dessiner l'hexagone
        void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override {
            // Changer la couleur en fonction de l'�tat (survol ou normal)
            if (isHovered) {
                brush.setColor(Qt::lightGray); // Couleur lors du survol
            }
            else {
                if (couleur == BLANC) {
                    brush.setColor(Qt::white);
                }
                else {
                    brush.setColor(Qt::black);
                }
            }

            // Dessiner l'hexagone
            painter->setRenderHint(QPainter::Antialiasing);
            painter->setPen(pen);
            painter->setBrush(brush);
            painter->drawPolygon(hexagon);

            // Si une pi�ce est pr�sente, dessiner son symbole
            if (piece) {
                painter->setPen(couleur == BLANC ? Qt::black : Qt::white);
                QFont font = painter->font();
                font.setPointSize(12);
                painter->setFont(font);
                painter->drawText(boundingRect(), Qt::AlignCenter, QString::fromStdString(piece->getSymbole()));
            }
        }

        // V�rifie si le clic est dans l'hexagone
        bool hitButton(const QPointF& pos) const {
            return hexagon.containsPoint(pos, Qt::OddEvenFill);
        }

        void updateHexagon() {
            int w = boundingRect().width();
            int h = boundingRect().height();

            QPointF center(w / 2.0, h / 2.0);
            int size = std::min(w, h) / 2.0;

            hexagon.clear();
            for (int i = 0; i < 6; ++i) {
                double angle = M_PI / 3.0 * i;
                hexagon << QPointF(center.x() + size * std::cos(angle), center.y() + size * std::sin(angle));
            }
        }

        void setPiece(const JeuHive::Piece& p) {
            piece = &p;
            setCouleur(p.getCouleur());
            update();
        }

        void setNoPiece() {
            setCouleur(BLANC);
            piece = nullptr;
            update();
        }

        void setCouleur(Couleur c) {
            couleur = c;
            update();
        }

        const Coordonnee& getCoord() const {
            return coord;
        }

        const JeuHive::Piece& getPiece() const { return *piece; }
        bool piecePresente() const { return piece != nullptr; }

    public:
        // Gestion de l'�v�nement de clic
        void mousePressEvent(QGraphicsSceneMouseEvent* event) override {
            emit caseClicked(this);
        }

        // Gestion de l'�v�nement de survol (entr�e souris)
        void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override {
            isHovered = true;
            update();
        }

        // Gestion de l'�v�nement de survol (sortie souris)
        void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override {
            isHovered = false;
            update();
        }

    signals:
        void caseClicked(VueCase* vueCase);

    private:
        const Piece* piece;
        Coordonnee coord;
        QPen pen;
        QBrush brush;
        QPolygonF hexagon;
        Couleur couleur;
        bool isHovered = false;
    };
}
