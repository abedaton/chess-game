#ifndef CHESSITEM_H
#define CHESSITEM_H

#include <QGraphicsPixmapItem>
#include <iostream>
#include <sstream>
//#include "PlateauBox.h"

class ChessItem : public QGraphicsPixmapItem{

public:
    ChessItem(std::string pieceType, QGraphicsItem* parent = nullptr);
    //void setBox(PlateauBox* box);
    //PlateauBox* getBox();

    void setPicture(std::string pieceType,std::string);
    std::string get_common_path();
private:
    //PlateauBox* _currentBox;

};

#endif // CHESSITEM_H
