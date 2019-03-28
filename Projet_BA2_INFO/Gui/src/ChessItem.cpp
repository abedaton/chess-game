#include "ChessItem.hpp"

ChessItem::ChessItem(std::string pieceType,std::string pool_name,std::string suffix, int size, QGraphicsItem *parent) : QGraphicsPixmapItem(parent), _size(size), _suffix(suffix){
    setPicture(pieceType,pool_name);
}


std::string ChessItem::get_common_path(){return "./Gui/img";}

void ChessItem::setPicture(std::string pieceType,std::string pool){
	
	std::string pic_name;
	
	std::stringstream ss;
	ss<<this->get_common_path();
	if (pool != "") {ss<<"/"<<pool<<"/";}
	ss<<pieceType<<_suffix<<".png";
	pic_name = ss.str(); // ! pas d'utilisation de ss.str() directement (-> obligé de passer par variable) sinon peut generer problèmes!
	const QString qstr = QString::fromStdString(pic_name);
	
	QPixmap pic(qstr);
    
    pic = pic.scaled(_size,_size);
    setPixmap(pic);

}
/*
void ChessItem::setBox(PlateauBox *box){
    _currentBox = box;
}
*/
