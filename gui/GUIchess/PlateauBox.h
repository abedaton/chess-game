#ifndef PLATEAUBOX_H
#define PLATEAUBOX_H

#include <QWidget>
#include <QBrush>
#include <QPen>
#include <QGraphicsRectItem>

class PlateauBox : public QGraphicsRectItem{
public:
    explicit PlateauBox(int x , int y , int sideLenght, QGraphicsItem* parent = nullptr);
    void setColor(QColor color);
    void setFirstColor(QColor color);
    //void resetColor(QColor color);
private:
    int _sideLenght;
    QBrush _brush;
    QColor _color;
    QPen _pen;
};

#endif // PLATEAUBOX_H
