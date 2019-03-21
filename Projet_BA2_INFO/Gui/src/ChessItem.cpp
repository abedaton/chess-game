#include "ChessItem.hpp"

ChessItem::ChessItem(std::string pieceType, QGraphicsItem *parent) : QGraphicsPixmapItem(parent){
    setPicture(pieceType);
}

void ChessItem::setPicture(std::string pieceType){
    if(pieceType == "pionB"){
        QPixmap pic("./img/pionB.png");
        pic = pic.scaled(65,65);
        setPixmap(pic);
    }
    else if(pieceType == "pionW"){
        QPixmap pic("./img/fog.png");
        pic = pic.scaled(65,65);
        setPixmap(pic);
    }



}
/*
void ChessItem::setBox(PlateauBox *box){
    _currentBox = box;
}
*/
