
#include "DarkChess.hpp"
#include <sstream>

extern MyOstream mout;

//--------------------DarkChess----------------------------------------------------------------------------------------------------

<<<<<<< HEAD:Projet_BA2_INFO/Client/game/Games/DarkChess/DarkChess.cpp
DarkChess::DarkChess(Player* p_low, Player* p_high,Player* deb_player,Player* locked_play, Dico* dict) : BaseChess(p_low,p_high,deb_player,dict), fog((*(new std::vector<std::vector<int>>()))), locked_player(locked_play){
=======
DarkChess::DarkChess(Player* p_low, Player* p_high,Player* deb_player,Player* locked_play, Dico* dict, AbstractAffichage* aff) : BaseChess(p_low,p_high,deb_player,dict,aff), fog((*(new std::vector<std::vector<int>>()))), locked_player(locked_play){
>>>>>>> Partie_Serveur:Projet_BA2_INFO/Client/game/GameRules/DarkChess/DarkChess.cpp
	
	if((deb_player != p_low) and (deb_player != p_high)){throw MyException(&mout,"joueur devant commencé inconnnu!");}
	if((locked_play != nullptr) and (locked_play != p_low) and (locked_play != p_high)){throw MyException(&mout,"joueur etant verouille inconnnu!");}
	
	this->initialisation();
} //*< Constructor

Player* DarkChess::get_real_locked_player() const {
	return this->locked_player;
}

Player* DarkChess::get_locked_player() const {
	
	if (this->get_real_locked_player() != nullptr){return this->get_real_locked_player();}
	else{return this->get_non_active_player();}
		
}

void  DarkChess::set_locked_player(Player* locked_play){this->locked_player = locked_play;}

std::vector<std::vector<int>> DarkChess::get_fog() const {return this->fog;}
void DarkChess::set_fog(std::vector<std::vector<int>> fog_vect){this->fog = fog_vect;}

void DarkChess::initialise_board(){
    Plateau *plat = new Plateau(8);
    this->set_plateau(plat);
}

void DarkChess::initialise_high_pieces(){
    /* mise en place des pieces pour le joeur se trouvant en haut du tableau */

    Player *own = get_high_player();

    // ligne 8
    Tour *tour_un = new Tour();
    this->initial_set_piece(tour_un, own, "A8");

    Chevalier *cheval_un = new Chevalier();
    this->initial_set_piece(cheval_un, own, "B8");

    Fous *fou_un = new Fous();
    this->initial_set_piece(fou_un, own, "C8");

    Dame *dame = new Dame();
    this->initial_set_piece(dame, own, "D8");

    Roi *roi = new Roi();
    this->initial_set_piece(roi, own, "E8");

    Fous *fou_deux = new Fous();
    this->initial_set_piece(fou_deux, own, "F8");

    Chevalier *cheval_deux = new Chevalier();
    this->initial_set_piece(cheval_deux, own, "G8");

    Tour *tour_deux = new Tour();
    this->initial_set_piece(tour_deux, own, "H8");

    // ligne 7
    Pion *pion_un = new Pion("down");
    this->initial_set_piece(pion_un, own, "A7");

    Pion *pion_deux = new Pion("down");
    this->initial_set_piece(pion_deux, own, "B7");

    Pion *pion_trois = new Pion("down");
    this->initial_set_piece(pion_trois, own, "C7");

    Pion *pion_quatre = new Pion("down");
    this->initial_set_piece(pion_quatre, own, "D7");

    Pion *pion_cinq = new Pion("down");
    this->initial_set_piece(pion_cinq, own, "E7");

    Pion *pion_six = new Pion("down");
    this->initial_set_piece(pion_six, own, "F7");

    Pion *pion_sept = new Pion("down");
    this->initial_set_piece(pion_sept, own, "G7");

    Pion *pion_huit = new Pion("down");
    this->initial_set_piece(pion_huit, own, "H7");
}

void DarkChess::initialise_low_pieces(){
    /* mise en place des pieces pour le joeur se trouvant en bas du tableau */

    Player *own = get_low_player();

	// ligne 2
    Pion *pion_un = new Pion("up");
    this->initial_set_piece(pion_un, own, "A2");

    Pion *pion_deux = new Pion("up");
    this->initial_set_piece(pion_deux, own, "B2");

    Pion *pion_trois = new Pion("up");
    this->initial_set_piece(pion_trois, own, "C2");

    Pion *pion_quatre = new Pion("up");
    this->initial_set_piece(pion_quatre, own, "D2");

    Pion *pion_cinq = new Pion("up");
    this->initial_set_piece(pion_cinq, own, "E2");

    Pion *pion_six = new Pion("up");
    this->initial_set_piece(pion_six, own, "F2");

    Pion *pion_sept = new Pion("up");
    this->initial_set_piece(pion_sept, own, "G2");

    Pion *pion_huit = new Pion("up");
    this->initial_set_piece(pion_huit, own, "H2");

    // ligne 1
    Tour *tour_un = new Tour();
    this->initial_set_piece(tour_un, own, "A1");

    Chevalier *cheval_un = new Chevalier();
    this->initial_set_piece(cheval_un, own, "B1");

    Fous *fou_un = new Fous();
    this->initial_set_piece(fou_un, own, "C1");

    Dame *dame = new Dame();
    this->initial_set_piece(dame, own, "D1");

    Roi *roi = new Roi();
    this->initial_set_piece(roi, own, "E1");

    Fous *fou_deux = new Fous();
    this->initial_set_piece(fou_deux, own, "F1");

    Chevalier *cheval_deux = new Chevalier();
    this->initial_set_piece(cheval_deux, own, "G1");

    Tour *tour_deux = new Tour();
    this->initial_set_piece(tour_deux, own, "H1");

}

void DarkChess::affichage(Player* play){
<<<<<<< HEAD:Projet_BA2_INFO/Client/game/Games/DarkChess/DarkChess.cpp
    /* fonction affaichant le tableau de jeu ainsi que les joueurs l'entourant */
    make_fog(play);
    AffichageDarkChess *aff = new AffichageDarkChess(this->get_plateau(), this->get_dico(), "Symbole_", "",play->get_langue(),
                                                     this->get_low_player(), this->get_high_player(), "*", "", this->get_fog());
    this->get_active_player()->send_msg(aff->get_affichage(), true);
=======
	/* fonction affaichant le tableau de jeu ainsi que les joueurs l'entourant */
	
	make_fog(play);
	
	AffichageDarkChess* aff = dynamic_cast<AffichageDarkChess*>(this->get_affich());
	if (aff == nullptr){throw MyException(&mout,"Classe d'affichage invalide pour DarkChess");}
	
	if (this->get_action_cnt() == 0){aff->set_locked_player(play);}
	
	aff->set_fog(this->get_fog());
	aff->set_active_player(this->get_active_player());
	aff->set_dico_language(this->get_active_player()->get_langue()); // plustard a enlever !!!!
	
	aff->show();
	//this->get_active_player()->send_msg(aff->get_affichage(),true);
>>>>>>> Partie_Serveur:Projet_BA2_INFO/Client/game/GameRules/DarkChess/DarkChess.cpp
}

void DarkChess::affichage(){
	affichage(this->get_locked_player());
}

std::pair<bool, std::string> DarkChess::execute_step(Player* play){
    /* fonction principale du jeu, boucle d'execution qui est lancé pour débuté le jeu et qui lorsque se termine termine le jeu*/
    
    this->set_active_player(play);

    bool end = false;
    bool abandon = false;

    Trinome<std::pair<std::string, BitypeVar<Chesspiece *>>, std::pair<std::string, BitypeVar<Chesspiece *>>, std::pair<bool, bool>> *coords;

    std::pair<std::string, BitypeVar<Chesspiece *>> in_couple, out_couple;
    bool switch_pos;

    std::string in, out;
    BitypeVar<Chesspiece *> adv_pe_in;
    BitypeVar<Chesspiece *> adv_pe_out;

    std::pair<bool, bool> bool_info;

    
    if (this->get_action_cnt() == 0){
		if (this->get_real_locked_player() != nullptr){this->affichage();}
		else{this->affichage(this->get_active_player());}
		
	}

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

    //
    end = this->exec_step(in, out, adv_pe_out, switch_pos, abandon);
    //

    std::string result_sep = ";";
    std::stringstream ss_res;
    ss_res << in << result_sep;
    if (switch_pos == true){ss_res << this->get_roc_symbol() << result_sep;}
    
    ss_res << out;

    std::pair<bool, std::string> result = std::make_pair((end or abandon), ss_res.str());

    return result;
}

std::pair<bool, bool> DarkChess::execute_forced_step(BitypeVar<Trinome<std::string,std::string,bool>*>* res_bit,Player* play){
	
	this->set_active_player(play);
	
	if (this->get_action_cnt() == 0){
		if (this->get_real_locked_player() != nullptr){this->affichage();}
		else{this->affichage(this->get_active_player());}
		
	}
	
    bool ok = false;
	bool end = false;
	
	if (res_bit->get_state() == true){
		
		Trinome<std::string,std::string,bool>* res_trinome = res_bit->get_var();
			
		std::string in = res_trinome->get_first();
		std::string out = res_trinome->get_second();
		bool switch_pos = res_trinome->get_third();

		std::pair<bool, BitypeVar<Chesspiece *>> in_paire = check_in_validity_non_symbol(in, "", ""); // verify in //les commentaires sont inutiles ici
		bool in_isvalid = in_paire.first;

		if (in_isvalid == true){

			BitypeVar<Chesspiece *> in_bit = in_paire.second;

			if (in_bit.get_state() == false){throw MyException(&mout, "IN invalide car non-attribué");}

			MatPosi *mpos = new MatPosi(out);
			BitypeVar<Chesspiece *> out_bit = this->get_plateau()->get_piece(mpos->to_pair());
			delete mpos;

			if (switch_pos == true){

				if (out_bit.get_state() == false){throw MyException(&mout, "OUT invalide car non-attribué alors que dans roc");}

				// verify roc
				Chesspiece *in_pe = in_bit.get_var();
				bool ok_roc = is_roquable(in_pe);

				if (ok_roc){

					bool in_is_king, in_is_tour;

					Roi *roi = nullptr;
					Tour *tour = nullptr;

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

					if (good_type_in_pe == true){
						if (in_is_king == true){
							roi = dynamic_cast<Roi *>(in_pe);
						}
						else{
							tour = dynamic_cast<Tour *>(in_pe);
						}

						ok = this->check_roc_validity(roi, tour, out_bit, in_is_king, in_is_tour);
					}
				}
			}
			else{
				std::pair<bool, BitypeVar<Chesspiece *>> out_paire = normal_output_check(in, out); // verify out
				ok = out_paire.first;
			}

			if (ok == true){

				MatPosi *mpos = new MatPosi(out);
				BitypeVar<Chesspiece *> adv_pe_out = this->get_plateau()->get_piece(mpos->to_pair()); // recup de piece de out
				delete mpos;

				end = this->exec_step(in, out, adv_pe_out, switch_pos, false); // abandon est tjs false ici
			}
		}
	}

    std::pair<bool, bool> result = std::make_pair(ok, end);

    return result;
}

void DarkChess::make_fog(Player* play){
    /* Créer et met à jour le tableau contenant toutes les positions cacher du plateau*/
    std::vector<BitypeVar<Chesspiece*>> row;
    std::vector<std::pair<int, int>>* positions_vect;
    const int size(8);
    
    // init le tableau tout est caché
    std::vector<std::vector<int>> anti_fog_vect(8, std::vector<int>(8, 1));
    for (int i = 0; i < size; i++){   
        row = this->get_plateau()->get_row(i);
        for (int j = 0; j < size; j++){
			
            // check si la case contient bien une piece
            if (row[j].get_state()){
                Chesspiece* piece = row[j].get_var();
                
                // std::cout << "Board : "<<piece->get_name()<<"  x:  " << i << "  y:  " << j << std::endl;
                
                // construit uniquement en fonction du joueur actif
                if (piece->get_owner() == play){
                    //std::cout << "active player:  " << this->get_active_player()->get_name() << std::endl;
                    // std::cout<<"piece owner:  "<<piece->get_owner()->get_name()<<std::endl;
                    
                    // posititon de la piece est dévoilé
                    anti_fog_vect[piece->get_posi()->get_x()][piece->get_posi()->get_y()] = 0;
                    positions_vect = this->check_all_mov(piece);

                    // regarde les cases ou la piece peut se déplacer et les cases ou elle peut capturer pour les dévoiler
                    for (unsigned k = 0; k < positions_vect->size(); k++){
                        // std::cout << "movement : " << piece->get_name() << "  x:  " << (*positionMov)[k].second << "  y:  " << (*positionMov)[k].second << std::endl;
                        anti_fog_vect[(*positions_vect)[k].first][(*positions_vect)[k].second] = 0;
                    }
                }
            }
        }
    }
    this->set_fog(anti_fog_vect);
}



bool DarkChess::check_non_active_player_king(Chesspiece* pe) {
	/* fonction qui vérifie l'état du roi adverse sur le plateau
	 * (en echec, en echec et mat, coincé, ...) */
	(void) *pe;
	return false;
	
}

std::vector<Chesspiece*>* DarkChess::evolution_possibilities(){
	
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

bool DarkChess::roc_check_king_position_and_path_danger(MatPosi* mpos_roi, MatPosi* mpos_roi_dst, bool gauche_isking,int co_roi_dst,std::vector<MatPosi>* between_vect){
	
	MatPosi tmp_mpos_roi = *mpos_roi;
	(void)tmp_mpos_roi;
	
	MatPosi tmp_mpos_roi_dst = *mpos_roi_dst;
	(void)tmp_mpos_roi_dst;
	
	(void)gauche_isking;
	(void)co_roi_dst;
	
	std::vector<MatPosi> tmp_between_vect = *between_vect;
	(void)tmp_between_vect;
			
	return true; // retourne si roc est valide
	
}

std::vector<std::pair<int, int>>* DarkChess::check_all_mov(Chesspiece *pe){

    std::vector<std::pair<int, int>>* tmp;

    std::vector<std::pair<int, int>>* res = new std::vector<std::pair<int, int>>();
    
    std::vector<std::string> mode_vect {"depl", "capt", "capt_same", "capt_empty", "depl_full"};
    
    for (long long unsigned int i = 0; i < mode_vect.size(); i++){
		tmp = this->loop_moves(pe,mode_vect[i]);
		res->insert(res->end(), tmp->begin(), tmp->end());
	}

    return res;
} 


std::vector<std::pair<int, int>>* DarkChess::loop_moves(Chesspiece *pe, std::string mode){

    std::string limited_mode = this->get_plateau()->get_limited_mode(mode);

    std::vector<std::pair<std::pair<int, int>, AdvTuple>> vect = pe->algo(limited_mode);

    std::vector<std::pair<int, int>> *res = new std::vector<std::pair<int, int>>();
    MatPosi *elem;
    Posi *origin = pe->get_posi();
    MatPosi *mposi_origi = new MatPosi(*origin);
    std::pair<int, int> paire_origi = mposi_origi->to_pair();
    for (long long unsigned int i = 0; i < vect.size(); i++){
        elem = new MatPosi(vect[i].first);
        AdvTuple adv_tup = vect[i].second;
        std::pair<int, int> paire = elem->to_pair();
        vect[i].first.first >= 0 && vect[i].first.second >= 0;
        if (this->check_danger_mouvement_and_path(paire_origi, adv_tup, paire, mode)){
            res->push_back(vect[i].first);
        }
    }
    return res;
}
<<<<<<< HEAD:Projet_BA2_INFO/Client/game/Games/DarkChess/DarkChess.cpp

bool DarkChess::check_non_active_player_king(Chesspiece* pe) {
	/* fonction qui vérifie l'état du roi adverse sur le plateau
	 * (en echec, en echec et mat, coincé, ...) */
	(void) *pe;
	return false;
	
}

std::vector<Chesspiece*>* DarkChess::evolution_possibilities(){
	
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

bool DarkChess::roc_check_king_position_and_path_danger(MatPosi* mpos_roi, MatPosi* mpos_roi_dst, bool gauche_isking,int co_roi_dst,std::vector<MatPosi>* between_vect){
	
	MatPosi tmp_mpos_roi = *mpos_roi;
	(void)tmp_mpos_roi;
	
	MatPosi tmp_mpos_roi_dst = *mpos_roi_dst;
	(void)tmp_mpos_roi_dst;
	
	(void)gauche_isking;
	(void)co_roi_dst;
	
	std::vector<MatPosi> tmp_between_vect = *between_vect;
	(void)tmp_between_vect;
			
	return true; // retourne si roc est valide
	
}
=======
>>>>>>> Partie_Serveur:Projet_BA2_INFO/Client/game/GameRules/DarkChess/DarkChess.cpp
