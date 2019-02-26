
#include "Chesspiece.hpp"

// -------------------------CHESSPIECE----------------------------------------------

Chesspiece::Chesspiece() : limite(0), position(nullptr), liste_depl(nullptr), liste_capt(nullptr), depl(nullptr), owner(new Human("")), capt(nullptr),updt_needed(false), has_moved(false) {
	this->depl = new Decoder(this);
	this->capt = new Decoder(this);
	} //*< Constructor
	
Chesspiece::Chesspiece(const Chesspiece& pe) : limite(pe.limite), position(pe.position), liste_depl(pe.liste_depl), liste_capt(pe.liste_capt), depl(pe.depl), owner(pe.owner), capt(pe.capt),updt_needed(pe.updt_needed), has_moved(pe.has_moved) {}
	
std::ostream& operator <<(std::ostream &s,Chesspiece &c){
	/* affchage d'un Chesspiece */
    s<<c.get_name(); //"Chesspiece()"
    return s;
}

std::ostream& operator <<(std::ostream &s,Chesspiece* c){
	/* affchage d'un Chesspiece */
    s<<(*c);
    return s;
}

void Chesspiece::set_limite(int lim){
	this->limite = lim;
	this->decoders_update();}

int Chesspiece::get_limite(){return this->limite;}


void Chesspiece::updt(){} // ne fait rien pour cette classe, plustard redéfini evntuellement

void Chesspiece::update(){
	if (this->get_update_needed() == true){this->updt();}
	}

std::string Chesspiece::get_name(){return "Chesspiece()";}

bool Chesspiece::get_has_moved(){return this->has_moved;}
void Chesspiece::set_has_moved(bool mov) {this->has_moved = mov;}

Posi* Chesspiece::get_posi(){return this->position;}

void Chesspiece::set_posi(Posi* p){
	this->position = p;
	this->decoders_update();
	
	if (this->get_has_moved() == false){this->set_has_moved(true);}
	
	}

std::vector<AdvTuple>* Chesspiece::get_liste_depl(){return this->liste_depl;}
void Chesspiece::set_liste_depl(std::vector<AdvTuple>* li){
	this->liste_depl = li;
	this->decoders_update();
	}
	
std::vector<AdvTuple>* Chesspiece::get_liste_capt(){return this->liste_capt;}
void Chesspiece::set_liste_capt(std::vector<AdvTuple>* li){
	this->liste_capt = li;
	this->decoders_update();
	}

Decoder* Chesspiece::get_depl(){return this->depl;}

std::vector<std::pair<std::pair<int,int>,AdvTuple>> Chesspiece::algo(std::string s){
	if (s == "depl"){return this->depl->decode();}
	else if (s == "capt"){return this->capt->decode();}
	else {throw MyException(&mout, "mode invalide pour algo chesspiece");}
}

Player* Chesspiece::get_owner(){return this->owner;}
void Chesspiece::set_owner(Player* proprio){this->owner = proprio;}

void Chesspiece::decoders_update(){
	if (this->get_liste_capt() == nullptr){this->make_capt_list();}
	
	this->depl->maj(this,"depl");
	this->capt->maj(this,"capt");
}

void Chesspiece::set_update_needed(bool up){this->updt_needed = up;}
bool Chesspiece::get_update_needed(){return this->updt_needed;}

void Chesspiece::make_capt_list(){this->set_liste_capt(this->get_liste_depl());}

// -------------------------DECODER----------------------------------------------

Decoder::Decoder() : pe(nullptr) , liste(nullptr), limite(0), posi(nullptr) {} //*< Constructor
Decoder::Decoder(Chesspiece* piece) : pe(piece), liste(nullptr), limite(0), posi(nullptr) {} //*< Constructor

std::ostream& operator <<(std::ostream &s,Decoder &c){
	/* affchage d'un Decoder */
    s<<"Decoder("<<c.get_limite()<<")";
    return s;
}

void Decoder::set_liste(std::vector<AdvTuple>* li){this->liste = li;}

int Decoder::get_limite(){return this->limite;}

void Decoder::maj(Chesspiece* piece,std::string s){
	this->pe = piece;
	
	if (s == "depl"){this->liste = this->pe->get_liste_depl();}
	else if (s == "capt"){this->liste = this->pe->get_liste_capt();}
	else{throw MyException(&mout, "mode invalide pour maj decoder");}
	
	this->limite = this->pe->get_limite();
	this->posi = this->pe->get_posi();
}

std::vector<std::pair<std::pair<int,int>,AdvTuple>> Decoder::decode(){
	bool updt = false;
	
	std::vector<std::pair<std::pair<int,int>,AdvTuple>>* res = new std::vector<std::pair<std::pair<int,int>,AdvTuple>>();
	
	for(long long unsigned int i=0;i<this->liste->size();i++){
		AdvTuple tup = (*(this->liste))[i];
		std::vector<std::pair<int,int>>* vals = tup.get_res(this->limite,*(this->posi));
		for(long long unsigned int j=0;j<vals->size();j++){
			std::pair<std::pair<int,int>,AdvTuple> paire = std::make_pair((*vals)[j],tup);
			res->push_back(paire);
		}
		
		if((updt == false) and (tup.need_update() == true)){
			updt = true;
			if (this->pe->get_update_needed() != true){this->pe->set_update_needed(true);}
		}
	}	
	
	return *res;
}
