#include "PlateauBox.hpp"

PlateauBox::PlateauBox(int x, int y, int sideLenght = 65, QGraphicsItem *parent) : _sideLenght(sideLenght), QGraphicsRectItem(parent) {
    setRect(0, 0, sideLenght, sideLenght);
    setPos(x,y);
    // setPen(_pen);
    _brush.setStyle(Qt::SolidPattern);
    setBrush(_brush);
    _piece = nullptr;
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

void PlateauBox::setPiece(ChessItem *piece){
    piece->setPos(x(),y());
    _piece = piece;
}
