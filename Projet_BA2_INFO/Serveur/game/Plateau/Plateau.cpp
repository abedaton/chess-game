
#include "Plateau.hpp"

extern MyOstream mout;

// ----------------FONCTION HORS PLATEAU---------------------------

bool detect_pair_in_list_of_pairs(std::vector<std::pair<int,int>> liste ,std::pair<int,int> paire){
	/* fonction qui détecte une paire dans une liste de paires */
	
	bool found = false;
	for(long long unsigned int i=0;(i<(liste.size()) and (found == false));i++){
		std::pair<int,int> comp = liste[i];
		
		if ((found == false) and (comp.first == paire.first) and (comp.second == paire.second)){
			found = true;
		}
	}
	
	return found;
}

bool detect_pair_in_list_of_double_pairs(std::vector<std::pair<std::pair<int,int>,AdvTuple>> liste ,std::pair<int,int> paire){
	/* fonction qui détecte une paire dans une liste de doubles paires
	 * dans la double paire il y a une paire et un Advtuple dont on se fout pour cette recherche*/
	
	bool found = false;
	for(long long unsigned int i=0;(i<(liste.size()) and (found == false));i++){
		std::pair<int,int> comp = liste[i].first;
		
		if ((found == false) and (comp.first == paire.first) and (comp.second == paire.second)){
			found = true;
		}
	}
	
	return found;
}

std::string adaptive_mode(BitypeVar<Chesspiece*> out,std::string mode){
	/* fonction qui vérifie si la case d'arrivée est vide ou remplie et retourne le mode corresponant */
	
	if (mode == ""){ // deduire mode
		// verifier si case vide ou remplie
		if (out.get_state() == true){mode = "capt";} // --> remplie -> capt
		else {mode = "depl";} // --> vide -> move
	}
	return mode;
}

std::vector<std::vector<BitypeVar<Chesspiece*>>>* make_board(int plat_size){
	/* fonction qui initialise le plateau (vecteur de vecteur de case) */
	
	std::vector<std::vector<BitypeVar<Chesspiece*>>>* plat = new std::vector<std::vector<BitypeVar<Chesspiece*>>>();
	for(int i=0;i<plat_size;i++){
		std::vector<BitypeVar<Chesspiece*>>* ligne = new std::vector<BitypeVar<Chesspiece*>>();
		for(int j=0;j<plat_size;j++){
			Chesspiece* chess_ini = new Chesspiece();
			ligne->push_back(BitypeVar<Chesspiece*>(false,chess_ini));
		}
		plat->push_back(*(ligne));
	}
	return plat;
}

// ------------------PLATEAU------------------------

Plateau::Plateau(int t) : taille(t), board(nullptr){ //*< Constructor
	
	// creation du tableau !!!
	int plat_size = this->taille;
	
	std::vector<std::vector<BitypeVar<Chesspiece*>>>* plat = make_board(plat_size);
	
	this->board = plat;	
	} 

Plateau::Plateau(const Plateau& plat): taille(plat.taille), board(nullptr){
	
	std::vector<std::vector<BitypeVar<Chesspiece*>>>* empty_plat = make_board(this->taille);
	this->board = empty_plat;
	
	for(int i=0;i<plat.taille;i++){
		for(int j=0;j<plat.taille;j++){
			std::pair<int,int> paire = std::make_pair(j,i);
			BitypeVar<Chesspiece*> bi_var = plat.get_piece(paire);
			if (bi_var.get_state() == true){
				Chesspiece* pe = bi_var.get_var();
				this->set_piece(paire,&(*(pe)));
			}
		}
	}
}


std::ostream& operator <<(std::ostream &s,Plateau &c){
	/* affchage d'un Plateau */
	
	(void)c;
	
	s<<"Plateau()";

    return s;
}


std::ostream& operator <<(std::ostream &s,Plateau* c){
	/* affchage d'un Plateau */
    s<<(*c);
    return s;
}

int Plateau::get_taille() const {return this->taille;}

std::vector<BitypeVar<Chesspiece*>> Plateau::get_row(int ligne){return (*this->board)[ligne];}

void Plateau::set_piece(std::pair<int,int> paire,Chesspiece* c,bool initial){
	/* fonction qui place une piece a un endroit peu importe de ce qui se trouve catuellement a cet endroit
	 * cette fonction met aussi a jour les caractèristique de la piece */
	
	int colonne = paire.first;
	int ligne = paire.second;
	
	Posi* new_posi = new Posi(colonne,ligne);
	
	c->set_posi(new_posi);
	
	if (initial){c->set_has_moved(false);}
	
	c->set_limite(this->taille);
	
	BitypeVar<Chesspiece*>* tup_c = new BitypeVar<Chesspiece*>(true,c);
	
	((*this->board)[ligne])[colonne] = *(tup_c);
}

void Plateau::set_piece(std::pair<int,int> paire,Chesspiece* c){return this->set_piece(paire,c,false);}

BitypeVar<Chesspiece*> Plateau::get_piece(std::pair<int,int> paire) const{
	/* fonction qui permet de recuperer une piece se trouvant a une coordonée donnée */
	 
	int colonne = paire.first;
	int ligne = paire.second;
	
	return ((*this->board)[ligne])[colonne];
}

BitypeVar<Chesspiece*> Plateau::get_piece(int sum_val) const{
	/* fonction qui permet de recuperer une piece se trouvant a une coordonée donnée */
	
	BitypeVar<int>* bit = new BitypeVar<int>(false,0);
	BitypeVar<int>* plat_size = new BitypeVar<int>(true,this->get_taille());

	PlatPosi* ppos = new PlatPosi(sum_val,*bit,*plat_size);
	
	return this->get_piece(ppos->to_pair());
}
	
bool Plateau::isvalid_move(std::pair<int,int> paire_in, std::pair<int,int> paire_out, std::string mode){
	/* fonction qui verifie si un mouvement est valdide */
	bool res;
	
	BitypeVar<Chesspiece*> tup_pe_in = this->get_piece(paire_in);
	Chesspiece* pe = tup_pe_in.get_var();
	
	BitypeVar<Chesspiece*> tup_pe_out = this->get_piece(paire_out);
	
	if (tup_pe_out.get_state() == false or pe->get_owner() != (tup_pe_out.get_var()->get_owner())){
		
		mode = adaptive_mode(tup_pe_out,mode);

		std::vector<std::pair<std::pair<int,int>,AdvTuple>> res_pe = pe->algo(mode); //<----------------------------------------------------------------------------------------------
		res = detect_pair_in_list_of_double_pairs(res_pe,paire_out);
		
		if (mode == "depl"){res = res and (tup_pe_out.get_state() == false);}
		else{res = res and (tup_pe_out.get_state() == true) and (pe->get_owner() != tup_pe_out.get_var()->get_owner());}
		
	}
	else{res = false;} // même propriétaire de pieces
		
	return res;
	
}

bool Plateau::isvalid_move(std::pair<int,int> paire_in, std::pair<int,int> paire_out){
	/* fonction surchargée, qui permet d'ommettre le string indiquant le mode */
	
	return this->isvalid_move(paire_in, paire_out, "");
}

bool Plateau::move(std::pair<int,int> paire_in,std::pair<int,int> paire_out){
	/* fonction qui déplace une piece vers une coordonée donnée en vérifiant au préalable si le mouvement est valide */
	
	int col_in = paire_in.first;
	int lig_in = paire_in.second;

	int col_out = paire_out.first;
	int lig_out = paire_out.second;
	
	BitypeVar<Chesspiece*> tup_pe = get_piece(paire_in);
	
	bool moved = false;
	
	if (tup_pe.get_state() == true){ // (!= None en python)
		Chesspiece* pe = tup_pe.get_var();
		
		bool inside;
		mout<<"("<<col_in<<","<<lig_in<<") --> ("<<col_out<<","<<lig_out<<")"<<std::endl;
		
		inside = this->isvalid_move(paire_in,paire_out);
				
		if (inside == true){
			mout<<"mouvement valide"<<std::endl;
			Posi* new_posi = new Posi(col_out,lig_out);
			
			pe->set_posi(new_posi); // mive a jour de la posi de pe
			pe->update();
			
			BitypeVar<Chesspiece*>* new_tup_pe = new BitypeVar<Chesspiece*>(true,pe);
			
			((*this->board)[lig_out])[col_out] = *(new_tup_pe);
			Chesspiece* chess_ini = new Chesspiece();
			((*this->board)[lig_in])[col_in] = BitypeVar<Chesspiece*>(false,chess_ini);
			
			moved = true;
		}
	}
	
	return moved;
}

bool Plateau::switch_positions(std::pair<int,int> paire_in,std::pair<int,int> paire_out){
	/* fonction qui inverse la position de 2 pieces sur le plateau */
	
	int col_in = paire_in.first;
	int lig_in = paire_in.second;

	int col_out = paire_out.first;
	int lig_out = paire_out.second;
	
	BitypeVar<Chesspiece*> tup_pe_in = get_piece(paire_in);
	
	bool moved = false;
	
	if (tup_pe_in.get_state() == true){ // (!= None en python)
		Chesspiece* pe_in = tup_pe_in.get_var();
		
		BitypeVar<Chesspiece*> tup_pe_out = get_piece(paire_out);
		
		if (tup_pe_out.get_state() == true){ // (!= None en python)
			Chesspiece* pe_out = tup_pe_out.get_var();
		
			Posi* new_in_posi = new Posi(col_out,lig_out);
			Posi* new_out_posi = new Posi(col_in,lig_in);
			
			pe_in->set_posi(new_in_posi);
			pe_in->update();
			
			pe_out->set_posi(new_out_posi);
			pe_out->update();
						
			BitypeVar<Chesspiece*>* new_tup_pe_in = new BitypeVar<Chesspiece*>(true,pe_in);
			BitypeVar<Chesspiece*>* new_tup_pe_out = new BitypeVar<Chesspiece*>(true,pe_out);
			
			((*this->board)[lig_out])[col_out] = *(new_tup_pe_in);
			((*this->board)[lig_in])[col_in] = *(new_tup_pe_out);
			
			moved = true;
		}
	}
	
	return moved;
}

bool Plateau::verify_in_board(std::pair<int,int> paire){
	/* fonction qui vérifie si une coordonée se trouve dans le tableau */
	int col = paire.first;
	int lig = paire.second;
	
	return (col >= 0 and col < this->taille and lig >= 0 and lig < this->taille);
}

bool Plateau::is_empty_location(std::pair<int,int> paire){
	/* fonction qui vérifie si a une coordonée ne se trouve pas une piece */
	return (not(this->get_piece(paire)).get_state());
}

bool Plateau::is_empty_location(int sum_coords){
	/* fonction qui vérifie si a une coordonée ne se trouve pas une piece */
	return (not(this->get_piece(sum_coords)).get_state());
}

int Plateau::begin_position(){return 0;}
int Plateau::end_position(){
	
	int plat_size = this->get_taille();
	
	return (plat_size*plat_size)-1; // -1 car commence a 0
}

//PlatPosi* Plateau::convert_coord(int sum_coords){return 0;}
