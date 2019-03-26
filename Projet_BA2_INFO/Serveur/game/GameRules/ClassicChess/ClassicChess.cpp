
#include "ClassicChess.hpp"
#include <sstream>

extern MyOstream mout;

//--------------------ClassicChess----------------------------------------------------------------------------------------------------

ClassicChess::ClassicChess(Player* p_low, Player* p_high,Player* deb_player, Dico* dict,AbstractAffichage* aff) : BaseChess(p_low,p_high,deb_player,dict,aff){
	
	if((deb_player != p_low) and (deb_player != p_high)){throw MyException(&mout,"joueur devant commencé inconnnu!");}
	
	this->initialisation();
} //*< Constructor


void ClassicChess::initialise_board(){	
	Plateau* plat = new Plateau(8);
	this->set_plateau(plat);
	
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

void ClassicChess::initialise_low_pieces(){ 
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

void ClassicChess::affichage(){
	/* fonction affaichant le tableau de jeu ainsi que les joueurs l'entourant */
	
	AbstractAffichage* aff = this->get_affich();
	
	aff->set_active_player(this->get_active_player());
	aff->set_dico_language(this->get_active_player()->get_langue()); // plustard a enlever !!!!
	
	aff->show();
	//this->get_active_player()->send_msg(aff->get_affichage(),true);
}

std::pair<bool,std::string> ClassicChess::execute_step(Player* play){
	
	/* fonction principale du jeu, boucle d'execution qui est lancé pour débuté le jeu et qui lorsque se termine termine le jeu*/
	
	this->set_active_player(play);
	
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

std::pair<bool,bool> ClassicChess::execute_forced_step(BitypeVar<Trinome<std::string,std::string,bool>*>* res_bit,Player* play){
	
	this->set_active_player(play);
	
	if (this->get_action_cnt() == 0){this->affichage();}
	
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

std::vector<Chesspiece*>* ClassicChess::evolution_possibilities(){
	
	Tour* tour = new Tour();
	Fous* fous = new Fous();
	Chevalier* chevalier = new Chevalier();
	Dame* dame = new Dame();
	
	std::vector<Chesspiece*>* chess_vect = new std::vector<Chesspiece*>();
	chess_vect->push_back(tour);
	chess_vect->push_back(fous);
	chess_vect->push_back(chevalier);
	chess_vect->push_back(dame);
	
	return chess_vect;
	
}
