
#include "AntiChess.hpp"
#include <sstream>

extern MyOstream mout;

//--------------------AntiChess----------------------------------------------------------------------------------------------------

AntiChess::AntiChess(Player* p_low, Player* p_high,Player* deb_player, Dico* dict) : BaseChess(p_low,p_high,deb_player,dict){
	
	if((deb_player != p_low) and (deb_player != p_high)){throw MyException(&mout,"joueur devant commencé inconnnu!");}
	
	this->initialisation();
} //*< Constructor


void AntiChess::initialise_board(){	
	Plateau* plat = new Plateau(8);
	this->set_plateau(plat);
	
}

void AntiChess::initialise_high_pieces(){
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

void AntiChess::initialise_low_pieces(){ 
	/* mise en place des pieces pour le joeur se trouvant en bas du tableau */

	Player* own = get_low_player();
	
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

}

void AntiChess::affichage(){
	/* fonction affaichant le tableau de jeu ainsi que les joueurs l'entourant */
	
	Affichage* aff = new Affichage(this->get_plateau(), this->get_dico(),"Symbole_","",this->get_active_player()->get_langue(),this->get_low_player(), this->get_high_player(),"*" ,"");
	this->get_active_player()->send_msg(aff->get_affichage(),true);
}

std::pair<bool,std::string> AntiChess::execute_step(){
	
	/* fonction principale du jeu, boucle d'execution qui est lancé pour débuté le jeu et qui lorsque se termine termine le jeu*/
	
	bool end = false;
	bool abandon = false;
	
	Trinome<Paire<std::string,BitypeVar<Chesspiece*>>,Paire<std::string,BitypeVar<Chesspiece*>>,Paire<bool,bool>>* coords;
	
	Paire<std::string,BitypeVar<Chesspiece*>> in_couple,out_couple;
	bool switch_pos;
	
	std::string in,out;
	BitypeVar<Chesspiece*> adv_pe_in;
	BitypeVar<Chesspiece*> adv_pe_out;
	
	Paire<bool,bool> bool_info;
	if (this->get_action_cnt() == 0){this->affichage();}

	coords = this->ask_for_input();
	in_couple = coords->get_first();

	in = in_couple.get_first();
	adv_pe_in = in_couple.get_second();
	
	out_couple = coords->get_second();
	out = out_couple.get_first();
	adv_pe_out = out_couple.get_second();
	
	bool_info = coords->get_third();
	
	abandon = bool_info.get_first();
	switch_pos = bool_info.get_second();
	//std::cout << "print4" << std::endl;

	//
	end = this->exec_step(in, out, adv_pe_out, switch_pos, abandon);
	//
	
	std::string result_sep = ";";
	std::stringstream ss_res;
	ss_res<<in<<result_sep;
	if (switch_pos == true){ss_res<<this->get_roc_symbol()<<result_sep;}
	ss_res<<out;
	
	std::pair<bool,std::string> result = std::make_pair((end or abandon), ss_res.str());

    return result;
}

std::pair<bool,bool> AntiChess::execute_step(BitypeVar<Trinome<std::string,std::string,bool>*>* res_bit){
	
	bool ok = false;
	bool end = false;
	
	if (res_bit->get_state() == true){
	
		Trinome<std::string,std::string,bool>* res_trinome = res_bit->get_var();
			
		std::string in = res_trinome->get_first();
		std::string out = res_trinome->get_second();
		bool switch_pos = res_trinome->get_third();

		Paire<bool,BitypeVar<Chesspiece*>> in_paire = check_in_validity_non_symbol(in,"",""); // verify in //les commentaires sont inutiles ici
		bool in_isvalid = in_paire.get_first();
		
		if (in_isvalid == true){
			
			BitypeVar<Chesspiece*> in_bit = in_paire.get_second();
			
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
				Paire<bool,BitypeVar<Chesspiece*>> out_paire = normal_output_check(in,out); // verify out
				ok = out_paire.get_first();
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

bool AntiChess::verify_kings(){
	/* fonction vérifiant la présence des roi des deux joueurs sur le plateau */
	
	return false; // retourne si echec et mat
	
}

bool AntiChess::check_non_active_player_king(Chesspiece* pe) {
	/* fonction qui vérifie l'état du roi adverse sur le plateau
	 * (en echec, en echec et mat, coincé, ...) */
	(void) *pe;
	return false;
	
}

std::vector<Chesspiece*>* AntiChess::evolution_possibilities(){
	
	Tour* tour = new Tour();
	Fous* fous = new Fous();
	Chevalier* chevalier = new Chevalier();
	Dame* dame = new Dame();
	Roi* roi = new Roi();
	
	std::vector<Chesspiece*>* chess_vect = new std::vector<Chesspiece*>();
	chess_vect->push_back(tour);
	chess_vect->push_back(fous);
	chess_vect->push_back(chevalier);
	chess_vect->push_back(dame);
	chess_vect->push_back(roi);
	
	return chess_vect;
	
}

std::string AntiChess::get_affichage_pat() const{
	std::stringstream ss;
	ss<<this->get_dico()->search(this->get_active_player()->get_langue(),"vict")<<" "<<this->get_active_player()<<" !"<<std::endl;}
	return ss.str;

}

bool AntiChess::check_roc_accept(BitypeVar<Chesspiece*> in_pe) const {
	(void)in_pe;
	return false;
}
