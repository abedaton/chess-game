#include "ChessItem.hpp"

ChessItem::ChessItem(std::string pieceType, QGraphicsItem *parent) : QGraphicsPixmapItem(parent){
    setPicture(pieceType);
}

std::string ChessItem::get_common_path(){return "./Gui/img";}

void ChessItem::setPicture(std::string pieceType,std::string pool){
	QPixmap pic;
	std::string pic_name;
	
	std::stringstream ss;
	ss<<this->get_common_path();
	if (pool != "") {ss<<"/"<<pool<<"/";}
	ss<<pieceType<<".png"; // plustard rajouter W ou B selon couleur de piece en paramètre de la même facon
	pic_name = ss.str(); // ! pas d'utilisation de ss.str() directement (-> obligé de passer par variable) sinon peut generer problèmes!
	
	QPixmap pic(pic_name);
    
    pic = pic.scaled(65,65);
    setPixmap(pic);

}
/*
void ChessItem::setBox(PlateauBox *box){
    _currentBox = box;
}
*/
