
#include "TrappistChess.hpp"
#include <sstream>

extern MyOstream mout;

//MyOstream mout("logfile.txt"); // ???

//--------------------TrappistChess----------------------------------------------------------------------------------------------------

bool TrappistChess::check_pat(){
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

TrappistChess::TrappistChess(Player* p_low, Player* p_high,Player* deb_player, Dico* dict) : BaseChess(p_low,p_high,deb_player,dict){
	
	if((deb_player != p_low) and (deb_player != p_high)){throw MyException(&mout,"joueur devant commencé inconnnu!");}
	
	this->initialisation();
} //*< Constructor


void TrappistChess::initialise_board()
{
    Plateau* plat = new Plateau(24);
    this->set_plateau(plat);
}

void TrappistChess::initialise_high_pieces(){
	/* mise en place des pieces pour le joeur se trouvant en haut du tableau
	 * selon https://www.chessvariants.com/rules/trappist-1 */

	Player* own = get_high_player();
	
	//ligne 24
	Pion* pion_b_vingt_quatre = new Pion("down");
    this->initial_set_piece(pion_b_vingt_quatre, own, "B24");
    
    Faucon* fauc_d_vingt_quatre = new Faucon();
    this->initial_set_piece(fauc_d_vingt_quatre, own, "D24");
    
    Pion* pion_f_vingt_quatre = new Pion("down");
    this->initial_set_piece(pion_f_vingt_quatre, own, "F24");
    
    Pion* pion_s_vingt_quatre = new Pion("down");
    this->initial_set_piece(pion_s_vingt_quatre, own, "S24");
    
    Faucon* fauc_u_vingt_quatre = new Faucon();
    this->initial_set_piece(fauc_u_vingt_quatre, own, "U24");
    
    Pion* pion_w_vingt_quatre = new Pion("down");
    this->initial_set_piece(pion_w_vingt_quatre, own, "W24");
	
	//ligne 23
    Pion* pion_c_vingt_trois = new Pion("down");
    this->initial_set_piece(pion_c_vingt_trois, own, "C23");
    
    Pion* pion_e_vingt_trois = new Pion("down");
    this->initial_set_piece(pion_e_vingt_trois, own, "E23");
    
    Pion* pion_t_vingt_trois = new Pion("down");
    this->initial_set_piece(pion_t_vingt_trois, own, "T23");
    
    Pion* pion_v_vingt_trois = new Pion("down");
    this->initial_set_piece(pion_v_vingt_trois, own, "V23");
	
	//ligne 22
	Pion* pion_d_vingt_deux = new Pion("down");
    this->initial_set_piece(pion_d_vingt_deux, own, "D22");
    
    Pion* pion_u_vingt_deux = new Pion("down");
    this->initial_set_piece(pion_u_vingt_deux, own, "U22");
	
	//ligne 17
	Pion* pion_e_dix_sept = new Pion("down");
    this->initial_set_piece(pion_e_dix_sept, own, "E17");

	Fonctionnaire* fonc_f_dix_sept = new Fonctionnaire();
    this->initial_set_piece(fonc_f_dix_sept, own, "F17");
	
	Chevalier* cheval_k_dix_sept = new Chevalier();
    this->initial_set_piece(cheval_k_dix_sept, own, "K17");
    
    Fous* fou_l_dix_sept = new Fous();
    this->initial_set_piece(fou_l_dix_sept , own, "L17");
   
    Fous* fou_m_dix_sept = new Fous();
    this->initial_set_piece(fou_m_dix_sept, own, "M17");
    
    Chevalier* cheval_n_dix_sept = new Chevalier();
    this->initial_set_piece(cheval_n_dix_sept, own, "N17");
    
    Fonctionnaire* fonc_s_dix_sept = new Fonctionnaire();
    this->initial_set_piece(fonc_s_dix_sept, own, "S17");
    
    Pion* pion_t_dix_sept = new Pion("down");
    this->initial_set_piece(pion_t_dix_sept, own, "T17");
	
	// ligne 16
    Pion* pion_f_seize = new Pion("down");
    this->initial_set_piece(pion_f_seize, own, "F16");
    
    Tour* tour_g_seize = new Tour();
	this->initial_set_piece(tour_g_seize,own,"G16");
	
	Chancellier* chanc_h_seize = new Chancellier();
	this->initial_set_piece(chanc_h_seize,own,"H16");
	
	Garde* garde_i_seize = new Garde();
	this->initial_set_piece(garde_i_seize,own,"I16");
	
	Chevalier* cheval_j_seize = new Chevalier();
	this->initial_set_piece(cheval_j_seize,own,"J16");
	
	Fous* fou_k_seize = new Fous();
	this->initial_set_piece(fou_k_seize,own,"K16");
	
	Dame* dame_l_seize = new Dame();
	this->initial_set_piece(dame_l_seize,own,"L16");
	
	Roi* roi_m_seize = new Roi();
	this->initial_set_piece(roi_m_seize,own,"M16");
	
	Fous* fou_deux = new Fous();
	this->initial_set_piece(fou_deux,own,"N16");
	
	Chevalier* cheval_o_seize = new Chevalier();
	this->initial_set_piece(cheval_o_seize,own,"O16");
	
	Garde* garde_p_seize = new Garde();
	this->initial_set_piece(garde_p_seize,own,"P16");
	
	Chancellier* chanc_q_seize = new Chancellier();
	this->initial_set_piece(chanc_q_seize,own,"Q16");
	
	Tour* tour_r_seize = new Tour();
	this->initial_set_piece(tour_r_seize,own,"R16");
	
	Pion* pion_s_seize = new Pion("down");
    this->initial_set_piece(pion_s_seize, own, "S16");
	
	// ligne 15
    Pion* pion_g_quinze = new Pion("down");
    this->initial_set_piece(pion_g_quinze, own, "G15");
    
    Pion* pion_h_quinze = new Pion("down");
    this->initial_set_piece(pion_h_quinze, own, "H15");
    
    Pion* pion_i_quinze = new Pion("down");
    this->initial_set_piece(pion_i_quinze, own, "I15");
    
    Pion* pion_j_quinze = new Pion("down");
    this->initial_set_piece(pion_j_quinze, own, "J15");
    
    Pion* pion_k_quinze = new Pion("down");
    this->initial_set_piece(pion_k_quinze, own, "K15");
    
    Pion* pion_l_quinze = new Pion("down");
    this->initial_set_piece(pion_l_quinze, own, "L15");
    
    Pion* pion_m_quinze = new Pion("down");
    this->initial_set_piece(pion_m_quinze, own, "M15");
    
    Pion* pion_n_quinze = new Pion("down");
    this->initial_set_piece(pion_n_quinze, own, "N15");
    
    Pion* pion_o_quinze = new Pion("down");
    this->initial_set_piece(pion_o_quinze, own, "O15");
    
    Pion* pion_p_quinze = new Pion("down");
    this->initial_set_piece(pion_p_quinze, own, "P15");
    
    Pion* pion_q_quinze = new Pion("down");
    this->initial_set_piece(pion_q_quinze, own, "Q15");
    
    Pion* pion_r_quinze = new Pion("down");
    this->initial_set_piece(pion_r_quinze, own, "R15");

}

void TrappistChess::initialise_low_pieces()
{
    /* mise en place des pieces pour le joeur se trouvant en bas du tableau
     * selon https://www.chessvariants.com/rules/trappist-1
     * */
    
    // plustard utiliser fonctionnalité mirror de coorédonée pour les 2 cotés!-------------------------------------------------------------------------
    //(! ne pas le rendre abligatoire pour rester compatible avec toutes les variantes [ex: horde chess])
    // ex: bool miiror et ask_for mirroring(std;;string coord ,bool mirror)

    Player* own = get_low_player();

    // ligne 10
    Pion* pion_g_dix = new Pion("up");
    this->initial_set_piece(pion_g_dix, own, "G10");
    
    Pion* pion_h_dix = new Pion("up");
    this->initial_set_piece(pion_h_dix, own, "H10");
    
    Pion* pion_i_dix = new Pion("up");
    this->initial_set_piece(pion_i_dix, own, "I10");
    
    Pion* pion_j_dix = new Pion("up");
    this->initial_set_piece(pion_j_dix, own, "J10");
    
    Pion* pion_k_dix = new Pion("up");
    this->initial_set_piece(pion_k_dix, own, "K10");
    
    Pion* pion_l_dix = new Pion("up");
    this->initial_set_piece(pion_l_dix, own, "L10");
    
    Pion* pion_m_dix = new Pion("up");
    this->initial_set_piece(pion_m_dix, own, "M10");
    
    Pion* pion_n_dix = new Pion("up");
    this->initial_set_piece(pion_n_dix, own, "N10");
    
    Pion* pion_o_dix = new Pion("up");
    this->initial_set_piece(pion_o_dix, own, "O10");
    
    Pion* pion_p_dix = new Pion("up");
    this->initial_set_piece(pion_p_dix, own, "P10");
    
    Pion* pion_q_dix = new Pion("up");
    this->initial_set_piece(pion_q_dix, own, "Q10");
    
    Pion* pion_r_dix = new Pion("up");
    this->initial_set_piece(pion_r_dix, own, "R10");
	
	//ligne 9
    Pion* pion_f_neuf = new Pion("up");
    this->initial_set_piece(pion_f_neuf, own, "F9");
    
    Tour* tour_g_neuf = new Tour();
	this->initial_set_piece(tour_g_neuf,own,"G9");
	
	Chancellier* chanc_h_neuf = new Chancellier();
	this->initial_set_piece(chanc_h_neuf,own,"H9");
	
	Garde* garde_i_neuf = new Garde();
	this->initial_set_piece(garde_i_neuf,own,"I9");
	
	Chevalier* cheval_j_neuf = new Chevalier();
	this->initial_set_piece(cheval_j_neuf,own,"J9");
	
	Fous* fou_k_neuf = new Fous();
	this->initial_set_piece(fou_k_neuf,own,"K9");
	
	Dame* dame_l_neuf = new Dame();
	this->initial_set_piece(dame_l_neuf,own,"L9");
	
	Roi* roi_m_neuf = new Roi();
	this->initial_set_piece(roi_m_neuf,own,"M9");
	
	Fous* fou_deux = new Fous();
	this->initial_set_piece(fou_deux,own,"N9");
	
	Chevalier* cheval_o_neuf = new Chevalier();
	this->initial_set_piece(cheval_o_neuf,own,"O9");
	
	Garde* garde_p_neuf = new Garde();
	this->initial_set_piece(garde_p_neuf,own,"P9");
	
	Chancellier* chanc_q_neuf = new Chancellier();
	this->initial_set_piece(chanc_q_neuf,own,"Q9");
	
	Tour* tour_r_neuf = new Tour();
	this->initial_set_piece(tour_r_neuf,own,"R9");
	
	Pion* pion_s_neuf = new Pion("up");
    this->initial_set_piece(pion_s_neuf, own, "S9");
	
	//ligne 8
	Pion* pion_e_huit = new Pion("up");
    this->initial_set_piece(pion_e_huit, own, "E8");

	Fonctionnaire* fonc_f_huit = new Fonctionnaire();
    this->initial_set_piece(fonc_f_huit, own, "F8");
	
	Chevalier* cheval_k_huit = new Chevalier();
    this->initial_set_piece(cheval_k_huit, own, "K8");
    
    Fous* fou_l_huit = new Fous();
    this->initial_set_piece(fou_l_huit , own, "L8");
   
    Fous* fou_m_huit = new Fous();
    this->initial_set_piece(fou_m_huit, own, "M8");
    
    Chevalier* cheval_n_huit = new Chevalier();
    this->initial_set_piece(cheval_n_huit, own, "N8");
    
    Fonctionnaire* fonc_s_huit = new Fonctionnaire();
    this->initial_set_piece(fonc_s_huit, own, "S8");
    
    Pion* pion_t_huit = new Pion("up");
    this->initial_set_piece(pion_t_huit, own, "T8");
	
	//ligne 3
	Pion* pion_d_trois = new Pion("up");
    this->initial_set_piece(pion_d_trois, own, "D3");
    
    Pion* pion_u_trois = new Pion("up");
    this->initial_set_piece(pion_u_trois, own, "U3");
	
	//ligne 2
    Pion* pion_c_deux = new Pion("up");
    this->initial_set_piece(pion_c_deux, own, "C2");
    
    Pion* pion_e_deux = new Pion("up");
    this->initial_set_piece(pion_e_deux, own, "E2");
    
    Pion* pion_t_deux = new Pion("up");
    this->initial_set_piece(pion_t_deux, own, "T2");
    
    Pion* pion_v_deux = new Pion("up");
    this->initial_set_piece(pion_v_deux, own, "V2");
	
	//ligne 1
	Pion* pion_b_un = new Pion("up");
    this->initial_set_piece(pion_b_un, own, "B1");
    
    Faucon* fauc_d_un = new Faucon();
    this->initial_set_piece(fauc_d_un, own, "D1");
    
    Pion* pion_f_un = new Pion("up");
    this->initial_set_piece(pion_f_un, own, "F1");
    
    Pion* pion_s_un = new Pion("up");
    this->initial_set_piece(pion_s_un, own, "S1");
    
    Faucon* fauc_u_un = new Faucon();
    this->initial_set_piece(fauc_u_un, own, "U1");
    
    Pion* pion_w_un = new Pion("up");
    this->initial_set_piece(pion_w_un, own, "W1");
	
}

void TrappistChess::affichage(){
	/* fonction affaichant le tableau de jeu ainsi que les joueurs l'entourant */
	
	Affichage* aff = new Affichage(this->get_plateau(), this->get_dico(),"Symbole_","",this->get_active_player()->get_langue(),this->get_low_player(), this->get_high_player(),"*" ,"",6,3);
	this->get_active_player()->send_msg(aff->get_affichage(),true);
}

std::pair<bool,BitypeVar<Chesspiece*>> TrappistChess::normal_output_check(std::string in,std::string out){
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

Trinome<std::string,BitypeVar<Chesspiece*>,Trinome<bool,bool,bool>*>* TrappistChess::out_input(std::string in, BitypeVar<Chesspiece*> in_pe){
	
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
		
	bool roc_accept = false; // roc interdit dans trappist!
		
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

bool TrappistChess::exec_step(std::string in, std::string out, BitypeVar<Chesspiece*> adv_pe_out, bool switch_pos,bool abandon){
	
	bool end;
	
	if (not abandon){
		end = check_end_game(adv_pe_out, switch_pos);
	
		// ici on suppose que input correcte puisque apres les verification
		this->exec_move(in,out,switch_pos);
	}
	
	if (not(end)){this->check_evolution();} // nouveau !!
	
	if (not(end)){
		end = this->verify_kings();
		//if(not(end)){
		//	end = this->check_pat();
		//}
		
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

std::pair<bool,std::string> TrappistChess::execute_step(){
	
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
	//std::cout << "print4" << std::endl;

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

std::pair<bool,bool> TrappistChess::execute_step(BitypeVar<Trinome<std::string,std::string,bool>*>* res_bit){

	bool ok = false;
	bool end = false;
	
	if (res_bit->get_state() == true){
	
		Trinome<std::string,std::string,bool>* res_trinome = res_bit->get_var();
			
		std::string in = res_trinome->get_first();
		std::string out = res_trinome->get_second();
		bool switch_pos = res_trinome->get_third();
	
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
	}
	
	std::pair<bool,bool> result = std::make_pair(ok,end);
	
	return result;
	
}

std::vector<Chesspiece*>* TrappistChess::evolution_possibilities(){
	
	Tour* tour = new Tour();
	Fous* fous = new Fous();
	Chevalier* chevalier = new Chevalier();
	Dame* dame = new Dame();
	Fonctionnaire* fonctionnaire = new Fonctionnaire();
	Garde* garde = new Garde();
	Faucon* faucon = new Faucon();
	Chancellier* chancellier = new Chancellier();
	
	std::vector<Chesspiece*>* chess_vect = new std::vector<Chesspiece*>();
	chess_vect->push_back(tour);
	chess_vect->push_back(fous);
	chess_vect->push_back(chevalier);
	chess_vect->push_back(dame);
	chess_vect->push_back(fonctionnaire);
	chess_vect->push_back(garde);
	chess_vect->push_back(faucon);
	chess_vect->push_back(chancellier);
	
	return chess_vect;
	
}

int TrappistChess::get_evolution_row(Player* play){
	
	int row;
	
	if (play == this->get_low_player()){row = 15;} //16 si on commence a 1
	else if (play == this->get_high_player()){row = 8;} // 9 si on commence a 1
	else{throw MyException(&mout,"joueur inconnu pour avoir sa ligne d'evolution!");}
	
	return row;
}
