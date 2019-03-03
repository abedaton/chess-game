
#include "ClassicChess.hpp"
#include <sstream>

extern MyOstream mout;

//MyOstream mout("logfile.txt"); // ???

//--------------------ClassicChess----------------------------------------------------------------------------------------------------

bool ClassicChess::check_pat(){
	int taille = this->get_plateau()->get_taille();
		
	bool escape = false;
		
	int lig = 0;
	while(lig<taille and not escape){ // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! (plustard iterateur iterator(plateau))
		int col=0;
		while(col<taille and not escape){			
			MatPosi* mpos = new MatPosi(col,lig);
			std::pair<int,int> paire = mpos->to_pair();
			
			if (not(this->get_plateau()->is_empty_location(paire))){
				Chesspiece* pe = this->get_plateau()->get_piece(paire).get_var();
				if (this->get_active_player() == pe->get_owner()){
					
					escape = this->can_escape_position(pe ,"depl");
					if (not(escape)){escape = this->can_escape_position(pe ,"capt");}
					
				}
			}
		}
	}
	//mout << "		EN ECHEC ET MAT ?" << escape <<std::endl;
	return escape;
}

ClassicChess::ClassicChess(Player* p_low, Player* p_high,Player* deb_player, Dico* dict) : BaseChess(p_low,p_high,deb_player,dict){
	
	if((deb_player != p_low) and (deb_player != p_high)){throw MyException(&mout,"joueur devant commencé inconnnu!");}
	
	this->initialisation();
} //*< Constructor


void ClassicChess::initialise_board(){	
	Plateau* plat = new Plateau(8);
	this->set_plateau(plat);
	
}

void ClassicChess::initialise_low_pieces(){ 
	/* mise en place des pieces pour le joeur se trouvant en bas du tableau */

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
	/* mise en place des pieces pour le joeur se trouvant en haut du tableau */

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

void ClassicChess::affichage(){
	/* fonction affaichant le tableau de jeu ainsi que les joueurs l'entourant */
	
	Affichage* aff = new Affichage(this->get_plateau(), this->get_dico(),"Symbole_","",this->get_active_player()->get_langue(),this->get_low_player(), this->get_high_player(),"*" ,"");
	this->get_active_player()->send_msg(aff->get_affichage(),true);
}

std::pair<bool,BitypeVar<Chesspiece*>> ClassicChess::normal_output_check(std::string in,std::string out){
	/* normal en oposition avec roc_output_check,
	 * output designe la 2e partie de la selectiond de piece c.a.d. le choix de la destination de la piecesélectionné */
	
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
				ss<<this->get_dico()->search(this->get_active_player()->get_langue(),"retry")<<", "<< this->get_dico()->search(this->get_active_player()->get_langue(),"cap_pe_self")<<std::endl;
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
	
	/* out designe la 2e partie de la selectiond de piece c.a.d. le choix de la destination de la piece sélectionné (en in)
	 * boucle while gèrant toutes les possibilités concernat ce choix de destination*/
	
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
		ss_menu<<this->get_dico()->search(this->get_active_player()->get_langue(),"depl_pe")<<" "<<in<<std::endl;
		ss_menu<<this->get_dico()->search(this->get_active_player()->get_langue(),"ou")<<" "<<this->get_ret_symbol()<<" "<<this->get_dico()->search(this->get_active_player()->get_langue(),this->get_ret_symbol())<<std::endl;
		if (roc_accept == true){ss_menu<<this->get_dico()->search(this->get_active_player()->get_langue(),"ou")<<" "<<this->get_roc_symbol()<<" "<<this->get_dico()->search(this->get_active_player()->get_langue(),this->get_roc_symbol())<<std::endl;}
		ss_menu<<this->get_dico()->search(this->get_active_player()->get_langue(),"ou")<<" "<<this->get_end_symbol()<<" "<<this->get_dico()->search(this->get_active_player()->get_langue(),this->get_end_symbol())<<std::endl;
		ss_menu<<this->get_dico()->search(this->get_active_player()->get_langue(),"ou")<<" "<<this->get_liste_depl_symbol()<<" "<<this->get_dico()->search(this->get_active_player()->get_langue(),this->get_liste_depl_symbol())<<std::endl;
		ss_menu<<this->get_dico()->search(this->get_active_player()->get_langue(),"ou")<<" "<<this->get_liste_capt_symbol()<<" "<<this->get_dico()->search(this->get_active_player()->get_langue(),this->get_liste_capt_symbol())<<std::endl;
		ss_menu<<this->get_dico()->search(this->get_active_player()->get_langue(),"ou")<<" "<<this->get_lang_symbol()<<" "<<this->get_dico()->search(this->get_active_player()->get_langue(),this->get_lang_symbol())<<std::endl;
		
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

Trinome<std::string,std::string,bool>* ClassicChess::decode_merged_string(std::string merged_string){
	
	Trinome<std::string,std::string,bool>* res_trinome = new Trinome<std::string,std::string,bool>();
	
	std::vector<std::string>* res_vect = split_string(merged_string,";");
	
	std::string in,out;
	bool switch_pos = false;
	
	if (res_vect->size() == 2){
		
		in = (*res_vect)[0];
		out = (*res_vect)[1];
	}
	
	else if (res_vect->size() == 3){
		
		in = (*res_vect)[0];
		out = (*res_vect)[2];
		
		if ((*res_vect)[1] != this->get_roc_symbol()){throw MyException(&mout,"symbole invalide !");}
		else {switch_pos = true;}

	}
	else {throw MyException(&mout,"merged_string invalide !");}
	
	res_trinome->set_first(in);
	res_trinome->set_second(out);
	res_trinome->set_third(switch_pos);
	
	return res_trinome;
	
}

bool ClassicChess::exec_step(std::string in, std::string out, BitypeVar<Chesspiece*> adv_pe_out, bool switch_pos,bool abandon){
	
	bool end;
	
	if (not abandon){
		end = check_end_game(adv_pe_out, switch_pos);
	
		// ici on suppose que input correcte puisque apres les verification
		this->exec_move(in,out,switch_pos);
	}
	
	if (not(end)){this->check_evolution();} // nouveau !!
	
	if (not(end)){
		end = this->verify_kings();
		if(not(end)){
			end = this->check_pat();
		}
	} //RAJOUTER LE PAT
	else{this->get_active_player()->send_msg(this->get_dico()->search(this->get_active_player()->get_langue(),"mode_echec_et_mat"),true);} // si arret par consequences automatiquement echec et mat (pas possible de pat)
	
	this->affichage();
	
	if (not end and not abandon){this->change_active_player();}
	else{
		
		if (abandon == true){this->change_active_player();}
		
		std::stringstream ss;
		
		ss<<this->get_dico()->search(this->get_active_player()->get_langue(),"vict")<<" "<<get_active_player()<<" !"<<std::endl;
		ss<<this->get_dico()->search(this->get_active_player()->get_langue(),"fin_match")<<"!"<<std::endl;
		
		this->get_active_player()->send_msg(ss.str());
	}
	
	this->inc_action_cnt();

	return end;

}

std::pair<bool,std::string> ClassicChess::execute_step(){
	
	/* fonction principale du jeu, boucle d'execution qui est lancé pour débuté le jeu et qui lorsque se termine termine le jeu*/
	
	bool end = false;
	bool abandon = false;
	
	Trinome<std::pair<std::string,BitypeVar<Chesspiece*>>,std::pair<std::string,BitypeVar<Chesspiece*>>,std::pair<bool,bool>>* coords;
	
	std::pair<std::string,BitypeVar<Chesspiece*>> in_couple,out_couple;
	bool switch_pos;
	
	std::string in,out;
	BitypeVar<Chesspiece*> adv_pe_in;
	BitypeVar<Chesspiece*> adv_pe_out;
	
	std::pair<bool,bool> bool_info;
	if (this->get_action_cnt() == 0){this->affichage();}

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
	std::cout << "print4" << std::endl;

	//
	end = this->exec_step(in, out, adv_pe_out, switch_pos, abandon);
	//
	
	std::string result_sep = ";";
	std::stringstream ss_res;
	ss_res<<in<<result_sep;
	if (switch_pos == true){ss_res<<this->get_roc_symbol()<<result_sep;}
	ss_res<<out;
	
	std::pair<bool,std::string> result = std::make_pair((end or abandon),ss_res.str());
	
	return result;
}

std::pair<bool,bool> ClassicChess::execute_step(std::string merged_coords){
	
	Trinome<std::string,std::string,bool>* res_trinome = this->decode_merged_string(merged_coords);
	
	std::string in = res_trinome->get_first();
	std::string out = res_trinome->get_second();
	bool switch_pos = res_trinome->get_third();

	bool ok = false;
	bool end = false;
	
	std::pair<bool,BitypeVar<Chesspiece*>> in_paire = check_in_validity_non_symbol(in,"",""); // verify in //les commentaires sont inutiles ici
	bool in_isvalid = in_paire.first;
	
	if (in_isvalid == true){
		
		BitypeVar<Chesspiece*> in_bit = in_paire.second;
		
		if (in_bit.get_state() == false){throw MyException(&mout,"IN invalide car non-attribué");}
		
		MatPosi* mpos = new MatPosi(out);
		BitypeVar<Chesspiece*> out_bit = this->get_plateau()->get_piece(mpos->to_pair());
		delete mpos;
	
		if(switch_pos == true){
			
			if (out_bit.get_state() == false){throw MyException(&mout,"OUT invalide car non-attribué alors que dans roc");}
			
			// verify roc
			Chesspiece* in_pe = in_bit.get_var();
			bool ok_roc = is_roquable(in_pe);
			
			if (ok_roc){
				
				bool in_is_king,in_is_tour;
				
				Roi* roi;
				Tour* tour;
				
				bool good_type_in_pe = true;
				
				if (verifier_type_pe<Roi>(in_pe)){
					in_is_king = true;
					in_is_tour = false;
				}
				else if (verifier_type_pe<Tour>(in_pe)){
					in_is_king = true;
					in_is_tour = false;
				}
				else{
					ok = false;
					good_type_in_pe = false;
				}
				
				if(good_type_in_pe == true){
					if (in_is_king == true){roi = dynamic_cast<Roi*>(in_pe);}
					else{tour = dynamic_cast<Tour*>(in_pe);}
					
					ok = this->check_roc_validity(roi,tour, out_bit, in_is_king, in_is_tour);
				}
			}
		}
		else{
			std::pair<bool,BitypeVar<Chesspiece*>> out_paire = normal_output_check(in,out); // verify out
			ok = out_paire.first;
		}
		
		if (ok == true){
						
			MatPosi* mpos = new MatPosi(out);
			BitypeVar<Chesspiece*> adv_pe_out = this->get_plateau()->get_piece(mpos->to_pair()); // recup de piece de out
			delete mpos;
			
			end = this->exec_step(in, out, adv_pe_out, switch_pos, false); //abandon est tjs false ici
		}
	}
	
	std::pair<bool,bool> result = std::make_pair(ok,end);
	
	return result;
	
}

std::pair<bool,bool> ClassicChess::execute_step(std::string merged_coords,std::string player_name){
	
	//if (this->get_active_player()->get_name() != player_name){throw MyException(&mout,"execution impossible, ce n'est pas le tour de ce joueur");}
	
	return this->execute_step(merged_coords);
	
}

