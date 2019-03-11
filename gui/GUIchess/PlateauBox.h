#ifndef PLATEAUBOX_H
#define PLATEAUBOX_H

#include <QWidget>
#include <QBrush>
#include <QPen>
#include <QGraphicsRectItem>
#include <iostream>

class PlateauBox : public QGraphicsRectItem{
public:
    explicit PlateauBox(int x , int y , int sideLenght, QGraphicsItem* parent = nullptr);
    void setColor(QColor color);
    void setFirstColor(QColor color);
    void setPosition(int x, int y);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    //void resetColor(QColor color);
private:
    int _sideLenght;
    QBrush _brush;
    QColor _color;
    QPen _pen;
    std::pair<int,int> _pos;
};

#endif // PLATEAUBOX_H
