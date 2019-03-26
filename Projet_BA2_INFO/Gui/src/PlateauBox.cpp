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

void PlateauBox::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    // std::cout << _pos.first() << "," << _pos.second() << std::endl;
    //setColor(Qt::red);
    //std::cout << _color.rgb() << std::endl;
    if(_piece != nullptr && (_brush != Qt::red && _brush != Qt::green)){
        std::cout << "rouge" << std::endl;
        int moves[] = {1, 2, 3};
        int cap[] = {6};


        _scene->showMoves(moves,cap);
        _scene->setPriorityBox(this);
    }

    else if(_brush.color() == Qt::red && _piece == nullptr){

        movePiece();
        //std::cout << "FINAL : " << _piece << std::endl;

    }
    else if(_brush.color() == Qt::green && _piece != nullptr){
        delete _piece;
        movePiece();

    }

    else{
        std::cout << "oupsi pas de piece" << std::endl;
    }

    char letter = 65 + std::get<1>(_pos);
    std::cout << letter << 8 - std::get<0>(_pos) << std::endl; ///CAN

}


void PlateauBox::setPiece(ChessItem *piece){
    if(piece != nullptr)
        piece->setPos(x(),y());

    //std::cout << "AVANT : " << _piece << std::endl;
    _piece = piece;
    //std::cout << "APRES : " <<_piece << std::endl;
}

void PlateauBox::resetColor(){
    setColor(_color);
}

ChessItem* PlateauBox::getPiece() const{
    return _piece;
}

void PlateauBox::movePiece(){
    setPiece(_scene->getPriorityBox()->getPiece());
    _scene->getPriorityBox()->setPiece(nullptr);
    _scene->resetAllColors();
}
