//#include <iostream>
//#include <utility>
//#include <sstream>
#include "PlatPosi.hpp"


PlatPosi::PlatPosi(int x,int y) : MatPosi(x,y), row_size(* (new BitypeVar<int>(false,0)) ), col_size(* (new BitypeVar<int>(false,0)) ) {this->check_if_out_plat();} //*< Constructor

PlatPosi::PlatPosi(Paire<int,int> paire) : MatPosi(paire), row_size(* (new BitypeVar<int>(false,0)) ), col_size(* (new BitypeVar<int>(false,0)) ) {this->check_if_out_plat();} //*< Constructor

PlatPosi::PlatPosi(std::string s) : MatPosi(s), row_size(* (new BitypeVar<int>(false,0)) ), col_size(* (new BitypeVar<int>(false,0)) ) {this->check_if_out_plat();} //*< Constructor

PlatPosi::PlatPosi(std::string s,BitypeVar<int> row_s,BitypeVar<int> col_s) : MatPosi(s), row_size(row_s), col_size(col_s) {this->check_if_out_plat();} //*< Constructor

PlatPosi::PlatPosi(std::string s,BitypeVar<int> row_s) : MatPosi(s), row_size(row_s), col_size(row_s) {this->check_if_out_plat();} //*< Constructor

PlatPosi::PlatPosi(int first,BitypeVar<int> second,BitypeVar<int> row_s, BitypeVar<int> col_s) : MatPosi(0,0), row_size(row_s), col_size(col_s){
	
	int col;
	int lig;
	
	if (second.get_state() == true){
		col = first;
		lig = second.get_var();
		}
	else{
		
		int taille_row = this->get_row_size();
		col = first%taille_row;
		lig = first/taille_row;
	}
	
	//MatPosi::MatPosi(col,lig);
	this->set_col(col);
	this->set_lig(lig);
			
	this->check_if_out_plat();
	

} //*< Constructor

PlatPosi::PlatPosi(int first,BitypeVar<int> second,BitypeVar<int> row_s) : PlatPosi(first,second,row_s,row_s) {} //*< Constructor

PlatPosi::PlatPosi(const MatPosi& p) : MatPosi(p), row_size(* (new BitypeVar<int>(false,0)) ), col_size(* (new BitypeVar<int>(false,0)) ) {this->check_if_out_plat();}

std::ostream& operator <<(std::ostream &s,PlatPosi &c){
	/* affchage d'un PlatPosi */
    s<<"PlatPosi("<<"col:"<<c.get_col()<<" ,lig:"<<c.get_lig()<<" ,row_size:"<<c.get_row_size()<<" ,col_size:"<<c.get_col_size()<<")";
    return s;
}

std::ostream& operator <<(std::ostream &s,PlatPosi* c){
	/* affchage d'un PlatPosi */
    s<<(*c);
    return s;
}

int PlatPosi::get_row_size() const{
	
	if (this->row_size.get_state() == false){throw MyException(&mout,"pas de taille de plateau indiquée");}
	
	return this->row_size.get_var();
}

void PlatPosi::set_row_size(BitypeVar<int> bit) {
	this->row_size = bit;
}

int PlatPosi::get_col_size() const{
	
	if (this->col_size.get_state() == false){throw MyException(&mout,"pas de taille de plateau indiquée");}
	
	return this->col_size.get_var();
}

void PlatPosi::set_col_size(BitypeVar<int> bit) {
	this->col_size = bit;
}

bool PlatPosi::is_in_plat(int col, int lig, int taille_col, int taille_lig){		
	return (col >= 0 and col < taille_col and lig >= 0 and lig < taille_lig);
}

bool PlatPosi::is_in_plat(int col, int lig, int taille){	
	return this->is_in_plat(col, lig ,taille ,taille);
}

bool PlatPosi::is_in_plat(){	
	//return ( this->to_sum_val() < this->get_row_size()*this->get_row_size() ) // trop lourd
	
	int col = this->get_col();
	int lig = this->get_lig();
	int taille_lig = this->get_row_size();
	int taille_col = this->get_col_size();
	
	return this->is_in_plat(col,lig,taille_col,taille_lig);
}

void PlatPosi::check_if_out_plat(){
	if (not this->is_in_plat()) {throw MyException(&mout,"coordonee sort du plateau");}
}

int PlatPosi::to_sum_val(){
	// ----------------------------------------------------------------------------------------------------------------------------
	
	int col = this->get_col();
	int lig = this->get_lig();
	int taille_row = this->get_row_size();
	
	return (lig*taille_row + col);
	
}



bool PlatPosi::isvalid_coord(std::string s){
	/* fonction calculant si un string s est est une coordonée matricielle valide */
	
	bool res = false;
	
	if(MatPosi::isvalid_coord(s)){
		
		MatPosi* mpos = new MatPosi(s);
		
		Paire<int,int> paire_mpos = mpos->to_pair();
		
		delete mpos;
		
		try{
			this->is_in_plat(paire_mpos.get_first(), paire_mpos.get_second(), this->get_col_size(), this->get_row_size());
			res = true;	
		}
		catch (MyException& e){res = false;} // pas vraiment necessaire en theorie
		
	}
	
	return res;
}

void PlatPosi::invert_y_axis(){
		
	int new_lig = this->get_col_size() - this->get_lig() - 1; //la taille d'une colonne est le nombre de lignes, le -1 car commence a 0 (val_max = len(vect) -1 )
	this->set_lig(new_lig);
	
}
