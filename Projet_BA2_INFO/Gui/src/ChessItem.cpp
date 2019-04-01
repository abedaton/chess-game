#ifndef CHESSITEM_CPP
#define CHESSITEM_CPP
#include "ChessItem.hpp"

ChessItem::ChessItem(std::string pieceType,std::string pool_name,std::string suffix, int size, QGraphicsItem *parent) :  _pieceType(pieceType), QGraphicsPixmapItem(parent), _size(size), _suffix(suffix){
    setPicture(pieceType,pool_name);
}


std::string ChessItem::get_common_path(){return "./Gui/img";}

void ChessItem::setPicture(std::string pieceType,std::string pool) {
	
	std::string pic_name;
	
	std::stringstream ss;
	ss<<this->get_common_path();
	if (pool != "") {ss<<"/"<<pool<<"/";}
	ss<<pieceType<<_suffix<<".png";
	pic_name = ss.str(); // ! pas d'utilisation de ss.str() directement (-> obligé de passer par variable) sinon peut generer problèmes!
	const QString qstr = QString::fromStdString(pic_name);
	
	QPixmap _pic(qstr);
    
    _pic = _pic.scaled(_size,_size);
    this->addPixmap(_pic);


}

void ChessItem::setPixmapAgain(){
	std::cout << &_pic << std::endl;
	setPixmap(_pic);
	std::cout << "wshhh" << std::endl;
}

std::string ChessItem::getPieceType(){
	return _pieceType;
}
std::string ChessItem::getColor(){
	return _suffix;
}


/*
void ChessItem::setBox(PlateauBox *box){
    _currentBox = box;
}
*/
#endif