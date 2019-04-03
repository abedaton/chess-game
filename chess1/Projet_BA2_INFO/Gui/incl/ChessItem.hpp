#pragma once
#ifndef CHESSITEM_H
#define CHESSITEM_H

#include <QGraphicsPixmapItem>
#include <iostream>
#include <sstream>
//#include "PlateauBox.h"

class ChessItem : public QGraphicsPixmapItem{

public:
    ChessItem(std::string pieceType,std::string pool_name, std::string suffix, int size, QGraphicsItem* parent = nullptr);
    //void setBox(PlateauBox* box);
    //PlateauBox* getBox();

    void setPicture(std::string pieceType,std::string pool);
    std::string get_common_path();

    void setPixmapAgain();
    std::string getPieceType();

    std::string getColor();
private:
    //PlateauBox* _currentBox;
    QPixmap _pic;
    std::string _pieceType;
    int _size;
    std::string _suffix;

};

#endif // CHESSITEM_H
