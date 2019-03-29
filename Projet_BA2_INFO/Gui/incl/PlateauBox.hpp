#pragma once
#ifndef PLATEAUBOX_HPP
#define PLATEAUBOX_HPP

#include <QBrush>
#include <QGraphicsRectItem>
#include <QPen>
#include <QWidget>
#include <iostream>
#include "ChessItem.hpp"
#include "PlateauScene.hpp"

class PlateauScene;

class PlateauBox : public QGraphicsRectItem {
    public:
    explicit PlateauBox(int x, int y, int sideLenght, QGraphicsItem *parent = nullptr);
    void setColor(QColor color);
    void setFirstColor(QColor color);
    void setPosition(int x, int y);
    void setPiece(ChessItem* piece);
    ChessItem* getPiece() const;
    void resetColor();
    void movePiece();

    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    PlateauScene* _scene;
    private:
    int _sideLenght;
    QBrush _brush;
    QColor _color;
    QPen _pen;
    std::pair<int, int> _pos;
    ChessItem* _piece;
};

#endif // PLATEAUBOX_HPP
