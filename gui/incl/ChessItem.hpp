#ifndef CHESSITEM_H
#define CHESSITEM_H

#include <QGraphicsPixmapItem>
#include <iostream>
//#include "PlateauBox.h"

class ChessItem : public QGraphicsPixmapItem{

public:
    ChessItem(std::string pieceType, QGraphicsItem* parent = nullptr);
    //void setBox(PlateauBox* box);
    //PlateauBox* getBox();

    void setPicture(std::string pieceType);
private:
    //PlateauBox* _currentBox;

};

#endif // CHESSITEM_H
