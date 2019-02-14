
#include "Pieces.hpp"

extern MyOstream mout;

// -------------------------TOUR----------------------------------------------

Tour::Tour() : Chesspiece() {

	std::vector<AdvTuple>* li = new std::vector<AdvTuple>();
	li->push_back(AdvTuple(0,1,"translation"));
	li->push_back(AdvTuple(1,0,"translation"));
	this->set_liste_depl(li);
		
	this->decoders_update();
}

std::string Tour::get_name() {return "T";}

// -------------------------FOUS----------------------------------------------

Fous::Fous() : Chesspiece() {
	
	std::vector<AdvTuple>* li = new std::vector<AdvTuple>();
	li->push_back(AdvTuple(1,1,"translation"));
	li->push_back(AdvTuple(-1,1,"translation"));
	this->set_liste_depl(li);
		
	this->decoders_update();
}

std::string Fous::get_name() {return "Fou";}

// -------------------------PION----------------------------------------------

Pion::Pion(std::string dir) : Chesspiece(), alternative(nullptr), direction(dir) {
	BitypeVar<int>* alt_first;
	BitypeVar<int>* alt_second;
	BitypeVar<int>* sec_first;
	BitypeVar<int>* sec_second;

	if (this->direction == "up"){
		alt_first = new BitypeVar<int>(true,0);
		alt_second = new BitypeVar<int>(true,1);
		
		sec_first = new BitypeVar<int>(true,0);
		sec_second = new BitypeVar<int>(true,2);
	}
		
	else if (this->direction == "down"){
		alt_first = new BitypeVar<int>(true,-1);
		alt_second = new BitypeVar<int>(true,0);
		
		sec_first = new BitypeVar<int>(true,-2);
		sec_second = new BitypeVar<int>(true,0);
	}
		
	else {throw MyException(&mout, "direction Pion inconnue! dans constructeur");}
	
	std::pair<int,std::string> a = std::make_pair(1,"");
	BitypeVar<std::pair<int,std::string>>* alt_third = new BitypeVar<std::pair<int,std::string>>(true,a);
	AdvTuple* alt = new AdvTuple(0,1,"translation",alt_first,alt_second,alt_third);
	
	std::pair<int,std::string> b = std::make_pair(1,"");
	BitypeVar<std::pair<int,std::string>>* sec_third = new BitypeVar<std::pair<int,std::string>>(true,b);
	AdvTuple* sec = new AdvTuple(0,1,"translation",sec_first,sec_second,sec_third,true);
	
	std::vector<AdvTuple>* li = new std::vector<AdvTuple>();
	li->push_back(*(alt));
	li->push_back(*(sec));
	this->set_liste_depl(li);
	
	std::vector<AdvTuple>* alt_li = new std::vector<AdvTuple>();
	alt_li->push_back(*(alt));
	this->alternative = alt_li;
	
	this->decoders_update();
}
	
Pion::Pion() : Pion("up") {}

Pion::Pion(const Pion& p) : Chesspiece(p), alternative(p.alternative), direction(p.direction) {}

void Pion::updt(){
	
	this->set_liste_depl(this->get_alternative());
	this->decoders_update();
	mout<<"Update Pion !"<<std::endl;
	
}

std::string Pion::get_name() {return "P";}

std::vector<AdvTuple>* Pion::get_alternative(){
	return this->alternative;
}

void Pion::make_capt_list(){
	BitypeVar<int>* one_first;
	BitypeVar<int>* one_second;
	BitypeVar<int>* two_first;
	BitypeVar<int>* two_second;
	
	if (this->direction == "up"){
		one_first = new BitypeVar<int>(true,0);
		one_second = new BitypeVar<int>(true,1);
		
		two_first = new BitypeVar<int>(true,0);
		two_second = new BitypeVar<int>(true,1);
	}
	
	else if (this->direction == "down"){
		one_first = new BitypeVar<int>(true,-1);
		one_second = new BitypeVar<int>(true,0);
		
		two_first = new BitypeVar<int>(true,-1);
		two_second = new BitypeVar<int>(true,0);
	}
	
	else {throw MyException(&mout, "direction Pion inconnue! dans make_capt_list");}
	
	std::pair<int,std::string> a = std::make_pair(1,"");
	BitypeVar<std::pair<int,std::string>>* one_third = new BitypeVar<std::pair<int,std::string>>(true,a);
	AdvTuple* one = new AdvTuple(1,1,"translation",one_first,one_second,one_third);
	
	std::pair<int,std::string> b = std::make_pair(1,"");
	BitypeVar<std::pair<int,std::string>>* two_third = new BitypeVar<std::pair<int,std::string>>(true,b);
	AdvTuple* two = new AdvTuple(-1,1,"translation",two_first,two_second,two_third,true);
	
	std::vector<AdvTuple>* capt_li = new std::vector<AdvTuple>();
	capt_li->push_back(*(one));
	capt_li->push_back(*(two));
	this->set_liste_capt(capt_li);
	
}

// -------------------------DAME----------------------------------------------

Dame::Dame() : Chesspiece() {
	
	std::vector<AdvTuple>* li = new std::vector<AdvTuple>();
	li->push_back(AdvTuple(1,1,"translation"));
	li->push_back(AdvTuple(-1,1,"translation"));
	li->push_back(AdvTuple(0,1,"translation"));
	li->push_back(AdvTuple(1,0,"translation"));
	this->set_liste_depl(li);
		
	this->decoders_update();
}

std::string Dame::get_name() {return "D";}

// -------------------------ROI----------------------------------------------

Roi::Roi() : Chesspiece() {
	
	BitypeVar<int>* one_first = new BitypeVar<int>(true,-1);
	BitypeVar<int>* one_second = new BitypeVar<int>(true,1);
	std::pair<int,std::string> a = std::make_pair(1,"");
	BitypeVar<std::pair<int,std::string>>* one_third = new BitypeVar<std::pair<int,std::string>>(true,a);
	AdvTuple* one = new AdvTuple(1,1,"translation",one_first,one_second,one_third);
	
	BitypeVar<int>* two_first = new BitypeVar<int>(true,-1);
	BitypeVar<int>* two_second = new BitypeVar<int>(true,1);
	std::pair<int,std::string> b = std::make_pair(1,"");
	BitypeVar<std::pair<int,std::string>>* two_third = new BitypeVar<std::pair<int,std::string>>(true,b);
	AdvTuple* two = new AdvTuple(-1,1,"translation",two_first,two_second,two_third);
	
	BitypeVar<int>* three_first = new BitypeVar<int>(true,-1);
	BitypeVar<int>* three_second = new BitypeVar<int>(true,1);
	std::pair<int,std::string> c = std::make_pair(1,"");
	BitypeVar<std::pair<int,std::string>>* three_third = new BitypeVar<std::pair<int,std::string>>(true,c);
	AdvTuple* three = new AdvTuple(0,1,"translation",three_first,three_second,three_third);
	
	BitypeVar<int>* four_first = new BitypeVar<int>(true,-1);
	BitypeVar<int>* four_second = new BitypeVar<int>(true,1);
	std::pair<int,std::string> d = std::make_pair(1,"");
	BitypeVar<std::pair<int,std::string>>* four_third = new BitypeVar<std::pair<int,std::string>>(true,d);
	AdvTuple* four = new AdvTuple(1,0,"translation",four_first,four_second,four_third);
	
	std::vector<AdvTuple>* li = new std::vector<AdvTuple>();
	li->push_back(*(one));
	li->push_back(*(two));
	li->push_back(*(three));
	li->push_back(*(four));
	this->set_liste_depl(li);
		
	this->decoders_update();
}

std::string Roi::get_name() {return "R";}

// -------------------------CHEVALIER----------------------------------------------

Chevalier::Chevalier() : Chesspiece() {
	
	BitypeVar<int>* one_first = new BitypeVar<int>(true,-1);
	BitypeVar<int>* one_second = new BitypeVar<int>(true,1);
	std::pair<int,std::string> a = std::make_pair(1,"");
	BitypeVar<std::pair<int,std::string>>* one_third = new BitypeVar<std::pair<int,std::string>>(true,a);
	AdvTuple* one = new AdvTuple(1,2,"saut",one_first,one_second,one_third);
	
	BitypeVar<int>* two_first = new BitypeVar<int>(true,-1);
	BitypeVar<int>* two_second = new BitypeVar<int>(true,1);
	std::pair<int,std::string> b = std::make_pair(1,"");
	BitypeVar<std::pair<int,std::string>>* two_third = new BitypeVar<std::pair<int,std::string>>(true,b);
	AdvTuple* two = new AdvTuple(2,1,"saut",two_first,two_second,two_third);
	
	BitypeVar<int>* three_first = new BitypeVar<int>(true,-1);
	BitypeVar<int>* three_second = new BitypeVar<int>(true,1);
	std::pair<int,std::string> c = std::make_pair(1,"");
	BitypeVar<std::pair<int,std::string>>* three_third = new BitypeVar<std::pair<int,std::string>>(true,c);
	AdvTuple* three = new AdvTuple(-2,1,"saut",three_first,three_second,three_third);
	
	BitypeVar<int>* four_first = new BitypeVar<int>(true,-1);
	BitypeVar<int>* four_second = new BitypeVar<int>(true,1);
	std::pair<int,std::string> d = std::make_pair(1,"");
	BitypeVar<std::pair<int,std::string>>* four_third = new BitypeVar<std::pair<int,std::string>>(true,d);
	AdvTuple* four = new AdvTuple(-1,2,"saut",four_first,four_second,four_third);
	
	std::vector<AdvTuple>* li = new std::vector<AdvTuple>();
	li->push_back(*(one));
	li->push_back(*(two));
	li->push_back(*(three));
	li->push_back(*(four));
	this->set_liste_depl(li);
		
	this->decoders_update();
}

std::string Chevalier::get_name() {return "Che";}

// -------------------------FONCTIONNAIRE----------------------------------------------

Fonctionnaire::Fonctionnaire() : Chesspiece() {
	
	BitypeVar<int>* one_first = new BitypeVar<int>(true,5);
	BitypeVar<int>* one_second = new BitypeVar<int>(false,0);
	std::pair<int,std::string> a = std::make_pair(0,"prime");
	BitypeVar<std::pair<int,std::string>>* one_third = new BitypeVar<std::pair<int,std::string>>(true,a);
	AdvTuple* one = new AdvTuple(0,1,"saut",one_first,one_second,one_third);
	
	BitypeVar<int>* two_first = new BitypeVar<int>(true,5);
	BitypeVar<int>* two_second = new BitypeVar<int>(false,0);
	std::pair<int,std::string> b = std::make_pair(0,"prime");
	BitypeVar<std::pair<int,std::string>>* two_third = new BitypeVar<std::pair<int,std::string>>(true,b);
	AdvTuple* two = new AdvTuple(1,0,"saut",two_first,two_second,two_third);
	
	std::vector<AdvTuple>* li = new std::vector<AdvTuple>();
	li->push_back(*(one));
	li->push_back(*(two));
	this->set_liste_depl(li);
		
	this->decoders_update();
}

std::string Fonctionnaire::get_name() {return "Fon";}

// -------------------------GARDE----------------------------------------------

Garde::Garde() : Chesspiece() {
	
	BitypeVar<int>* one_first = new BitypeVar<int>(true,-1);
	BitypeVar<int>* one_second = new BitypeVar<int>(true,1);
	std::pair<int,std::string> a = std::make_pair(1,"");
	BitypeVar<std::pair<int,std::string>>* one_third = new BitypeVar<std::pair<int,std::string>>(true,a);
	AdvTuple* one = new AdvTuple(1,1,"translation",one_first,one_second,one_third);
	
	BitypeVar<int>* two_first = new BitypeVar<int>(true,-1);
	BitypeVar<int>* two_second = new BitypeVar<int>(true,1);
	std::pair<int,std::string> b = std::make_pair(1,"");
	BitypeVar<std::pair<int,std::string>>* two_third = new BitypeVar<std::pair<int,std::string>>(true,b);
	AdvTuple* two = new AdvTuple(-1,1,"translation",two_first,two_second,two_third);
	
	BitypeVar<int>* three_first = new BitypeVar<int>(true,-1);
	BitypeVar<int>* three_second = new BitypeVar<int>(true,1);
	std::pair<int,std::string> c = std::make_pair(1,"");
	BitypeVar<std::pair<int,std::string>>* three_third = new BitypeVar<std::pair<int,std::string>>(true,c);
	AdvTuple* three = new AdvTuple(0,1,"translation",three_first,three_second,three_third);
	
	BitypeVar<int>* four_first = new BitypeVar<int>(true,-1);
	BitypeVar<int>* four_second = new BitypeVar<int>(true,1);
	std::pair<int,std::string> d = std::make_pair(1,"");
	BitypeVar<std::pair<int,std::string>>* four_third = new BitypeVar<std::pair<int,std::string>>(true,d);
	AdvTuple* four = new AdvTuple(1,0,"translation",four_first,four_second,four_third);
	
	std::vector<AdvTuple>* li = new std::vector<AdvTuple>();
	li->push_back(*(one));
	li->push_back(*(two));
	li->push_back(*(three));
	li->push_back(*(four));
	this->set_liste_depl(li);
		
	this->decoders_update();
}

std::string Garde::get_name() {return "G";}

// -------------------------FAUCON----------------------------------------------

Faucon::Faucon() : Chesspiece() {
	
	BitypeVar<int>* one_first = new BitypeVar<int>(true,2);
	BitypeVar<int>* one_second = new BitypeVar<int>(true,3);
	std::pair<int,std::string> a = std::make_pair(1,"");
	BitypeVar<std::pair<int,std::string>>* one_third = new BitypeVar<std::pair<int,std::string>>(true,a);
	AdvTuple* one = new AdvTuple(1,1,"saut",one_first,one_second,one_third);
	
	BitypeVar<int>* two_first = new BitypeVar<int>(true,2);
	BitypeVar<int>* two_second = new BitypeVar<int>(true,3);
	std::pair<int,std::string> b = std::make_pair(1,"");
	BitypeVar<std::pair<int,std::string>>* two_third = new BitypeVar<std::pair<int,std::string>>(true,b);
	AdvTuple* two = new AdvTuple(-1,1,"saut",two_first,two_second,two_third);
	
	BitypeVar<int>* three_first = new BitypeVar<int>(true,2);
	BitypeVar<int>* three_second = new BitypeVar<int>(true,3);
	std::pair<int,std::string> c = std::make_pair(1,"");
	BitypeVar<std::pair<int,std::string>>* three_third = new BitypeVar<std::pair<int,std::string>>(true,c);
	AdvTuple* three = new AdvTuple(0,1,"saut",three_first,three_second,three_third);
	
	BitypeVar<int>* four_first = new BitypeVar<int>(true,2);
	BitypeVar<int>* four_second = new BitypeVar<int>(true,3);
	std::pair<int,std::string> d = std::make_pair(1,"");
	BitypeVar<std::pair<int,std::string>>* four_third = new BitypeVar<std::pair<int,std::string>>(true,d);
	AdvTuple* four = new AdvTuple(1,0,"saut",four_first,four_second,four_third);
	
	BitypeVar<int>* five_first = new BitypeVar<int>(true,-3);
	BitypeVar<int>* five_second = new BitypeVar<int>(true,-2);
	std::pair<int,std::string> e = std::make_pair(1,"");
	BitypeVar<std::pair<int,std::string>>* five_third = new BitypeVar<std::pair<int,std::string>>(true,e);
	AdvTuple* five = new AdvTuple(1,1,"saut",five_first,five_second,five_third);
	
	BitypeVar<int>* six_first = new BitypeVar<int>(true,-3);
	BitypeVar<int>* six_second = new BitypeVar<int>(true,-2);
	std::pair<int,std::string> f = std::make_pair(1,"");
	BitypeVar<std::pair<int,std::string>>* six_third = new BitypeVar<std::pair<int,std::string>>(true,f);
	AdvTuple* six = new AdvTuple(-1,1,"saut",six_first,six_second,six_third);
	
	BitypeVar<int>* seven_first = new BitypeVar<int>(true,-3);
	BitypeVar<int>* seven_second = new BitypeVar<int>(true,-2);
	std::pair<int,std::string> g = std::make_pair(1,"");
	BitypeVar<std::pair<int,std::string>>* seven_third = new BitypeVar<std::pair<int,std::string>>(true,g);
	AdvTuple* seven = new AdvTuple(0,1,"saut",seven_first,seven_second,seven_third);
	
	BitypeVar<int>* eight_first = new BitypeVar<int>(true,-3);
	BitypeVar<int>* eight_second = new BitypeVar<int>(true,-2);
	std::pair<int,std::string> h = std::make_pair(1,"");
	BitypeVar<std::pair<int,std::string>>* eight_third = new BitypeVar<std::pair<int,std::string>>(true,h);
	AdvTuple* eight = new AdvTuple(1,0,"saut",eight_first,eight_second,eight_third);
	
	std::vector<AdvTuple>* li = new std::vector<AdvTuple>();
	li->push_back(*(one));
	li->push_back(*(two));
	li->push_back(*(three));
	li->push_back(*(four));
	li->push_back(*(five));
	li->push_back(*(six));
	li->push_back(*(seven));
	li->push_back(*(eight));
	this->set_liste_depl(li);
		
	this->decoders_update();
}

std::string Faucon::get_name() {return "Fa";}

// -------------------------CHANCELLIER----------------------------------------------

Chancellier::Chancellier() : Chesspiece() {
	
	BitypeVar<int>* one_first = new BitypeVar<int>(true,-1);
	BitypeVar<int>* one_second = new BitypeVar<int>(true,1);
	std::pair<int,std::string> a = std::make_pair(1,"");
	BitypeVar<std::pair<int,std::string>>* one_third = new BitypeVar<std::pair<int,std::string>>(true,a);
	AdvTuple* one = new AdvTuple(1,2,"saut",one_first,one_second,one_third);
	
	BitypeVar<int>* two_first = new BitypeVar<int>(true,-1);
	BitypeVar<int>* two_second = new BitypeVar<int>(true,1);
	std::pair<int,std::string> b = std::make_pair(1,"");
	BitypeVar<std::pair<int,std::string>>* two_third = new BitypeVar<std::pair<int,std::string>>(true,b);
	AdvTuple* two = new AdvTuple(2,1,"saut",two_first,two_second,two_third);
	
	BitypeVar<int>* three_first = new BitypeVar<int>(true,-1);
	BitypeVar<int>* three_second = new BitypeVar<int>(true,1);
	std::pair<int,std::string> c = std::make_pair(1,"");
	BitypeVar<std::pair<int,std::string>>* three_third = new BitypeVar<std::pair<int,std::string>>(true,c);
	AdvTuple* three = new AdvTuple(-2,1,"saut",three_first,three_second,three_third);
	
	BitypeVar<int>* four_first = new BitypeVar<int>(true,-1);
	BitypeVar<int>* four_second = new BitypeVar<int>(true,1);
	std::pair<int,std::string> d = std::make_pair(1,"");
	BitypeVar<std::pair<int,std::string>>* four_third = new BitypeVar<std::pair<int,std::string>>(true,d);
	AdvTuple* four = new AdvTuple(-1,2,"saut",four_first,four_second,four_third);
	
	std::vector<AdvTuple>* li = new std::vector<AdvTuple>();
	li->push_back(*(one));
	li->push_back(*(two));
	li->push_back(*(three));
	li->push_back(*(four));
	li->push_back(AdvTuple(0,1,"translation"));
	li->push_back(AdvTuple(1,0,"translation"));
	this->set_liste_depl(li);
		
	this->decoders_update();
}

std::string Chancellier::get_name() {return "Cha";}
