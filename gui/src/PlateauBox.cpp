#include "PlateauBox.h"

PlateauBox::PlateauBox(int x, int y, int sideLenght = 65, QGraphicsItem *parent) : _sideLenght(sideLenght), QGraphicsRectItem(parent) {
    setRect(x, y, sideLenght, sideLenght);
    // setPen(_pen);
    _brush.setStyle(Qt::SolidPattern);
    setBrush(_brush);
}

void PlateauBox::setColor(QColor color) {
    _brush.setColor(color);
    setBrush(color);
}

void PlateauBox::setFirstColor(QColor color) {
    _color = color;
    setColor(_color);
}

void PlateauBox::setPosition(int x, int y) {
    _pos = std::pair<int, int>(x, y);
}

void PlateauBox::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    // std::cout << _pos.first() << "," << _pos.second() << std::endl;
    setColor(Qt::green);
}
