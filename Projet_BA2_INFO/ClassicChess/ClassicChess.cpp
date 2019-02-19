
#include "ClassicChess.hpp"

extern MyOstream mout;

//--------------------ClassicChess----------------------------------------------------------------------------------------------------

ClassicChess::ClassicChess(Player* p_low, Player* p_high, Dico* dict, std::string lang) : BaseChess(p_low,p_high,dict,lang){
	this->initialisation();
} //*< Constructor


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
		
	//ligne 8
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
	
	//ligne 7
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

std::string ClassicChess::affichage_plateau(){
	
	return (this->get_plateau()->adaptive_affichage("Symbole_","",this->get_dico(),this->get_langue())).str();
	
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
		dst = this->get_plateau()->get_piece(mpos_out->to_pair());
				
		if (dst.get_state() == true){
					
			cap_piece = dst.get_var();
						
			if (cap_piece->get_owner() == get_active_player()){ // piece de soi-meme
				
				std::stringstream ss;
				ss<<this->get_dico()->search(this->get_langue(),"retry")<<", "<< this->get_dico()->search(this->get_langue(),"cap_pe_self")<<std::endl;
				this->get_active_player()->send_msg(ss.str());
				
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

Trinome<std::string,BitypeVar<Chesspiece*>,Trinome<bool,bool,bool>*>* ClassicChess::out_input(std::string in, BitypeVar<Chesspiece*> in_pe){
	BitypeVar<Chesspiece*> dst;
	std::pair<int,int> conv;
	std::pair<bool,BitypeVar<Chesspiece*>> norm_paire;
	
	std::string out = "";
	
	bool part_b = false;
	bool again = false;
	bool correspond = false;
	bool found;
	
	bool roc_accept = (verifier_type_pe<Roi>(in_pe) or verifier_type_pe<Tour>(in_pe));
		
	bool end_game = false;
	while (not(part_b) and not(again) and not(correspond) and not(end_game)){
		
		std::stringstream ss_menu;
		ss_menu<<this->get_dico()->search(this->get_langue(),"depl_pe")<<" "<<in<<std::endl;
		ss_menu<<this->get_dico()->search(this->get_langue(),"ou")<<" ret "<<this->get_dico()->search(this->get_langue(),"ret")<<std::endl;
		if (roc_accept == true){ss_menu<<this->get_dico()->search(this->get_langue(),"ou")<<" roc "<<this->get_dico()->search(this->get_langue(),"roc")<<std::endl;}
		ss_menu<<this->get_dico()->search(this->get_langue(),"ou")<<" end "<<this->get_dico()->search(this->get_langue(),"end")<<std::endl;
		ss_menu<<this->get_dico()->search(this->get_langue(),"ou")<<" liste_depl "<<this->get_dico()->search(this->get_langue(),"liste_depl")<<std::endl;
		ss_menu<<this->get_dico()->search(this->get_langue(),"ou")<<" liste_capt "<<this->get_dico()->search(this->get_langue(),"liste_capt")<<std::endl;
		ss_menu<<this->get_dico()->search(this->get_langue(),"ou")<<" lang "<<this->get_dico()->search(this->get_langue(),"lang")<<std::endl;
		
		this->get_active_player()->send_msg(ss_menu.str());
		
		out = this->get_active_player()->recieve_msg();
		
		
		Trinome<Quadrinome<bool,bool,bool,bool>*, BitypeVar<Chesspiece*>, std::string > symbol_info = this->check_out_for_special_symbol(in_pe, out, roc_accept);
		
		Quadrinome<bool,bool,bool,bool>* symbol_bool_info = symbol_info.get_first();
		
		found = symbol_bool_info->get_first();
		
		if (found){
			
			dst = symbol_info.get_second();
			out = symbol_info.get_third();
			
			again = symbol_bool_info->get_second();
			correspond = symbol_bool_info->get_third();
			end_game = symbol_bool_info->get_fourth();
			
		}
		else{
			norm_paire = this->normal_output_check(in,out);
			part_b = norm_paire.first;
			dst = norm_paire.second;
		}
	}

	Trinome<bool,bool,bool>* trinome_bool_res = new Trinome<bool,bool,bool>(again,correspond,end_game);
	Trinome<std::string,BitypeVar<Chesspiece*>,Trinome<bool,bool,bool>*>* res = new Trinome<std::string,BitypeVar<Chesspiece*>,Trinome<bool,bool,bool>*>(out,dst,trinome_bool_res);
	
	return res;
}

void ClassicChess::execute(){
	bool end = false;
	Trinome<std::pair<std::string,BitypeVar<Chesspiece*>>,std::pair<std::string,BitypeVar<Chesspiece*>>,std::pair<bool,bool>>* coords;
	
	std::pair<std::string,BitypeVar<Chesspiece*>> in_couple,out_couple;
	bool switch_pos;
	
	std::string in,out;
	BitypeVar<Chesspiece*> adv_pe_in;
	BitypeVar<Chesspiece*> adv_pe_out;
	
	std::pair<bool,bool> bool_info;
	
	this->affichage();
	
	bool abandon = false;
	
	while (not(end)and not abandon){
		coords = this->ask_for_input();
		in_couple = coords->get_first();
		in = in_couple.first;
		adv_pe_in = in_couple.second;
		
		
		out_couple = coords->get_second();
		out = out_couple.first;
		adv_pe_out = out_couple.second;
		
		bool_info = coords->get_third();
		
		abandon = bool_info.first;
		switch_pos = bool_info.second;
		
		if (not abandon){
			end = check_end_game(adv_pe_out, switch_pos);
		
			// ici on suppose que input correcte puisque apres les verification
			this->exec_move(in,out,switch_pos);
		}
		
		this->check_evolution();
		
		if (not(end)){end = this->verify_kings();}
		else{this->get_active_player()->send_msg(this->get_dico()->search(this->get_langue(),"mode_echec_et_mat"),true);} // si arret par consequences automatiquement echec et mat (pas possible de pat)
		
		this->affichage();
		
		if (not end and not abandon){this->change_active_player();}
		else{
			
			if (abandon == true){this->change_active_player();}
			
			std::stringstream ss;
			
			ss<<this->get_dico()->search(this->get_langue(),"vict")<<" "<<get_active_player()<<" !"<<std::endl;
			ss<<this->get_dico()->search(this->get_langue(),"fin_match")<<"!"<<std::endl;
			
			this->get_active_player()->send_msg(ss.str());
		}
	}
}
