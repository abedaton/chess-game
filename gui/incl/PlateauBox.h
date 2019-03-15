#ifndef PLATEAUBOX_H
#define PLATEAUBOX_H

#include <QBrush>
#include <QGraphicsRectItem>
#include <QPen>
#include <QWidget>
#include <iostream>
#include "ChessItem.h"

class PlateauBox : public QGraphicsRectItem {
    public:
    explicit PlateauBox(int x, int y, int sideLenght, QGraphicsItem *parent = nullptr);
    void setColor(QColor color);
    void setFirstColor(QColor color);
    void setPosition(int x, int y);
    void setPiece(ChessItem* piece);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    // void resetColor(QColor color);
    private:
    int _sideLenght;
    QBrush _brush;
    QColor _color;
    QPen _pen;
    std::pair<int, int> _pos;
    ChessItem* _piece;
};

#endif // PLATEAUBOX_H
