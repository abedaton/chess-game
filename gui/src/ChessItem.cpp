#include "ChessItem.h"

ChessItem::ChessItem(std::string pieceType, QGraphicsItem *parent) : QGraphicsPixmapItem(parent){
    setPicture(pieceType);
}

void ChessItem::setPicture(std::string pieceType){
    if(pieceType == "pion"){
        QPixmap test("./img/pionB.png");
        test = test.scaled(65,65);
        std::cout << test.isNull() << std::endl;

        setPixmap(test);
    }

}
/*
void ChessItem::setBox(PlateauBox *box){
    _currentBox = box;
}
*/
