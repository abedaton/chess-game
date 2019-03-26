#include "ChessItem.hpp"

ChessItem::ChessItem(std::string pieceType, QGraphicsItem *parent) : QGraphicsPixmapItem(parent){
    setPicture(pieceType);
}

void ChessItem::setPicture(std::string pieceType){
    if(pieceType == "pionB"){
        QPixmap pic("./Gui/img/pionB.png");
        pic = pic.scaled(65,65);
        setPixmap(pic);
    }

    else if(pieceType == "pionW"){
        QPixmap pic("./Gui/img/pionW.png");
        pic = pic.scaled(65,65);
        setPixmap(pic);
    }
    
    // FOU
    else if(pieceType == "fouB"){
        QPixmap pic("./Gui/img/fouB.png");
        pic = pic.scaled(65,65);
        setPixmap(pic);
    }

    else if(pieceType == "fouW"){
        QPixmap pic("./Gui/img/fouW.png");
        pic = pic.scaled(65,65);
        setPixmap(pic);
    }

    // TOUR
    else if(pieceType == "tourB"){
        QPixmap pic("./Gui/img/tourB.png");
        pic = pic.scaled(65,65);
        setPixmap(pic);
    }

    else if(pieceType == "tourW"){
        QPixmap pic("./Gui/img/tourW.png");
        pic = pic.scaled(65,65);
        setPixmap(pic);
    }

    // CHEVALIER
    else if(pieceType == "chevB"){
        QPixmap pic("./Gui/img/chevB.png");
        pic = pic.scaled(65,65);
        setPixmap(pic);
    }

    else if(pieceType == "chevW"){
        QPixmap pic("./Gui/img/chevW.png");
        pic = pic.scaled(65,65);
        setPixmap(pic);
    }

    // REINE
    else if(pieceType == "reineB"){
        QPixmap pic("./Gui/img/reineB.png");
        pic = pic.scaled(65,65);
        setPixmap(pic);
    }

    else if(pieceType == "reineW"){
        QPixmap pic("./Gui/img/reineW.png");
        pic = pic.scaled(65,65);
        setPixmap(pic);
    }

    //ROI

    else if(pieceType == "roiB"){
        QPixmap pic("./Gui/img/roiB.png");
        pic = pic.scaled(65,65);
        setPixmap(pic);
    }

    else if(pieceType == "roiW"){
        QPixmap pic("./Gui/img/roiW.png");
        pic = pic.scaled(65,65);
        setPixmap(pic);
    }



}
/*
void ChessItem::setBox(PlateauBox *box){
    _currentBox = box;
}
*/
