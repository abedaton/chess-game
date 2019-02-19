
#include "Plateau.hpp"

extern MyOstream mout;

// ----------------FONCTION HORS PLATEAU---------------------------

bool detect_pair_in_list_of_pairs(std::vector<std::pair<int,int>> liste ,std::pair<int,int> paire){
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
	bool found = false;
	for(long long unsigned int i=0;(i<(liste.size()) and (found == false));i++){
		std::pair<int,int> comp = liste[i].first;
		
		if ((found == false) and (comp.first == paire.first) and (comp.second == paire.second)){
			found = true;
		}
	}
	
	return found;
}

std::string make_ligne(std::string s,int taille_voulue,int taille){
	std::string res;
	
	for(int i=0;i<taille;i++){
		res += "|";
		for(int j=0;j<taille_voulue;j++){res += s;}
	}
	
	res += "|";
	
	return res;
}

std::string crea_ligne_lettres(int limite,int taille_voulue){
	std::string alph = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	std::string res;
		
	res = "";
	for(int i=0;i<limite;i++){
		
		int taille_reste = taille_voulue-1; // 1 = taille alph[i]
		int av = taille_reste/2;
		int ap = taille_reste - av;
		
		res += " ";
		for(int j=0;j<av;j++){res += " ";}
		res += alph[i];
		for(int m=0;m<ap;m++){res += " ";}
		}
	res += " ";
	
	return res;
}

std::string adaptive_mode(BitypeVar<Chesspiece*> out,std::string mode){
	if (mode == ""){ // deduire mode
		// verifier si case vide ou remplie
		if (out.get_state() == true){mode = "capt";} // --> remplie -> capt
		else {mode = "depl";} // --> vide -> move
	}
	return mode;
}

std::vector<std::vector<BitypeVar<Chesspiece*>>>* make_board(int plat_size){
	
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
	
	s<<(c.adaptive_affichage("","",nullptr,"")).str();

    return s;
}


std::ostream& operator <<(std::ostream &s,Plateau* c){
	/* affchage d'un Plateau */
    s<<(*c);
    return s;
}

std::stringstream Plateau::adaptive_affichage(std::string pre ,std::string suf ,Dico* dico, std::string lang){
	
	std::stringstream s;
	
	std::vector<std::vector<BitypeVar<Chesspiece*>>>* plat = this->board;
	
	int taille_voulue_hor = 8;
	int taille_voulue_ver = 2;
		
	std::string big_l = make_ligne("-",taille_voulue_hor,int(plat->size())) + "-\n";
	std::string big_l_vide = make_ligne(" ",taille_voulue_hor,int(plat->size())) + "\n";
	std::string letter_line = crea_ligne_lettres(int(plat->size()),taille_voulue_hor);
	
	int ver_av = taille_voulue_ver/2;
	int ver_ap = taille_voulue_ver - ver_av;
	
	std::stringstream ss;
	
	s << letter_line << "\n" << big_l_vide;

	for(long long unsigned int i=0;i<plat->size();i++){
		
		s<<big_l;
		for(int k=0;k<ver_av;k++){s<<big_l_vide;}
		s<<"|";
		
		long long unsigned int new_i = plat->size()-1-i;
		for(long long unsigned int j=0;j<((*plat)[i]).size();j++){
			
			ss.clear();//clear any bits set
			ss.str(std::string());
			
			BitypeVar<Chesspiece*> elem = ((*plat)[new_i])[j];
			Chesspiece* piece = elem.get_var();
			if (elem.get_state() == true){
				
				std::stringstream temp_ss;
				temp_ss<<pre<<*(piece)<<suf;
				
				if (dico != nullptr){
					ss<<dico->search(lang,temp_ss.str());
				}
				else{ss<<temp_ss.str();}
			}
			
			else {ss<<" ";}
			
			std::string str_elem;
			str_elem = ss.str();
			int elem_size = int(str_elem.length());
			int taille_reste = taille_voulue_hor - elem_size;
			int hor_av = taille_reste/2;
			int hor_ap = taille_reste - hor_av;
			
			for(int m=0;m<hor_av;m++){s<<" ";}
			
			if (elem.get_state() == true){
				
				std::stringstream temp_s;
				temp_s<<pre<<*(piece)<<suf;
				
				if (dico != nullptr){
					s<<dico->search(lang,temp_s.str());
				}
				else{s<<temp_s.str();}
			}
			else {s<<" ";}
			
			for(int n=0;n<hor_ap;n++){s<<" ";}
			
			s<<"|";
				
		}
		
		std::string str_numb = std::to_string(new_i+1);
		int numb_size = int(str_numb.size());
		int numb_reste = taille_voulue_hor-numb_size;
        int numb_av = numb_reste/2;
        for(int p=0;p<numb_av;p++){s<<" ";}
		s<<str_numb;

		s<<"\n";
		for(int o=0;o<ver_ap;o++){s<<big_l_vide;}
	}
	s<<big_l;
    
    return s;
	}

int Plateau::get_taille(){return this->taille;}

std::vector<BitypeVar<Chesspiece*>> Plateau::get_row(int ligne){return (*this->board)[ligne];}

void Plateau::set_piece(std::pair<int,int> paire,Chesspiece* c,bool initial){
	
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
	int colonne = paire.first;
	int ligne = paire.second;
	
	return ((*this->board)[ligne])[colonne];
}

std::pair<bool,std::string> Plateau::isvalid_move(std::pair<int,int> paire_in, std::pair<int,int> paire_out){
	return this->isvalid_move(paire_in, paire_out, "");
}
	
std::pair<bool,std::string> Plateau::isvalid_move(std::pair<int,int> paire_in, std::pair<int,int> paire_out, std::string mode){ // !!!!!!!!!!!!!!!!!!!!!! revenir a bool seul !!!
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
	
	std::pair<bool,std::string> result = std::make_pair(res,mode);
	
	return result; // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! revenir a bool seul !!!
	
}

bool Plateau::move(std::pair<int,int> paire_in,std::pair<int,int> paire_out){
	
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
		
		std::pair<bool,std::string> ins_p;
		ins_p = this->isvalid_move(paire_in,paire_out);
		
		inside = ins_p.first;
		
		if (inside == true){
			mout<<"mouvement valide"<<std::endl;
			Posi* new_posi = new Posi(col_out,lig_out);
			
			pe->set_posi(new_posi);
			
			// mettre a jour posi !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
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
	int col = paire.first;
	int lig = paire.second;
	
	return (col >= 0 and col < this->taille and lig >= 0 and lig < this->taille);
}

bool Plateau::is_empty_location(std::pair<int,int> paire){
	return (not(this->get_piece(paire)).get_state());
	}
