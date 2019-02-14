
#include "ClassicChess.hpp"

extern MyOstream mout;

//-----------------------HORS CLASSE ClassicChess-----------------------------------------------

template <typename Type>
bool verifier_type_pe(BitypeVar<Chesspiece*> adv_pe){
	Chesspiece* pe;
	bool res = false;
	
	if (adv_pe.get_state() != false){
		pe = adv_pe.get_var();
		res = verifier_type_pe<Type>(pe);
		
	}
		
	return res;
}

template <typename Type>
bool verifier_type_pe(Chesspiece* pe){
	bool res;

	if(Type* v = dynamic_cast<Type*>(pe)){
		(void)v; // enlever warning
		res = true;
	}
		
	else{res = false;}
	
	return res;
}

bool check_end_game(BitypeVar<Chesspiece*> adv_pe, bool switch_pos){
	bool end_game;
	
	if (not(switch_pos)){
		end_game = verifier_type_pe<Roi>(adv_pe);
	}
	else{end_game = false;}
	
	return end_game;
}

BitypeVar<int>* detect_ennemy_pion_in_vect(std::vector<BitypeVar<Chesspiece*>> vect, Player* owner){
	BitypeVar<Chesspiece*> elem;
	bool found = false;
	
	BitypeVar<int>* res = new BitypeVar<int>();
	res->set_state(false);
	
	long long unsigned int i=0;
	while((i<vect.size()) and (res->get_state() == false)){		
		found = verifier_type_pe<Pion>(vect[i]);
		if (found == true){
			if((vect[i].get_var())->get_owner() == owner){
				res->set_state(true);
				res->set_var(int(i));
			}
		}
		i++;
	}
	return res;
}

BitypeVar<Chesspiece*>* select_king(std::vector<Chesspiece*>* vect,Player* owner){
	long long unsigned int i=0;
	bool found = false;	
	BitypeVar<Chesspiece*>* res = new BitypeVar<Chesspiece*>();
	res->set_state(false);
	
	while((i<vect->size()) and (found == false)){		
		
		if ((*vect)[i]->get_owner() == owner){
			res->set_var((*vect)[i]);
			res->set_state(true);
			found = true;
		}
		
		i++;
	}
	return res;
}

BitypeVar<std::pair<int,int>>* calculate_move_between_zones(MatPosi* begin, MatPosi* end){
	// fonction crée pour amelioration roque
	
	bool lig,col;
	std::pair<int,int> paire;
	BitypeVar<std::pair<int,int>>* res = new BitypeVar<std::pair<int,int>>();
	
	res->set_state(false);
	
	if (begin->get_lig() == end->get_lig()){lig = true;}
	if (begin->get_col() == end->get_col()){col = true;}
	
	if (lig and not(col)){
		res->set_state(true);
		paire = std::make_pair(1,0);
		res->set_var(paire);
	}
	else if (not(lig) and col){
		res->set_state(true);
		paire = std::make_pair(0,1);
		res->set_var(paire);
	}
	else if (not(lig) and not(col)){
		
		int diff_lig = begin->get_lig() - end->get_lig();
		int diff_col = begin->get_col() - end->get_col();
		
		if(std::abs(diff_lig) == std::abs(diff_col)){ //diagonale
			
			// verification de signe
			if(diff_lig == diff_col){
				res->set_state(true);
				paire = std::make_pair(1,1);
				res->set_var(paire);
			}
			
			else{
				res->set_state(true);
				paire = std::make_pair(-1,1);
				res->set_var(paire);
			}	
		
		}
		//else{} // pas diagonale
		
	}
	else{throw MyException(&mout,"calcul de zones intermediares d'un même emplacement");}
	
	return res;
	
}

std::pair<int,int> calc_roc_destinations(bool gauche_isking,std::vector<MatPosi>* between_vect){
		
	int taille = int(between_vect->size());
	
	if (taille<2){throw MyException(&mout,"roc impossible, espace insuffisant");}
	
	int co_roi,co_tour;
	
	if (taille%2 != 0){
		co_roi = taille/2;
	}
	else{
		if (gauche_isking == true){
			co_roi = taille/2;
		}
		else{
			co_roi = (taille/2) - 1 ;
		}
		
	}
		
	if (gauche_isking == false){ // tour a gauche
		co_tour = co_roi+1;
	}
	else{
		co_tour = co_roi-1;
	}
	
	std::pair<int,int> res = std::make_pair(co_roi,co_tour);
	
	return res;
	
}

std::vector<MatPosi*>* calc_king_move_path(bool king_isleft,int king_dest,std::vector<MatPosi>* between_vect){
	
	std::vector<MatPosi*>* res = new std::vector<MatPosi*>();
	
	if (king_isleft == true){
		for(int i=0;i<king_dest;i++){
			res->push_back(&((*between_vect)[i]));
		}
		
	}
	else{
		for(int i=king_dest+1;i<int(between_vect->size());i++){
			res->push_back(&((*between_vect)[i]));
		}
	}
	
	return res;
}

std::pair<MatPosi*,MatPosi*> sort_two_mpos(MatPosi* mpos_one,MatPosi* mpos_two){
	
	MatPosi* mpos_gauche;
	MatPosi* mpos_droite;
	
	if(*mpos_one < *mpos_two) { // roi a gauche
		mpos_gauche = mpos_one;
		mpos_droite = mpos_two;
	}
	
	else if(*mpos_one > *mpos_two) {
		mpos_gauche = mpos_two;
		mpos_droite = mpos_one;
	}
	
	//(*mpos_one == *mpos_two) 
	else{throw MyException(&mout,"sort avec 2 fois la même piece");} // roi a gauche
	
	return std::make_pair(mpos_gauche,mpos_droite);
	
}

BitypeVar<std::vector<MatPosi>*>* calc_zones_between_zones(MatPosi* begin, MatPosi* end, Message* messenger,Player* player){ // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	
	// fonction crée pour amelioration roque
	
	BitypeVar<std::vector<MatPosi>*>* res = new BitypeVar<std::vector<MatPosi>*>();
	std::vector<MatPosi>* vect = new std::vector<MatPosi>();
	res->set_state(false);
	
	BitypeVar<std::pair<int,int>>* bit_paire;
	
	int lig,col;
	
	bit_paire = calculate_move_between_zones(begin, end);
	
	if (bit_paire->get_state() == true){
		
		std::pair<int,int > paire = bit_paire->get_var();
		
		MatPosi* debut;
		MatPosi* fin;
		
		if (*begin > *end){
			debut = end;
			fin = begin;
		}
		else{
			debut = begin;
			fin = end;
		}
		
		
		lig = debut->get_lig();
		col = debut->get_col();
		
		res->set_state(true);
		
		MatPosi* temp_mpos;
		
		temp_mpos = new MatPosi(col,lig);
		
		while(*temp_mpos < *fin){
			
			col += paire.first;
			lig += paire.second;
			
			temp_mpos->set_col(col);
			temp_mpos->set_lig(lig);
			
			std::stringstream ss;
			ss<<debut->to_string()<<" "<<temp_mpos->to_string()<<" "<<fin->to_string()<<std::endl;
			messenger->send_msg(player,ss.str());
			
			if(*temp_mpos < *fin){vect->push_back(*temp_mpos);}
			
		}
		res->set_var(vect);		
	}
	
	return res;
	
}


//--------------------ClassicChess----------------------------------------------------------------------------------------------------

ClassicChess::ClassicChess(Player* p_low,Player* p_high,Dico* d , std::string lang, Message* msg) : plateau(nullptr) , low_player(p_low), high_player(p_high), active_player(p_low), dico(d), langue(lang), messenger(msg) {
	this->initialisation();
} //*< Constructor

Player* ClassicChess::get_low_player(){return this->low_player;}
Player* ClassicChess::get_high_player(){return this->high_player;}

Player* ClassicChess::get_other_player(Player* play){
	if (play == this->get_low_player()){return this->get_high_player();}
	else if (play == this->get_high_player()){return this->get_low_player();}
	else{throw MyException(&mout, "probleme get other player");}
}

Player* ClassicChess::get_active_player(){return this->active_player;}
Player* ClassicChess::get_non_active_player(){return this->get_other_player(this->get_active_player());}

Message* ClassicChess::get_messenger(){return this->messenger;}

void  ClassicChess::set_active_player(Player* a){this->active_player = a;}
void  ClassicChess::set_low_player(Player* l){this->low_player = l;}
void  ClassicChess::set_high_player(Player* h){this->high_player = h;}

int ClassicChess::get_player_row(Player* player){
	if (player == get_low_player()){return 0;}
	else if (player == get_high_player()){return this->plateau->get_taille()-1;}
	else{throw MyException(&mout, "probleme player cote plateau");}
}

Plateau* ClassicChess::get_plateau(){return this->plateau;}
void ClassicChess::set_plateau(Plateau* plat){this->plateau = plat;}

Dico* ClassicChess::get_dico(){return this->dico;}

std::string ClassicChess::get_langue(){return this->langue;}

void ClassicChess::initial_set_piece(Chesspiece* pe,Player* own,std::string mov){
	pe->set_owner(own);
	
	std::stringstream ss;
	ss<<pe->get_name()<<","<<pe->get_owner()<<std::endl;
	this->get_messenger()->send_msg(this->get_active_player(),ss.str());
	
	MatPosi* mpos = new MatPosi(mov);	
	this->plateau->set_piece(mpos->to_pair(),pe);
}

void ClassicChess::initialisation(){
	this->initialise_board();
	this->initialise_low_pieces();
	this->initialise_high_pieces();
}


void ClassicChess::initialise_board(){	
	Plateau* plat = new Plateau(8);
	this->set_plateau(plat);
	
}

void ClassicChess::initialise_low_pieces(){ 

	Player* own = get_low_player();
	
	//ligne 1
	Tour* tour_un = new Tour();
	this->initial_set_piece(tour_un,own,"A1");
	
	Chevalier* cheval_un = new Chevalier();
	this->initial_set_piece(cheval_un,own,"B1");
	
	Fous* fou_un = new Fous();
	this->initial_set_piece(fou_un,own,"C1");
	
	Dame* dame = new Dame();
	this->initial_set_piece(dame,own,"D1");
	
	Roi* roi = new Roi();
	this->initial_set_piece(roi,own,"E1");
	
	Fous* fou_deux = new Fous();
	this->initial_set_piece(fou_deux,own,"F1");
	
	Chevalier* cheval_deux = new Chevalier();
	this->initial_set_piece(cheval_deux,own,"G1");
	
	Tour* tour_deux = new Tour();
	this->initial_set_piece(tour_deux,own,"H1");
	
	//ligne 2
	Pion* pion_un = new Pion("up");
	this->initial_set_piece(pion_un,own,"A2");
	
	Pion* pion_deux = new Pion("up");
	this->initial_set_piece(pion_deux,own,"B2");
	
	Pion* pion_trois = new Pion("up");
	this->initial_set_piece(pion_trois,own,"C2");
	
	Pion* pion_quatre = new Pion("up");
	this->initial_set_piece(pion_quatre,own,"D2");
	
	Pion* pion_cinq = new Pion("up");
	this->initial_set_piece(pion_cinq,own,"E2");
	
	Pion* pion_six = new Pion("up");
	this->initial_set_piece(pion_six,own,"F2");
	
	Pion* pion_sept = new Pion("up");
	this->initial_set_piece(pion_sept,own,"G2");
	
	Pion* pion_huit = new Pion("up");
	this->initial_set_piece(pion_huit,own,"H2");

}

void ClassicChess::initialise_high_pieces(){

	Player* own = get_high_player();
		
	//ligne 1
	Tour* tour_un = new Tour();
	this->initial_set_piece(tour_un,own,"A8");
	
	Chevalier* cheval_un = new Chevalier();
	this->initial_set_piece(cheval_un,own,"B8");
	
	Fous* fou_un = new Fous();
	this->initial_set_piece(fou_un,own,"C8");
	
	Dame* dame = new Dame();
	this->initial_set_piece(dame,own,"D8");
	
	Roi* roi = new Roi();
	this->initial_set_piece(roi,own,"E8");
	
	Fous* fou_deux = new Fous();
	this->initial_set_piece(fou_deux,own,"F8");
	
	Chevalier* cheval_deux = new Chevalier();
	this->initial_set_piece(cheval_deux,own,"G8");
	
	Tour* tour_deux = new Tour();
	this->initial_set_piece(tour_deux,own,"H8");
	
	//ligne 2
	Pion* pion_un = new Pion("down");
	this->initial_set_piece(pion_un,own,"A7");
	
	Pion* pion_deux = new Pion("down");
	this->initial_set_piece(pion_deux,own,"B7");
	
	Pion* pion_trois = new Pion("down");
	this->initial_set_piece(pion_trois,own,"C7");
	
	Pion* pion_quatre = new Pion("down");
	this->initial_set_piece(pion_quatre,own,"D7");
	
	Pion* pion_cinq = new Pion("down");
	this->initial_set_piece(pion_cinq,own,"E7");
	
	Pion* pion_six = new Pion("down");
	this->initial_set_piece(pion_six,own,"F7");
	
	Pion* pion_sept = new Pion("down");
	this->initial_set_piece(pion_sept,own,"G7");
	
	Pion* pion_huit = new Pion("down");
	this->initial_set_piece(pion_huit,own,"H7");

}

void ClassicChess::show_bitype_vect(std::vector<BitypeVar<Chesspiece*>> vect){
	std::stringstream ss_glob;
	
	BitypeVar<Chesspiece*> elem;
	ss_glob<<"[";
	for(long long unsigned int i=0;i<vect.size();i++){
		if (vect[i].get_state() == true){
			
			// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! probleme mout vs std::cout avec heritage --> complexe! --> demander a prof
			//(probleme avec mout<<*(vect[i].get_var())) 
			//solution
			std::stringstream ss;
			ss<<*(vect[i].get_var());
			ss_glob<<ss.str();}
			
		else{ss_glob<<"None";}
		
		if (i != vect.size()-1){ss_glob<<", ";}
	}
	ss_glob<<"]"<<std::endl;
	this->get_messenger()->send_msg(this->get_active_player(),ss_glob.str());
}

BitypeVar<std::vector<MatPosi>*>* ClassicChess::calculate_zones_between_zones(MatPosi* begin, MatPosi* end){
	
	return calc_zones_between_zones(begin, end, this->get_messenger(),this->get_active_player());
	
}

std::pair<std::string,BitypeVar<Chesspiece*>> ClassicChess::in_input(std::string first_comment, std::string second_comment,std::string third_comment,bool ret_accept){
	BitypeVar<Chesspiece*> dst;
	std::pair<int,int> conv;
	Chesspiece* cap_piece;
	
	bool part_a;
	
	std::string in = "";
	while (not part_a){
		
		this->get_messenger()->send_msg(this->get_active_player(),first_comment,true);
		
		in = this->get_messenger()->recieve_msg(this->get_active_player());
		
		if (not((ret_accept == true) and (in == "ret"))){
		
			bool valid,again;
				
			again = false;
			valid = this->verify_validity_input(in);
			
			if (valid == true){
				MatPosi* mpos_in = new MatPosi(in);
				dst = this->plateau->get_piece(mpos_in->to_pair());
				
				if (dst.get_state() == true){
					cap_piece = dst.get_var();
					//mout<<"propio = "<<cap_piece->get_owner()<<std::endl;
					if (cap_piece->get_owner() != get_active_player()){
						this->get_messenger()->send_msg(this->get_active_player(),second_comment,true);
						again = true;
					}
				}
				else{
					this->get_messenger()->send_msg(this->get_active_player(),third_comment,true);
					again = true;
				}
					
				part_a = not(again);
			}
			else{part_a = false;}
		}
		else{part_a = true;}
	}
		
	std::pair<std::string,BitypeVar<Chesspiece*>> paire = std::make_pair(in,dst);
		
	return paire;
}

std::pair<std::string,BitypeVar<Chesspiece*>> ClassicChess::in_input(std::string first_comment, std::string second_comment,std::string third_comment){
	return this->in_input(first_comment, second_comment,third_comment,false);
}

std::pair<std::string,BitypeVar<Chesspiece*>> ClassicChess::in_depl_input(){
		
	std::stringstream ss_one,ss_two,ss_three;
	ss_one << this->dico->search(this->langue,"pe_a_depl");
	ss_two << this->dico->search(this->langue,"retry")<<", "<< this->dico->search(this->langue,"move_pe_oth");
	ss_three << this->dico->search(this->langue,"retry")<<", "<< this->dico->search(this->langue,"empty");
	
	return this->in_input(ss_one.str(), ss_two.str(), ss_three.str());
}

std::pair<std::string,BitypeVar<Chesspiece*>> ClassicChess::in_roc_input(){
	
	std::stringstream ss_one,ss_two,ss_three;
	ss_one << this->dico->search(this->langue,"roc_pe")<<std::endl;
	ss_one << this->dico->search(this->langue,"ou")<<" ret "<<this->dico->search(this->langue,"ret");
	
	ss_two << this->dico->search(this->langue,"retry")<<", "<< this->dico->search(this->langue,"roc_oth");
	ss_three << this->dico->search(this->langue,"retry")<<", "<< this->dico->search(this->langue,"roc_empty");
		
	return this->in_input(ss_one.str(), ss_two.str(), ss_three.str(),true);
}

bool ClassicChess::check_illegal_move(std::string in,std::string out){
	bool again;
	if (not(this->verify_move(in,out))){
		
		std::stringstream ss;
		ss<<this->dico->search(this->langue,"retry")<<", "<< this->dico->search(this->langue,"illegal_move")<<"!"<<std::endl;
		this->get_messenger()->send_msg(this->get_active_player(),ss.str());
		
		again = true;
		}
	else{again = false;}
	return again;
}

std::pair<bool,BitypeVar<Chesspiece*>> ClassicChess::normal_output_check(std::string in,std::string out){
	bool res;
	bool valid = this->verify_validity_input(out);
	Chesspiece* cap_piece;
	std::pair<int,int> conv;
	BitypeVar<Chesspiece*> dst;
				
	if (valid){
		bool again = false;
				
		MatPosi* mpos_out = new MatPosi(out);
		dst = this->plateau->get_piece(mpos_out->to_pair());
				
		if (dst.get_state() == true){
					
			cap_piece = dst.get_var();
						
			if (cap_piece->get_owner() == get_active_player()){ // piece de soi-meme
				
				std::stringstream ss;
				ss<<this->dico->search(this->langue,"retry")<<", "<< this->dico->search(this->langue,"cap_pe_self")<<std::endl;
				this->get_messenger()->send_msg(this->get_active_player(),ss.str());
				
				again = true;
			}
						
			else{
				// piece de l'adversaire
				// verifier que in peut faire le déplacement vers out !
				if(check_illegal_move(in,out) == true){again = true;}
			}
		}	
				
				// case vide
		else{if(check_illegal_move(in,out) == true){again = true;}} //cette notation evite la mise a false de "again"
			
		res = not(again);
	}
	else{
		res = false;
	}
	
	std::pair<bool,BitypeVar<Chesspiece*>> paire = std::make_pair(res,dst);
	return paire;
}

bool ClassicChess::verify_possible_roc(Roi* roi,Tour* tour){
	
	MatPosi mpos_roi = MatPosi(*(roi->get_posi()));
	MatPosi mpos_tour = MatPosi(*(tour->get_posi()));
	
	BitypeVar<std::pair<MatPosi*, MatPosi*>>* info = this->sort_mpos_and_calc_roc_info(&mpos_roi,&mpos_tour);
	
	return info->get_state();
	
}

Trinome<std::pair<bool,bool>,BitypeVar<Chesspiece*>,std::string>* ClassicChess::roc_first_pe_is_waiting(Chesspiece* pe){
	
	bool correspond = false;
	bool go_back = false;
	std::string out;
	BitypeVar<Chesspiece*> dst;
	std::pair<std::string,BitypeVar<Chesspiece*>> roc_paire;
	
	Roi* roi;
	Tour* tour;
	
	bool in_is_king;
	bool in_is_tour;
	
	in_is_king = verifier_type_pe<Roi>(pe);
	if (in_is_king == true){
		in_is_tour = false;
		roi = dynamic_cast<Roi*>(pe);
	}
	else{
		in_is_tour = verifier_type_pe<Tour>(pe);
		if (in_is_tour){tour = dynamic_cast<Tour*>(pe);}
		else{throw MyException(&mout,"piece roc ni roi ni tour!");}
	}
	
	while (not(correspond) and not(go_back)){
			
		roc_paire = this->in_roc_input();
		out = roc_paire.first;
		
		if (out != "ret"){
		
			dst = roc_paire.second;
			
			if (in_is_king == true){correspond = verifier_type_pe<Tour>(dst);}
			else{correspond = verifier_type_pe<Roi>(dst);}
			
			// rajouter des verifiations !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			// notamment positionnement
			
			if (correspond == true){
				
				if (in_is_king == true){tour = dynamic_cast<Tour*>(dst.get_var());}
				else{roi = dynamic_cast<Roi*>(dst.get_var());}
				
				correspond = this->verify_possible_roc(roi,tour);

				if (correspond == false){this->get_messenger()->send_msg(this->get_active_player(),"ROC IMPOSSIBLE!",true);} // <------------------------------------------------------------------------------------------ AJOUTER A DICO????
				
			}
			else{
				
				std::stringstream ss;
				
				if (in_is_tour == true){ss<<this->dico->search(this->langue,"roc_imp_chess")<<" "<<this->dico->search(this->langue,"chess_tour")<<std::endl;}
				else{ss<<this->dico->search(this->langue,"roc_imp_chess")<<" "<<this->dico->search(this->langue,"chess_roi")<<std::endl;}
				
				this->get_messenger()->send_msg(this->get_active_player(),ss.str());
				
			}
		}
		else{go_back = true;}
	}
	
	std::pair<bool,bool> state_paire = std::make_pair(go_back,correspond);
	Trinome<std::pair<bool,bool>,BitypeVar<Chesspiece*>,std::string>* res = new Trinome<std::pair<bool,bool>,BitypeVar<Chesspiece*>,std::string>(state_paire,dst,out);
	
	return res;
	
	
}

Trinome<std::pair<bool,bool>,BitypeVar<Chesspiece*>,std::string>* ClassicChess::roc_output_check(BitypeVar<Chesspiece*> in_pe){
	Chesspiece* in_piece;
	Trinome<std::pair<bool,bool>,BitypeVar<Chesspiece*>,std::string>* res;

	if (in_pe.get_state() == true){
		in_piece = in_pe.get_var();
								
		if(Roi* roi = dynamic_cast<Roi*>(in_piece)){
			res = this->roc_first_pe_is_waiting(roi);
		}
		
		else if(Tour* tour = dynamic_cast<Tour*>(in_piece)) {
			res = this->roc_first_pe_is_waiting(tour);
		}
		
		else{this->get_messenger()->send_msg(this->get_active_player(),this->dico->search(this->langue,"roc_pe_imp"),true);}
		
	}
	// else case vide (d'office non-selectionnable !)
	
	return res;
}

Trinome<std::string,BitypeVar<Chesspiece*>,std::pair<bool,bool>>* ClassicChess::out_input(std::string in, BitypeVar<Chesspiece*> in_pe){
	BitypeVar<Chesspiece*> dst;
	std::pair<int,int> conv;
	std::pair<bool,BitypeVar<Chesspiece*>> norm_paire;
	Trinome<std::pair<bool,bool>,BitypeVar<Chesspiece*>,std::string>* roc_trinome;
	
	std::string out = "";
	
	bool part_b = false;
	bool again = false;
	bool correspond = false;
	
	bool roc_accept = (verifier_type_pe<Roi>(in_pe) or verifier_type_pe<Tour>(in_pe));
	
	while (not(part_b) and not(again) and not(correspond)){
		
		std::stringstream ss_menu;

		ss_menu<<this->dico->search(this->langue,"depl_pe")<<" "<<in<<std::endl;
		ss_menu<<this->dico->search(this->langue,"ou")<<" ret "<<this->dico->search(this->langue,"ret")<<std::endl;
		if (roc_accept == true){ss_menu<<this->dico->search(this->langue,"ou")<<" roc "<<this->dico->search(this->langue,"roc")<<std::endl;}
		
		this->get_messenger()->send_msg(this->get_active_player(),ss_menu.str());
		
		out = this->get_messenger()->recieve_msg(this->get_active_player());
		
		if (out == "ret") {again = true;}
		
		else if (out == "roc"){
			if (roc_accept == true){
				roc_trinome = this->roc_output_check(in_pe);
				
				std::pair<bool,bool> state_paire = roc_trinome->get_first();
				
				again = state_paire.first;
				correspond = state_paire.second;
				
				dst = roc_trinome->get_second();
				out = roc_trinome->get_third();
			}
			else{this->get_messenger()->send_msg(this->get_active_player(),this->dico->search(this->langue,"roc_pe_imp"),true);}
		}
			
		else{
			norm_paire = this->normal_output_check(in,out);
			part_b = norm_paire.first;
			dst = norm_paire.second;
		}
	}
	std::pair<bool,bool> paire = std::make_pair(again,correspond);
	Trinome<std::string,BitypeVar<Chesspiece*>,std::pair<bool,bool>>* res = new Trinome<std::string,BitypeVar<Chesspiece*>,std::pair<bool,bool>>(out,dst,paire);
	
	return res;
}

void ClassicChess::show_depl_possibles(Chesspiece* pe){
	
	mout<<"liste deplacements : ";
	this->show_possible_mouvement(pe, "depl");
	
	mout<<"liste capture : ";
	this->show_possible_mouvement(pe, "capt");
	
}

void ClassicChess::show_depl_possibles(std::string str_co){
	BitypeVar<Chesspiece*> zone;
	Chesspiece* pe;
	
	MatPosi* mpos = new MatPosi(str_co);
	zone = this->plateau->get_piece(mpos->to_pair());
	pe = zone.get_var();
	
	this->show_depl_possibles(pe);
	
}

Trinome<std::pair<std::string,BitypeVar<Chesspiece*>>,std::pair<std::string,BitypeVar<Chesspiece*>>,bool>* ClassicChess::ask_for_input(){
	
	std::stringstream ss;
	ss<<this->get_active_player()<<" "<<this->dico->search(this->langue,"your_turn")<<"!"<<std::endl;
	this->get_messenger()->send_msg(this->get_active_player(),ss.str());
	
	Trinome<std::string,BitypeVar<Chesspiece*>,std::pair<bool,bool>>* out_p;
	std::pair<std::string,BitypeVar<Chesspiece*>> in_p;
	std::string in,out;
	
	bool again = true;
	BitypeVar<Chesspiece*> adv_pe_out;
	BitypeVar<Chesspiece*> adv_pe_in;
	std::pair<bool,bool> paire;
	bool switch_pos = false;
	
	while (again){
		in_p = this->in_depl_input();
		in = in_p.first;
		adv_pe_in = in_p.second;
		
		this->show_depl_possibles(in);
		
		out_p = this->out_input(in,adv_pe_in);
				
		out = out_p->get_first();
		adv_pe_out = out_p->get_second();
		
		paire = out_p->get_third();
		again = paire.first;
		switch_pos = paire.second;
	}
		
	std::pair<std::string,BitypeVar<Chesspiece*>> in_paire = std::make_pair(in,adv_pe_in);
	std::pair<std::string,BitypeVar<Chesspiece*>> out_paire = std::make_pair(out,adv_pe_out);
	
	Trinome<std::pair<std::string,BitypeVar<Chesspiece*>>,std::pair<std::string,BitypeVar<Chesspiece*>>,bool>* result = new Trinome<std::pair<std::string,BitypeVar<Chesspiece*>>,std::pair<std::string,BitypeVar<Chesspiece*>>,bool>(in_paire,out_paire,switch_pos);
	
	return result;
}

bool ClassicChess::verify_validity_input(std::string inp){
		
	bool res = false;
	if (isvalid_coord(inp)){
		if (this->verify_in_board(inp)){res = true;}
		else{
			std::stringstream ss_one;
			ss_one<<this->dico->search(this->langue,"retry")<<", "<< this->dico->search(this->langue,"co_ext")<<std::endl;
			this->get_messenger()->send_msg(this->get_active_player(),ss_one.str());
		}
	}
	else{
		std::stringstream ss_two;
		ss_two<<this->dico->search(this->langue,"retry")<<", "<< this->dico->search(this->langue,"co_inv")<<std::endl;
		this->get_messenger()->send_msg(this->get_active_player(),ss_two.str());
	}
	return res;
}

void ClassicChess::change_active_player(){
	if (this->get_active_player() == get_low_player()){set_active_player(get_high_player());}
	else if (this->get_active_player() == get_high_player()){set_active_player(get_low_player());}
	else{throw MyException(&mout, "probleme active player change");}
}

bool ClassicChess::verify_in_board(std::string s){
	MatPosi* mpos = new MatPosi(s);	
	return this->plateau->verify_in_board(mpos->to_pair());
}

void ClassicChess::print_mpos_vect(std::vector<MatPosi*>* vect,bool endline){ // ------------------------------------------------------ soit le rentrer dans ClassicCHess, soit lui donner un Message* en paramètre !!!!
	
	std::stringstream ss;
	
	ss<<"[";
	for(long long unsigned int i=0;i<vect->size();i++){
		
		ss<<((*vect)[i])->to_string();
		
		if (i<(vect->size()-1)){ss<<", ";}
		
	}
	ss<<"]";
	
	this->get_messenger()->send_msg(this->get_active_player(),ss.str(),endline);
		
}

void ClassicChess::print_mpos_vect(std::vector<MatPosi*>* vect){
	this->print_mpos_vect(vect,true);
	
}

BitypeVar<std::pair<MatPosi*,MatPosi*>>* ClassicChess::sort_mpos_and_calc_roc_info(MatPosi* mpos_one,MatPosi* mpos_two){
	
	std::pair<MatPosi*,MatPosi*> sorted_mpos_pair = sort_two_mpos(mpos_one, mpos_two);
	MatPosi* mpos_gauche = sorted_mpos_pair.first;
	MatPosi* mpos_droite = sorted_mpos_pair.second;

	BitypeVar<std::vector<MatPosi>*>* bit_vect = this->calculate_zones_between_zones(mpos_gauche, mpos_droite);
	
	MatPosi* mpos_roi_dst;
	MatPosi* mpos_tour_dst;
	
	bool valid_roc = false;
	
	if (bit_vect->get_state() == true){
		
		std::vector<MatPosi>* between_vect = bit_vect->get_var();
		
		// SI TOUTES LES CASES INTERMEDIARES SONT VIDES **************************************************************************************************************************************************************** !!!
		long long unsigned int i=0;
		bool stop = false;
		while (i<between_vect->size() and stop == false){
			
			if(not(this->plateau->is_empty_location(((*between_vect)[i]).to_pair()))){
				stop = true;
			};
			i++;
		}
		
		valid_roc = not(stop);
		if (valid_roc == true){
		
			BitypeVar<Chesspiece*> bit_chess_gauche = this->plateau->get_piece(mpos_gauche->to_pair());
			if (bit_chess_gauche.get_state() == false){throw MyException(&mout,"recup chesspiece de case vide");}
			
			bool gauche_isking = verifier_type_pe<Roi>(bit_chess_gauche);
			
			std::pair<int,int> coords = calc_roc_destinations(gauche_isking,between_vect);
			int co_roi_dst = coords.first;
			int co_tour_dst = coords.second;
			
			mpos_roi_dst = &((*between_vect)[co_roi_dst]);
			mpos_tour_dst = &((*between_vect)[co_tour_dst]);
			
			std::stringstream ss_gauche;
			ss_gauche<<"gauche = "<<mpos_gauche->to_string()<<", droite = "<<mpos_droite->to_string()<<std::endl;
			this->get_messenger()->send_msg(this->get_active_player(),ss_gauche.str());
			
			std::stringstream ss_droite;
			ss_droite<<"dst roi = "<<mpos_roi_dst->to_string()<<", dst tour = "<<mpos_tour_dst->to_string()<<std::endl;
			this->get_messenger()->send_msg(this->get_active_player(),ss_droite.str());
			
			// SI ROI PAS EN DANGER AVANT ROC **************************************************************************************************************************************************************** !!!
			BitypeVar<MatPosi*>* dang_roi_av;
			if (gauche_isking == true){
				dang_roi_av = this->is_endangered(mpos_gauche);
			}
			else{
				dang_roi_av = this->is_endangered(mpos_droite);
			}
			
			valid_roc = not(dang_roi_av->get_state());
			
			std::stringstream ss_roc_av;
			ss_roc_av<<"valid roc dang av"<<valid_roc<<std::endl;
			this->get_messenger()->send_msg(this->get_active_player(),ss_roc_av.str());
			
			if (valid_roc == true){
			
				// SI ROI PAS EN DANGER APRES ROC **************************************************************************************************************************************************************** !!!
				BitypeVar<MatPosi*>* dang_roi_ap = this->is_endangered(mpos_roi_dst,this->get_non_active_player());
				
				valid_roc = not(dang_roi_ap->get_state());
				
				std::stringstream ss_roc_ap;
				ss_roc_ap<<"valid roc dang ap"<<valid_roc<<std::endl;
				this->get_messenger()->send_msg(this->get_active_player(),ss_roc_ap.str());
				
				if (valid_roc == true){
				
					std::vector<MatPosi*>* king_steps_vect = calc_king_move_path((verifier_type_pe<Roi>(bit_chess_gauche) == true),co_roi_dst,between_vect);
					// SI STEPS ROI PAS EN DANGER **************************************************************************************************************************************************************** !!!
					
					long long unsigned int j=0;
					stop = false;
					while (j<king_steps_vect->size() and stop == false){
						BitypeVar<MatPosi*>* step_danger = this->is_endangered((*king_steps_vect)[j],this->get_non_active_player());
						if(step_danger->get_state() == true){
							stop = true;
						};
						
						j++;
					}
					
					valid_roc = not(stop);
					this->get_messenger()->send_msg(this->get_active_player(),"etapes rois: ");
					this->print_mpos_vect(king_steps_vect);
					
					std::stringstream ss_king_steps;
					ss_king_steps<<"valid king steps ? "<<valid_roc<<std::endl;
					this->get_messenger()->send_msg(this->get_active_player(),ss_king_steps.str(),true); // true ok car on souhaite une ligne d'espace
				}
			}
		}
	}
	else{throw MyException(&mout,"vecteur des zones entres 2 zones invalide");}
	
	BitypeVar<std::pair<MatPosi*,MatPosi*>>* res = new BitypeVar<std::pair<MatPosi*,MatPosi*>>();
	res->set_state(valid_roc);
	res->set_var(std::make_pair(mpos_roi_dst,mpos_tour_dst));
	
	return res; // retourner si roc ok (bool) et positions si ok
}

bool ClassicChess::exec_roc(MatPosi* mpos_one,MatPosi* mpos_two){
		
	BitypeVar<std::pair<MatPosi*,MatPosi*>>* info = this->sort_mpos_and_calc_roc_info(mpos_one,mpos_two);
	
	bool valid_roc = info->get_state();
	
	if (valid_roc == true){
		
		std::pair<MatPosi*,MatPosi*> dst_pair = info->get_var();
		MatPosi* mpos_roi_dst = dst_pair.first;
		MatPosi* mpos_tour_dst = dst_pair.second;
		
		bool one_isking = verifier_type_pe<Roi>(this->plateau->get_piece(mpos_one->to_pair()));
		
		MatPosi* mpos_roi_ini;
		MatPosi* mpos_tour_ini;
		
		if (one_isking == true){
			mpos_roi_ini = mpos_one;
			mpos_tour_ini = mpos_two;
		}
		
		else{
			mpos_roi_ini = mpos_two;
			mpos_tour_ini = mpos_one;
		}
	
		// deplacement des pieces:
		//rois --> dest tour et tour --> dest roi pois switch position (fait ce cette façon pour pouvoir plustard faire une sort de cinematique/ monterr visulemment l'inversion de place)
		this->exec_move(mpos_roi_ini, mpos_tour_dst);
		this->exec_move(mpos_tour_ini, mpos_roi_dst);
		
		this->plateau->switch_positions(mpos_roi_dst->to_pair(),mpos_tour_dst->to_pair());
	}
	
	return valid_roc;
	
}

void ClassicChess::exec_move(MatPosi* mpos_in, MatPosi* mpos_out, bool switch_mode){

	std::pair<int,int> pair_in = mpos_in->to_pair();
	std::pair<int,int> pair_out = mpos_out->to_pair();
	
	if (switch_mode == false){this->plateau->move(pair_in,pair_out);}
	else{
		
		//avant this->plateau->switch_positions(inp_in,inp_out);
		this->exec_roc(mpos_in,mpos_out);
	
	}
}

void ClassicChess::exec_move(MatPosi* mpos_in, MatPosi* mpos_out){
	this->exec_move(mpos_in, mpos_out, false);
}

void ClassicChess::exec_move(std::string str_in, std::string str_out, bool switch_mode){
	
	MatPosi* mpos_in = new MatPosi(str_in);
	MatPosi* mpos_out = new MatPosi(str_out);
	
	this->exec_move(mpos_in, mpos_out, switch_mode);
}

void ClassicChess::exec_move(std::string str_in, std::string str_out){	
	this->exec_move(str_in, str_out, false);
}

void ClassicChess::exec_move(std::pair<int,int> pair_in, std::pair<int,int> pair_out, bool switch_mode){
	
	MatPosi* mpos_in = new MatPosi(pair_in);
	MatPosi* mpos_out = new MatPosi(pair_out);
	
	this->exec_move(mpos_in, mpos_out, switch_mode);
}

void ClassicChess::exec_move(std::pair<int,int> pair_in, std::pair<int,int> pair_out){
	this->exec_move(pair_in, pair_out, false);
}


bool ClassicChess::verify_move(std::string in, std::string out){
	return this->verify_move(in, out, "");
}

bool ClassicChess::verify_move(std::string in, std::string out, std::string mode){
	
	MatPosi* mpos_in = new MatPosi(in);
	MatPosi* mpos_out = new MatPosi(out);
	
	return this->verify_move(mpos_in, mpos_out, mode);
}

bool ClassicChess::verify_move(std::pair<int,int> in, std::pair<int,int> out){
	return this->verify_move(in, out, "");
}

bool ClassicChess::verify_move(std::pair<int,int> in, std::pair<int,int> out, std::string mode){
	
	MatPosi* mpos_in = new MatPosi(in);
	MatPosi* mpos_out = new MatPosi(out);
	
	return this->verify_move(mpos_in, mpos_out, mode);
}

bool ClassicChess::verify_move(MatPosi* in, MatPosi* out){
	return this->verify_move(in, out, "");
}

bool ClassicChess::verify_move(MatPosi* in, MatPosi* out, std::string mode){
	BitypeVar<Chesspiece*> bi_t_in = this->plateau->get_piece(in->to_pair());
	BitypeVar<Chesspiece*> bi_t_out = this->plateau->get_piece(out->to_pair());
	
	bool res = false;	
	if (bi_t_in.get_state() == true){
		
		Chesspiece* pe = bi_t_in.get_var();
		
		mode = adaptive_mode(bi_t_out,mode);
		
		std::vector<MatPosi*>* sol = this->check_possible_mouvement(pe, mode);
		
		long long unsigned int i=0;
		while (i<sol->size() and res == false){
			MatPosi* elem = (*sol)[i];
			if (*elem == *out){res = true;}
			
			i++;
		}
	}
	return res;
}

std::vector<MatPosi*>* ClassicChess::check_possible_mouvement(Chesspiece* pe ,std::string mode){
	
	std::vector<std::pair<std::pair<int,int>,AdvTuple>> vect = pe->algo(mode);
	Posi* origin = pe->get_posi();
	
	std::vector<MatPosi*>* res = new std::vector<MatPosi*>();
	
	MatPosi* elem;
	bool keep;
	
	MatPosi* mposi_origi = new MatPosi(*origin);
	std::pair<int,int> paire_origi = mposi_origi->to_pair();
	
	for(long long unsigned int i=0;i<vect.size();i++){
		
		elem = new MatPosi(vect[i].first);
		AdvTuple adv_tup = vect[i].second;
		std::pair<int,int> paire = elem->to_pair();

		keep = this->en_danger(paire_origi, adv_tup, paire, mode);
		
		if (keep == true){
			res->push_back(elem);
		}
	}
	
	return res;
}

BitypeVar<AdvTuple*>* ClassicChess::find_linking_advtuple(std::pair<int,int> pair_in, std::pair<int,int> pair_out, std::string mode){
	BitypeVar<AdvTuple*>* found;
	BitypeVar<Chesspiece*> tup_in = this->plateau->get_piece(pair_in);
	
	if (tup_in.get_state() == true){
		Chesspiece* pe_in = tup_in.get_var();
		
		MatPosi* mpos_out = new MatPosi(pair_out);
		
		std::vector<std::pair<std::pair<int,int>,AdvTuple>> vect = pe_in->algo(mode);
		
		found = new BitypeVar<AdvTuple*>();
		found->set_state(false);
		
		long long unsigned int i=0;
		while(i<vect.size() and (found->get_state() == false)){
			MatPosi* mpos_elem = new MatPosi(vect[i].first);
			
			if (*mpos_elem == *mpos_out){
				found->set_var(&(vect[i].second));
				found->set_state(true);
			}
			
			i++;
		}
	}
	else{throw MyException(&mout, "demande de find_linking_advtuple() sur case vide en entree !");}
	
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! plusieuers Advtuples sont possible !!!! A ADAPTER (ou considerer qu'un seul suffit)!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	return found;
}

bool ClassicChess::complete_danger_test(std::pair<int,int> pair_in, std::pair<int,int> pair_out, std::string mode){
	bool keep = false;
	BitypeVar<AdvTuple*>* bit_var = this->find_linking_advtuple(pair_in, pair_out, mode);
	
	//mout << "link advt"<<*bit_var<<std::endl;

	if (bit_var->get_state() == true){
		AdvTuple adv_tup = *(bit_var->get_var());
		keep = this->en_danger(pair_in, adv_tup, pair_out, mode);
		//mout << "result keep"<<keep<<std::endl;
	}
	
	return keep;
	
}

bool in_vect(std::vector<std::string>* vect, std::string elem){
	bool res = false;
	
	long long unsigned int i=0;
	while(i<vect->size() and res == false){
		
		if ((*vect)[i] == elem){res = true;}
		
		i++;
		}
	return res;
	
}

void ClassicChess::show_possible_mouvement(Chesspiece* pe ,std::string mode){
	
	std::vector<MatPosi*>* vect = this->check_possible_mouvement(pe, mode);
	
	std::vector<std::string>* stock = new std::vector<std::string>();
	
	std::stringstream ss;
	
	ss<<"[";
	for(long long unsigned int i=0;i<vect->size();i++){
		std::string temp = (*vect)[i]->to_string();
		if (not(in_vect(stock,temp))){
			if (i != 0){ss<<", ";}
			ss<<temp;
			stock->push_back(temp);
		}
	}
	ss<<"]";
	
	this->get_messenger()->send_msg(this->get_active_player(),ss.str(),true);
}

void ClassicChess::affichage(){
	
	std::stringstream ss;
	
	ss<<std::endl;
	ss<<"["<<this->get_high_player()<<"]"<<std::endl;
	ss<<std::endl;
	
	ss<<(this->plateau->adaptive_affichage("Symbole_","",this->dico,this->langue)).str()<<std::endl;
	
	ss<<std::endl;
	ss<<"["<<this->get_low_player()<<"]"<<std::endl;
	
	this->get_messenger()->send_msg(this->get_active_player(),ss.str(),true);
}

void ClassicChess::execute(){
	bool end = false;
	Trinome<std::pair<std::string,BitypeVar<Chesspiece*>>,std::pair<std::string,BitypeVar<Chesspiece*>>,bool>* coords;
	
	std::pair<std::string,BitypeVar<Chesspiece*>> in_couple,out_couple;
	bool switch_pos;
	
	std::string in,out;
	BitypeVar<Chesspiece*> adv_pe_in;
	BitypeVar<Chesspiece*> adv_pe_out;
	
	this->affichage();
	
	while (not(end)){

		coords = this->ask_for_input();
		in_couple = coords->get_first();
		in = in_couple.first;
		adv_pe_in = in_couple.second;
		
		
		out_couple = coords->get_second();
		out = out_couple.first;
		adv_pe_out = out_couple.second;
		
		switch_pos = coords->get_third();
		
		end = check_end_game(adv_pe_out, switch_pos);
		
		// ici on suppose que input correcte puisque apres les verification
		this->exec_move(in,out,switch_pos);
		
		this->check_evolution();
		
		if (not(end)){end = this->verify_kings();}
		else{this->get_messenger()->send_msg(this->get_active_player(),this->dico->search(this->langue,"mode_echec_et_mat"),true);} // si arret par consequences automatiquement echec et mat (pas possible de pat)
		
		this->affichage();
		
		if (not end){this->change_active_player();}
		else{
			
			std::stringstream ss;
			
			ss<<this->dico->search(this->langue,"vict")<<" "<<get_active_player()<<" !"<<std::endl;
			ss<<this->dico->search(this->langue,"fin_match")<<"!"<<std::endl;
			
			this->get_messenger()->send_msg(this->get_active_player(),ss.str());
		}
	}
}

Chesspiece* ClassicChess::ask_evolution_imput(std::vector<Chesspiece*>* vect){
	Chesspiece* res;
	bool found = false;
	std::string in;
	while (found == false){
		
		std::stringstream deb_ss;
		
		deb_ss<<this->dico->search(this->langue,"choix_evolve")<<": ";
		for(long long unsigned int i=0;i<vect->size();i++){
			
			std::stringstream temp_ss;
			temp_ss<<"Nom_"<<*((*vect)[i]);

			deb_ss<<this->dico->search(this->langue,temp_ss.str());
			
			if (i < vect->size()-2){deb_ss<<", ";}
			else if (i == vect->size()-2){deb_ss<<" "<<this->dico->search(this->langue,"et")<<" ";}
			else if (i == vect->size()-1){deb_ss<<std::endl;}
		
		}
		
		this->get_messenger()->send_msg(this->get_active_player(),deb_ss.str());
		
		in = this->get_messenger()->recieve_msg(this->get_active_player());
		
		std::stringstream end_ss;
		
		long long unsigned int j=0;
		while ((found == false) and (j<vect->size())){
		
			std::stringstream ss;
			ss<<"Nom_"<<*((*vect)[j]);
			
			end_ss<<in<<"VS"<<this->dico->search(this->langue,ss.str())<<std::endl;
			if (in == this->dico->search(this->langue,ss.str())){
				found = true;
				res = (*vect)[j];
			}
			
			j++;
		}
		if (found == false){end_ss<<this->dico->search(this->langue,"retry")<<std::endl;}
		
		this->get_messenger()->send_msg(this->get_active_player(),end_ss.str());
		
	}
	return res;
}

void ClassicChess::check_evolution(){
	
	std::stringstream ss;
	
	ss<<"debut check_evolution() !"<<std::endl;
	int num_row = this->get_player_row(this->get_non_active_player());
	std::vector<BitypeVar<Chesspiece*>> lig = this->plateau->get_row(num_row);
	
	this->show_bitype_vect(lig);

	BitypeVar<int>* rep = detect_ennemy_pion_in_vect(lig, this->get_active_player());
	
	ss<<"etat lig "<<rep->get_state()<<std::endl;
	if (rep->get_state() == true){
		// evolve
		int num_col = rep->get_var();
		ss<<"indice lig "<<num_col<<std::endl;
		
		std::pair<int,int> paire = std::make_pair(num_col,num_row);
		
		Tour* tour = new Tour();
		Fous* fous = new Fous();
		Chevalier* chevalier = new Chevalier();
		Dame* dame = new Dame();
		
		std::vector<Chesspiece*>* chess_vect = new std::vector<Chesspiece*>();
		chess_vect->push_back(tour);
		chess_vect->push_back(fous);
		chess_vect->push_back(chevalier);
		chess_vect->push_back(dame);
		
		Chesspiece* nv_pe = ask_evolution_imput(chess_vect);
		
		nv_pe->set_owner(this->get_active_player());
		this->plateau->set_piece(paire,nv_pe);
		
	}
	
	ss<<"fin check_evolution() !"<<std::endl;
	
	this->get_messenger()->send_msg(this->get_active_player(),ss.str());
	
}

bool ClassicChess::can_escape_position(Chesspiece* pe ,std::string mode){
	bool escape = false;
	
	std::vector<MatPosi*>* vect = this->check_possible_mouvement(pe ,mode);
		
	long long unsigned int i=0;
	while(i<vect->size() and escape == false){
		MatPosi* mpos = (*vect)[i];
		//mout<<"cheking "<<mpos->to_string()<<std::endl;
		escape = not(this->is_endangered(mpos,this->get_other_player(pe->get_owner()))->get_state());
		//mout<<"reponce "<<escape<<std::endl;
		i++;
	}
	
	return escape;
}

bool ClassicChess::check_more_than_one_danger(MatPosi* mpos_zone){
	
	Human* player = new Human("");
	
	return this->check_more_than_one_danger(mpos_zone, player);
}

bool ClassicChess::check_more_than_one_danger(MatPosi* mpos_zone, Player* limitator){
	// !! plus ou moins copie colle de is_endangered
	
	int taille = this->plateau->get_taille();
	std::pair<int,int> paire_zone = mpos_zone->to_pair();
	
	std::string mode;
	if (this->plateau->is_empty_location(paire_zone)){mode = "depl";}
	else {mode = "capt";}
	
	int count = 0;
	int lig = 0;
	while(lig<taille and count < 2){ // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! (plustard iterateur iterator(plateau))
		int col=0;
		while(col<taille and count < 2){			
			MatPosi* mpos = new MatPosi(col,lig);
			std::pair<int,int> paire = mpos->to_pair();
			
			if (not(this->plateau->is_empty_location(paire))){				
				if ((limitator->get_name() == "") or ((limitator->get_name() != "") and (limitator == this->plateau->get_piece(paire).get_var()->get_owner()))){
					bool compl_danger = this->complete_danger_test(paire,paire_zone,mode);
					if (compl_danger == true){count +=1;}
				}
			}
			col++;
		}
		lig++;
	}
	return (count >= 2);
}

std::vector<MatPosi*>* ClassicChess::get_zones_between(std::pair<int,int> begin, std::pair<int,int> end, std::string mode){
	// plus ou moins copier coller de check_between
	
	std::vector<MatPosi*>* res = new std::vector<MatPosi*>();
	
	BitypeVar<AdvTuple*>* bit_adv = find_linking_advtuple(begin,end,mode);
	
	if (bit_adv->get_state() == true){
		
		AdvTuple* adv_tup = bit_adv->get_var();
			
		MatPosi* mposi_origi = new MatPosi(begin);
		MatPosi* mposi_end = new MatPosi(end);
		
		int limite = this->plateau->get_taille();
			
		if (adv_tup->get_depl_type() == "translation"){
			std::vector<std::pair<int,int>>* temp_vect = adv_tup->get_res(limite,*mposi_origi);
			// get_res donnes toutes les positions sauf position actuelle!
			
			long long unsigned int j=0;
			
			bool between;
			while (j<temp_vect->size()){
				MatPosi* mposi = new MatPosi((*temp_vect)[j]);
				
				if (*mposi_end > *mposi_origi){
					between = (*mposi > *mposi_origi) and (*mposi < *mposi_end);
				}
				else if (*mposi_end < *mposi_origi){
					between = (*mposi < *mposi_origi) and (*mposi > *mposi_end);
				}
				else{throw MyException(&mout, "deplacement immobile impossible");}
				
				if (between == true){res->push_back(mposi);}

				j++;
			}
		}
		else if (adv_tup->get_depl_type() != "saut"){throw MyException(&mout, "type deplacement inconnu");}
	}
	else{throw MyException(&mout,"mouvement impossible netre ces 2 positions!!!");}
	
	return res;		
}

bool ClassicChess::check_non_active_player_king(Chesspiece* pe){
	
	std::stringstream ss;
	
	bool mode_echec_et_mat = false;
	
	Posi* position = pe->get_posi();
	MatPosi* mpos = new MatPosi(*position);
	
	BitypeVar<MatPosi*>* danger_res =  this->is_endangered(mpos);
	bool mode_echec = danger_res->get_state();
	MatPosi* mpos_menace = danger_res->get_var();
	
	ss << mpos->to_string()<<" is in danger?: "<< mode_echec <<std::endl;
	
	//--
	bool escape = false;
	if (mode_echec == true){ // deteter aussi le PAT !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! si roi est seul piece restante du jouer et qu'il ne peut plus bouger --> pat !!!!!!!!!!!!!!!!!!!!!!!!
		//(sauf roc car si echec --> roc pas permis sinon inutile a verifier car roc ne peut pas empecher echec ou echec et mat (voir regles))
		
		escape = this->can_escape_position(pe ,"depl");
		
		if (not(escape)){escape = this->can_escape_position(pe ,"capt");}
		ss<<"depl_esacpe? "<<escape<<std::endl;
		if (not(escape)){
			
			if(this->check_more_than_one_danger(mpos)){
				mode_echec_et_mat = true;
			}
			else{ // 1 seul danger
				BitypeVar<MatPosi*>* dangerception = this->is_endangered(mpos_menace);
				bool danger_indanger = dangerception->get_state();
				
				if(danger_indanger == true){
					
					bool danger_two_dangers = this->check_more_than_one_danger(mpos_menace);
					
					if (not(danger_two_dangers)){
						MatPosi* dangerception_mpos = dangerception->get_var();
						
						BitypeVar<Chesspiece*> danger_bity = this->plateau->get_piece(dangerception_mpos->to_pair());
						
						//impossible que ce soit le roi (déjà geré dans can_escape !!!
						
						// menace peut être prise --> pas echec et mat !!!!						
							
					}
					else{mode_echec_et_mat = true;}
					
				}
				else{
					//allie peut-il s'interposer?
					bool blocked = false;
					
					std::vector<MatPosi*>* zones_between_vect = this->get_zones_between(mpos_menace->to_pair(), mpos->to_pair(), "capt");
					long long unsigned int i=0;
					while(i<zones_between_vect->size() and not(blocked)){
						
						MatPosi* mpos_zone = (*zones_between_vect)[i];
						
						BitypeVar<MatPosi*>* dangerzone = this->is_endangered(mpos_zone,this->get_non_active_player());
						blocked = dangerzone->get_state();
					
						i++;
					}
					
					ss<<"une pe peut-elle bloquer la menace? "<<blocked<<std::endl;
					
					if (not(blocked)){mode_echec_et_mat = true;}
				}
			}
		}
		//else{mode_echec_et_mat = false;}
		
		if (not(mode_echec_et_mat)){ss<<this->dico->search(this->langue,"mode_echec")<<std::endl;}
		else{ss<<this->dico->search(this->langue,"mode_echec_et_mat")<<std::endl;}
	}
	
	this->get_messenger()->send_msg(this->get_active_player(),ss.str());
	
	return mode_echec_et_mat;
	
}

bool ClassicChess::verify_kings(){
	
	std::vector<Chesspiece*>* vect = this->get_kings();
	Chesspiece* pe;
	this->get_messenger()->send_msg(this->get_active_player(),"DEB VERIFY KINGS:",true);
	
	bool mode_echec_et_mat = false;
	bool act_found = false;
	bool non_act_found = false;
	
	//MatPosi* mpos_echec;
	
	Chesspiece* active_player_king;
	Chesspiece* non_active_player_king;
	
	long long unsigned int i=0;
	while(i<vect->size() and (not(act_found) or not(non_act_found))){ // 1 seul roi a trouver
		pe = (*vect)[i];
		
		if (pe->get_owner() == this->get_non_active_player()){
			non_active_player_king = pe;
			non_act_found = true;
		}
			
		else if (pe->get_owner() == this->get_active_player()){
			active_player_king = pe;
			act_found = true;
		}
		
		i++;
	}

	if (not(act_found) or not(non_act_found)){throw MyException(&mout,"deux Roi non trouves!");}
	
	//mout << "en echec?"<<mode_echec<<std::endl;
	//mout << "en echec et mat?"<<mode_echec_et_mat<<std::endl;
	
	MatPosi* vict_mpos = new MatPosi(*(active_player_king->get_posi()));
	BitypeVar<MatPosi*>* vict = this->is_endangered(vict_mpos);
	
	bool victory = vict->get_state();
	
	if (not(victory)){
		mode_echec_et_mat = this->check_non_active_player_king(non_active_player_king);
	}
	else{
		std::stringstream ss;
		ss<<this->dico->search(this->langue,"vict")<<" "<<get_non_active_player()<<" ! (previson avant le deplacement reel)"<<std::endl;
		this->get_messenger()->send_msg(this->get_active_player(),ss.str());
	}
	
	this->get_messenger()->send_msg(this->get_active_player(),"FIN VERIFY KINGS:",true);
	
	return mode_echec_et_mat;
	
}

std::vector<Chesspiece*>* ClassicChess::get_kings(){
	
	// le serveur manipule un plateau,
	// le plateau ne doit pas connaitre ce qu'il contient pour exister
	
	int taille = this->plateau->get_taille();
	std::vector<Chesspiece*>* res = new std::vector<Chesspiece*>();
	
	for(int lig=0;lig<taille;lig++){ // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! (plustard iterateur iterator(plateau))
		for(int col=0;col<taille;col++){
			
			MatPosi* mposi = new MatPosi(col,lig);
			BitypeVar<Chesspiece*> dst = this->plateau->get_piece(mposi->to_pair());
			
			if (verifier_type_pe<Roi>(dst) == true){
				res->push_back(dst.get_var());
			}
		}
	}
	return res;
}

BitypeVar<MatPosi*>* ClassicChess::is_endangered(MatPosi* mpos_zone, Player* limitator){ // pe owner
	
	int taille = this->plateau->get_taille();
	BitypeVar<MatPosi*>* danger = new BitypeVar<MatPosi*>();
	
	std::pair<int,int> paire_zone = mpos_zone->to_pair();
	
	std::string mode;
	if (this->plateau->is_empty_location(paire_zone)){mode = "depl";}
	else {mode = "capt";}
	
	int lig = 0;
	while(lig<taille and danger->get_state() == false){ // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! (plustard iterateur iterator(plateau))
		int col=0;
		while(col<taille and danger->get_state() == false){			
			MatPosi* mpos = new MatPosi(col,lig);
			
			std::pair<int,int> paire = mpos->to_pair();
			
			if (not(this->plateau->is_empty_location(paire))){
				if ((limitator->get_name() == "") or ((limitator->get_name() != "") and (limitator == this->plateau->get_piece(paire).get_var()->get_owner()))){ // pe owner
					bool compl_danger = this->complete_danger_test(paire,paire_zone,mode);
					danger->set_state(compl_danger);
					danger->set_var(mpos);
				}
			}
			col++;
		}
		lig++;
	}
	return danger;
	
}

BitypeVar<MatPosi*>* ClassicChess::is_endangered(MatPosi* mpos_zone){
	
	Human* player = new Human("");
	
	return this->is_endangered(mpos_zone,player);
}

bool ClassicChess::en_danger(std::pair<int,int> paire_origi, AdvTuple adv_tup, std::pair<int,int> paire, std::string mode){
	bool keep = false;
	bool valid;
	std::pair<bool,std::string> ins_p;
	
	ins_p = this->plateau->isvalid_move(paire_origi, paire, mode);
	valid = ins_p.first;
	
	//mout << "valid"<<valid<<std::endl;
	
	if(valid == true){		
		keep = this->check_between(paire_origi, adv_tup, paire);
		//mout << "bewteen"<<keep<<std::endl;
	}
	//else{keep = false;}
	
	return keep;
	
}

bool ClassicChess::check_between(std::pair<int,int> begin, AdvTuple adv_tup, std::pair<int,int> end){
	
	bool keep = true;
	
	MatPosi* mposi_origi = new MatPosi(begin);
	MatPosi* mposi_end = new MatPosi(end);
	
	int limite = this->plateau->get_taille();
		
	if (adv_tup.get_depl_type() == "translation"){
		std::vector<std::pair<int,int>>* temp_vect = adv_tup.get_res(limite,*mposi_origi);
		// get_res donnes toutes les positions sauf position actuelle!
		
		bool stop = false;
		long long unsigned int j=0;
		
		while (j<temp_vect->size() and stop == false){
			MatPosi* mposi = new MatPosi((*temp_vect)[j]);
			std::pair<int,int> paire_norm = std::make_pair(mposi->get_col(),mposi->get_lig());
			
			bool between;
			if (*mposi_end > *mposi_origi){
				between = (*mposi > *mposi_origi) and (*mposi < *mposi_end);
			}
			else if (*mposi_end < *mposi_origi){
				between = (*mposi < *mposi_origi) and (*mposi > *mposi_end);
			}
			else{throw MyException(&mout, "deplacement immobile impossible");}
			
			
			if (between == true){stop = not(this->plateau->is_empty_location(paire_norm));}

			j++;
		}
		keep = not(stop);
	}
	
	else if (adv_tup.get_depl_type() != "saut"){throw MyException(&mout, "type deplacement inconnu");}
	
	return keep;	
}
