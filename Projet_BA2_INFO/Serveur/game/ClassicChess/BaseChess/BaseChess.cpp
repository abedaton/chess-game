
#include "BaseChess.hpp"

extern MyOstream mout;

/* principe général:
 * le serveur manipule un plateau,
 * le plateau ne doit pas connaitre ce qu'il contient pour exister */

//-----------------------HORS CLASSE BaseChess-----------------------------------------------

bool check_end_game(BitypeVar<Chesspiece*> adv_pe, bool switch_pos){
	
	/* fonction qui vérifie si la derniere piece prise etait un roi
	 * la piece prise étant la piece sur la 2e case (la case destination) selectionné lors d'un mouvement.
	 * le cas du roc étant implémenté comme une prise (selection de sa case comme "destination" [2e case selectionné]) est refusé */
	
	bool end_game;
	
	if (not(switch_pos)){
		end_game = verifier_type_pe<Roi>(adv_pe);
	}
	else{end_game = false;}
	
	return end_game;
}

BitypeVar<int>* detect_ennemy_pion_in_vect(std::vector<BitypeVar<Chesspiece*>> vect, Player* owner){
	
	/* fonction vérifiant si une piece ennemie se trouve dans le vecteur donné en paramètre
	 * piece ennemie = piece dont le propriétaire est différent de celui donné en paramètre */
	
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
	
	/* fonction qui renvoi le roi du joeuer donné en paramètre se situant dans la liste */
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
	/* fonction utile pour calculer les positions se situant entre 2 positions,
	 * cette fonction détermine le facteur multiplicatif de direction du mouvement
	 * (par conséquent indique la direcion du mouvement souhaité)
	 * 
	 * ex: si horizontal se sera (1,0) comme 1 en x et 0 en y
	 * 
	 * limitations: pêut seulment détecter si les 2 positions sor sur une ligne horizontale,verticale ou diagonale */
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
	/* fonction qui calucule la destination du roi et de la tour suite a un roc, peu import si c'est un prtit ou grand roque */
		
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
	/* fonction qui calucule les cases que le roi doit parcourir lors d'un roque,
	 * (utile pour vérifier si il est danger lors de son trajet)*/
	
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
	/* fonction qui classe 2 MatPosi, celui le plus a gauche est le 1e elemnt du retour, celui le plus a droite le second */
	
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

BitypeVar<std::vector<MatPosi>*>* calc_zones_between_zones(MatPosi* begin, MatPosi* end, Player* player){
	/* fonction qui calcule les positions réele se situant entre 2 positions
	 * 
	 * ex: entre (0,4) et (0,7) il y a (0,5) et (0,6)
	 * 
	 * limitations: pêut seulment détecter si les 2 positions sor sur une ligne horizontale,verticale ou diagonale
	 */
	
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
			
			player->send_msg(ss.str());
			
			if(*temp_mpos < *fin){vect->push_back(*temp_mpos);}
			
		}
		res->set_var(vect);		
	}
	
	return res;
	
}

bool is_elem_in_vect(std::vector<MatPosi*>* vect,MatPosi* elem){
	
	bool found = false;
	
	long long unsigned int i=0;
	while(i<vect->size() and not found){
		if (*elem == (*((*vect)[i]))){found = true;}
		i++;
	}
	
	return found;
}


std::vector<MatPosi*>* get_path_intesection(std::vector<std::vector<MatPosi*>*>* vect){
	
	std::vector<MatPosi*>* res = new std::vector<MatPosi*>();
	
	for(long long unsigned int i=0;i<((*vect)[0])->size();i++){
		
		std::vector<MatPosi*> small_vect = *((*vect)[0]);
		MatPosi* elem = (small_vect[i]);
		
		bool common = true;
		long long unsigned int j=0;
		
		while(j<vect->size() and common == true){
			
			if(not is_elem_in_vect((*vect)[j],elem)){common = false;}
			j++;
		}
		
		if (common == true){res->push_back(elem);}
	}
	
	
	return res;
	
}

//--------------------BaseChess----------------------------------------------------------------------------------------------------

BaseChess::BaseChess(Player* p_low,Player* p_high,Dico* dict) : plateau(nullptr) , low_player(p_low), high_player(p_high), active_player(p_low), dico(dict){
	//this->initialisation(); /!\ impossible de le mettre cette fonction ici car contructeur appelé par fils, par conséquent utilisation de fonction virtuelle pure dans ce cas.
	// a mettre dans le constructeur du fils !!!
	
} //*< Constructor

Player* BaseChess::get_low_player(){return this->low_player;}
Player* BaseChess::get_high_player(){return this->high_player;}

Player* BaseChess::get_other_player(Player* play){
	/* fonction permettant de recuperer l'autre joueur de la partie (l'opossant de clui donné en paramètre) */
	
	if (play == this->get_low_player()){return this->get_high_player();}
	else if (play == this->get_high_player()){return this->get_low_player();}
	else{throw MyException(&mout, "probleme get other player");}
}

Player* BaseChess::get_active_player(){return this->active_player;}
Player* BaseChess::get_non_active_player(){return this->get_other_player(this->get_active_player());}

void  BaseChess::set_active_player(Player* a){this->active_player = a;}
void  BaseChess::set_low_player(Player* l){this->low_player = l;}
void  BaseChess::set_high_player(Player* h){this->high_player = h;}

int BaseChess::get_player_row(Player* player){
	/* fonction permettant de savoir la ligne de départ (sur le plateau) d'un joueur donné en paramètre) */
	
	if (player == get_low_player()){return 0;}
	else if (player == get_high_player()){return this->get_plateau()->get_taille()-1;}
	else{throw MyException(&mout, "probleme player cote plateau");}
}

Plateau* BaseChess::get_plateau(){return this->plateau;}
void BaseChess::set_plateau(Plateau* plat){this->plateau = plat;}

Dico* BaseChess::get_dico(){return this->dico;}

std::string BaseChess::get_ret_symbol() const {return "ret";}
std::string BaseChess::get_roc_symbol() const {return "roc";}
std::string BaseChess::get_end_symbol() const {return "end";}
std::string BaseChess::get_lang_symbol() const {return "lang";}
std::string BaseChess::get_liste_depl_symbol() const {return "liste_depl";}
std::string BaseChess::get_liste_capt_symbol() const {return "liste_capt";}

void BaseChess::initial_set_piece(Chesspiece* pe,Player* own,std::string mov){
	/* fonction servant a placer avant que la partie commence les piece d'echec sur le tableau,
	 * c'est a ce moement qu'on leur attribue un propriétaire */
	
	pe->set_owner(own);
	
	std::stringstream ss;
	ss<<pe->get_name()<<","<<pe->get_owner()<<std::endl;
	this->get_active_player()->send_msg(ss.str());
	
	MatPosi* mpos = new MatPosi(mov);	
	this->get_plateau()->set_piece(mpos->to_pair(),pe,true);
}

void BaseChess::initialisation(){
	/* fonction regroupant toutes les actions a faire avant que la partie commence */
	
	this->initialise_board();
	this->initialise_low_pieces();
	this->initialise_high_pieces();
}

void BaseChess::show_bitype_vect(std::vector<BitypeVar<Chesspiece*>> vect){
	/* fonction affichant une vecteur de cases (BitypeVar contenant une piece d'echec)
	 * si la case est vide None est affiché */
	std::stringstream ss_glob;
	
	BitypeVar<Chesspiece*> elem;
	ss_glob<<"[";
	for(long long unsigned int i=0;i<vect.size();i++){
		if (vect[i].get_state() == true){
			
			// !!!!!!!!!!!!!!!!!!!!!!!!!! probleme mout vs std::cout avec heritage --> complexe! --> demander a prof
			//(probleme avec mout<<*(vect[i].get_var())) 
			//solution
			std::stringstream ss;
			ss<<*(vect[i].get_var());
			ss_glob<<ss.str();}
			
		else{ss_glob<<"None";}
		
		if (i != vect.size()-1){ss_glob<<", ";}
	}
	ss_glob<<"]"<<std::endl;
	
	this->get_active_player()->send_msg(ss_glob.str());
}

BitypeVar<std::vector<MatPosi>*>* BaseChess::calculate_zones_between_zones(MatPosi* begin, MatPosi* end){
	/* surcharge de fonction permettant d'ommetre le Player*, qui sera par default le joueur actif */
	
	return calc_zones_between_zones(begin, end, this->get_active_player());
	
}

void BaseChess::changement_langue_input(){
	/* fonction gêrant le changement de langue demandé par le joueur,
	 * langue servant pour tous le affichages de textes */
	
	std::vector<std::string> languages = this->get_dico()->get_possible_laguages();
	
	bool valid = false;
	std::string inp_lang;
	
	while (not valid){
		std::stringstream deb_ss;
		deb_ss<<this->get_dico()->search(this->get_active_player()->get_langue(),"select_lang")<<": ";
		for(long long unsigned int i=0;i<languages.size();i++){
			std::string langue = ((languages)[i]);
			deb_ss<<langue;
						
			if (i < languages.size()-2){deb_ss<<", ";}
			else if (i == languages.size()-2){deb_ss<<" "<<this->get_dico()->search(this->get_active_player()->get_langue(),"et")<<" ";}
			else if (i == languages.size()-1){deb_ss<<std::endl;}
		}
			
		this->get_active_player()->send_msg(deb_ss.str());
			
		inp_lang = this->get_active_player()->recieve_msg();
		valid = is_in_vect(&languages, inp_lang);
	}
			
	this->get_active_player()->set_langue(inp_lang);

}

Trinome<bool,bool,bool>* BaseChess::check_in_for_special_symbol(std::string inp,bool ret_accept){
	/* fonction verifiant si l'input IN est un string particulier (appéle symbole ici)
	 * et qui effectue des actions particuliere solon celle trouvé */
		
	bool found = true, go_back = false, end_game = false;
	
	if ( (ret_accept == true) and (inp == this->get_ret_symbol()) ){go_back = true;}
	else if (inp == this->get_end_symbol()) {end_game = true;}
	else if (inp == this->get_lang_symbol()){this->changement_langue_input();}
	else{found = false;}
	
	Trinome<bool,bool,bool>* res = new Trinome<bool,bool,bool>(found,go_back,end_game);
	return res;
		
}

Trinome<Quadrinome<bool,bool,bool,bool>*, BitypeVar<Chesspiece*>, std::string > BaseChess::check_out_for_special_symbol(BitypeVar<Chesspiece*> in_pe, std::string inp,bool roc_accept){
	/* fonction verifiant si l'input OUT est un string particulier (appéle symbole ici)
	 * et qui effectue des actions particuliere solon celle trouvé */
	
	Chesspiece* pe_in;
	if (in_pe.get_state() == true){
		pe_in = in_pe.get_var();
	}
	else{throw MyException(&mout,"IN invaldie alors que demande de OUT");}
		
	BitypeVar<Chesspiece*> dst;
	
	bool found = true, go_back = false, end_game = false, correspond = false;
	std::string out = inp;
	
	if (inp == this->get_ret_symbol()){go_back = true;}
	else if (inp == this->get_end_symbol()) {end_game = true;}
	
	else if ((roc_accept == false) and (inp == this->get_liste_depl_symbol())) {
		this->get_active_player()->send_msg("liste deplacements : ");
		this->show_possible_mouvement(pe_in, "depl");
		
	}
	else if ((roc_accept == false) and (inp == this->get_liste_capt_symbol())) {
		this->get_active_player()->send_msg("liste capture : ");
		this->show_possible_mouvement(pe_in, "capt");
		
	}
	
	else if (inp == this->get_lang_symbol()){this->changement_langue_input();}
	
	else if ((roc_accept == true) and (inp == this->get_roc_symbol())){
		if (roc_accept == true){
			Trinome<Trinome<bool,bool,bool>*,BitypeVar<Chesspiece*>,std::string>* roc_trinome = this->roc_output_check(in_pe);
			
			//
			
			Trinome<bool,bool,bool>* trinome_bool_res = roc_trinome->get_first();
			go_back = trinome_bool_res->get_first();
			correspond = trinome_bool_res->get_second();
			end_game = trinome_bool_res->get_third();
			
			dst = roc_trinome->get_second();
			out = roc_trinome->get_third();				
			//
			
			
		}
		else{this->get_active_player()->send_msg(this->get_dico()->search(this->get_active_player()->get_langue(),"roc_pe_imp"),true);}
	}
	
	else{found = false;}
	
	Quadrinome<bool,bool,bool,bool>* info_res = new Quadrinome<bool,bool,bool,bool>(found,go_back,correspond,end_game);
	Trinome<Quadrinome<bool,bool,bool,bool>*, BitypeVar<Chesspiece*>, std::string > res = Trinome<Quadrinome<bool,bool,bool,bool>*, BitypeVar<Chesspiece*>, std::string >(info_res,dst,out);
	
	return res;
		
}

Trinome<std::string,BitypeVar<Chesspiece*>,std::pair<bool,bool>>* BaseChess::in_input(Interpret* first_comment, Interpret* second_comment,Interpret* third_comment,bool ret_accept){
	/* l'input IN est l'input déterminant principalement la piece a sellectionner dans le tableau */
	
	BitypeVar<Chesspiece*> dst;
	std::pair<int,int> conv;
	Chesspiece* cap_piece;
	
	bool go_back = false;
	bool end_game = false;
	
	bool symbol_found;
	bool part_a = false;
	
	std::string in = "";
	while (not part_a and not go_back and not end_game){
		
		this->get_active_player()->send_msg(first_comment->get_text(this->get_active_player()->get_langue()),true);
		
		in = this->get_active_player()->recieve_msg();
		
		Trinome<bool,bool,bool>* symbol_info = this->check_in_for_special_symbol(in,ret_accept);
		symbol_found = symbol_info->get_first();
		
		if (symbol_found == false){

			bool valid,again;
				
			again = false;
			valid = this->verify_validity_input(in);
			
			if (valid == true){
				MatPosi* mpos_in = new MatPosi(in);
				dst = this->get_plateau()->get_piece(mpos_in->to_pair());
				
				if (dst.get_state() == true){
					cap_piece = dst.get_var();
					//mout<<"propio = "<<cap_piece->get_owner()<<std::endl;
					if (cap_piece->get_owner() != get_active_player()){
						this->get_active_player()->send_msg(second_comment->get_text(this->get_active_player()->get_langue()),true);
						again = true;
					}
				}
				else{
					this->get_active_player()->send_msg(third_comment->get_text(this->get_active_player()->get_langue()),true);
					again = true;
				}
					
				part_a = not(again);
			}
			else{part_a = false;}
		}
		else{		
			go_back = symbol_info->get_second();
			end_game = symbol_info->get_third();
		}
	}
	
	Trinome<std::string,BitypeVar<Chesspiece*>,std::pair<bool,bool>>* res = new Trinome<std::string,BitypeVar<Chesspiece*>,std::pair<bool,bool>>(in,dst,std::make_pair(go_back,end_game));
		
	return res;
}

Trinome<std::string,BitypeVar<Chesspiece*>,std::pair<bool,bool>>* BaseChess::in_input(Interpret* first_comment, Interpret* second_comment,Interpret* third_comment){
	/* surchage de fonction permettant d'ommetre le bool indiuant si un retour en arrière est permis */
	return this->in_input(first_comment, second_comment,third_comment,false);
}

Trinome<std::string,BitypeVar<Chesspiece*>,std::pair<bool,bool>>* BaseChess::in_depl_input(){
	/* depl en opossition avec roc, en effet cette fonction demnade un input de type IN et définit des messages d'erreurs différentes de sa variante roc */
	
	Interpret* interpret_one = new Interpret(this->get_dico());
	
	interpret_one->add_text("pe_a_depl", true, true);
	interpret_one->add_text("ou", false, true);
	
	// " end "
	interpret_one->add_text(" ", false, false);
	interpret_one->add_text(this->get_end_symbol(), false, false);
	interpret_one->add_text(" ", false, false);

	interpret_one->add_text(this->get_end_symbol(), true, true);
	
	interpret_one->add_text("ou", false, true);
	
	// " lang "
	interpret_one->add_text(" ", false, false);
	interpret_one->add_text(this->get_lang_symbol(), false, false);
	interpret_one->add_text(" ", false, false);
	
	interpret_one->add_text(this->get_lang_symbol(), false, true);
	
	
	Interpret* interpret_two = new Interpret(this->get_dico());
	
	interpret_two->add_text("retry", false, true);
	interpret_two->add_text(", ", false, false);
	interpret_two->add_text("move_pe_oth", false, true);
	
	
	Interpret* interpret_three = new Interpret(this->get_dico());
	
	interpret_three->add_text("retry", false, true);
	interpret_three->add_text(", ", false, false);
	interpret_three->add_text("empty", false, true);
	
	return this->in_input(interpret_one, interpret_two, interpret_three);
}

Trinome<std::string,BitypeVar<Chesspiece*>,std::pair<bool,bool>>* BaseChess::in_roc_input(){
	/* roc en opossition avec depl, en effet cette fonction demnade un input de type IN et définit des messages d'erreurs différentes de sa variante depl */
	
	Interpret* interpret_one = new Interpret(this->get_dico());
	
	interpret_one->add_text("roc_pe", true, true);
	interpret_one->add_text("ou", false, true);
	
	// " ret "
	interpret_one->add_text(" ", false, false);
	interpret_one->add_text(this->get_ret_symbol(), false, false);
	interpret_one->add_text(" ", false, false);
	
	interpret_one->add_text(this->get_ret_symbol(), true, true);
	
	interpret_one->add_text("ou", false, true);
	
	// " end "
	interpret_one->add_text(" ", false, false);
	interpret_one->add_text(this->get_end_symbol(), false, false);
	interpret_one->add_text(" ", false, false);
	
	interpret_one->add_text(this->get_end_symbol(), true, true);
	
	interpret_one->add_text("ou", false, true);
	
	// " lang "
	interpret_one->add_text(" ", false, false);
	interpret_one->add_text(this->get_lang_symbol(), false, false);
	interpret_one->add_text(" ", false, false);

	interpret_one->add_text(this->get_lang_symbol(), false, true);
	
	Interpret* interpret_two = new Interpret(this->get_dico());
	
	interpret_two->add_text("retry", false, true);
	interpret_two->add_text(", ", false, false);
	interpret_two->add_text("roc_oth", false, true);
	
	
	Interpret* interpret_three = new Interpret(this->get_dico());
	
	interpret_three->add_text("retry", false, true);
	interpret_three->add_text(", ", false, false);
	interpret_three->add_text("roc_empty", false, true);
		
	return this->in_input(interpret_one, interpret_two, interpret_three,true);
}

bool BaseChess::check_illegal_move(std::string in,std::string out){
	/* fonction qui vérifie si un mouvement est autorisé, si nécéssaire affiche un message d'echec,
	 * revoi un bool pour indiquer si l'input doit être recommancé */
	
	bool again;
	if (not(this->verify_move(in,out))){
		
		std::stringstream ss;
		ss<<this->get_dico()->search(this->get_active_player()->get_langue(),"retry")<<", "<< this->get_dico()->search(this->get_active_player()->get_langue(),"illegal_move")<<"!"<<std::endl;
		this->get_active_player()->send_msg(ss.str());
		
		again = true;
		}
	else{again = false;}
	return again;
}



bool BaseChess::verify_possible_roc(Roi* roi,Tour* tour){
	/* fonction qui ércupère les positions du roi et de la tour passé en paramètre et qu les transmet a une fonction qui calcule
	 * si un roc est permis */
	
	MatPosi mpos_roi = MatPosi(*(roi->get_posi()));
	MatPosi mpos_tour = MatPosi(*(tour->get_posi()));
	
	BitypeVar<std::pair<MatPosi*, MatPosi*>>* info = this->sort_mpos_and_calc_roc_info(&mpos_roi,&mpos_tour);
	
	return info->get_state();
	
}

Trinome<Trinome<bool,bool,bool>*,BitypeVar<Chesspiece*>,std::string>* BaseChess::roc_first_pe_is_waiting(Chesspiece* pe){
	/* fonction qui est la 2e partie de la verification du roc, c'est une partie qui se déroule alors que la 1e piece du roc a déjà été selectionné et validé */
	
	bool correspond = false;
	bool go_back = false;
	std::string out;
	BitypeVar<Chesspiece*> dst;
	Trinome<std::string,BitypeVar<Chesspiece*>,std::pair<bool,bool>>* roc_trinome;
	std::pair<bool,bool> roc_bool_info;
	
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
	
	bool end_game = false;
	while (not(correspond) and not(go_back) and not(end_game)){
			
		roc_trinome = this->in_roc_input();
		out = roc_trinome->get_first();
		
		roc_bool_info = roc_trinome->get_third();
		go_back = roc_bool_info.first;
		end_game = roc_bool_info.second;
		
		if (not(go_back) and not(end_game)){
		
			dst = roc_trinome->get_second();
			
			if (in_is_king == true){correspond = verifier_type_pe<Tour>(dst);}
			else{correspond = verifier_type_pe<Roi>(dst);}

			if (correspond == true){
				
				if (in_is_king == true){tour = dynamic_cast<Tour*>(dst.get_var());}
				else{roi = dynamic_cast<Roi*>(dst.get_var());}
				
				correspond = this->verify_possible_roc(roi,tour);

				if (correspond == false){this->get_active_player()->send_msg(this->get_dico()->search(this->get_active_player()->get_langue(),"not_pos_roc"),true);}
				else{
					
					// verfication de deplacement
					if (in_is_king == true){
						
						if(tour->get_has_moved() == true){
							correspond = false;
							this->get_active_player()->send_msg(this->get_dico()->search(this->get_active_player()->get_langue(),"roc_tower_no_perm_move"),true);
						}
					}
					else{
						
						if(roi->get_has_moved() == true){
							correspond = false;
							this->get_active_player()->send_msg(this->get_dico()->search(this->get_active_player()->get_langue(),"roc_king_no_perm_move"),true);
						}
					}
				}
			}
			else{
				
				std::stringstream ss;
				
				if (in_is_tour == true){ss<<this->get_dico()->search(this->get_active_player()->get_langue(),"roc_imp_chess")<<" "<<this->get_dico()->search(this->get_active_player()->get_langue(),"chess_tour")<<std::endl;}
				else{ss<<this->get_dico()->search(this->get_active_player()->get_langue(),"roc_imp_chess")<<" "<<this->get_dico()->search(this->get_active_player()->get_langue(),"chess_roi")<<std::endl;}
				
				this->get_active_player()->send_msg(ss.str());
				
			}
		}
	}
	
	Trinome<bool,bool,bool>* trinome_bool_res = new Trinome<bool,bool,bool>(go_back,correspond,end_game);
	Trinome<Trinome<bool,bool,bool>*,BitypeVar<Chesspiece*>,std::string>* res = new Trinome<Trinome<bool,bool,bool>*,BitypeVar<Chesspiece*>,std::string>(trinome_bool_res,dst,out);
	
	return res;
	
	
}

Trinome<Trinome<bool,bool,bool>*,BitypeVar<Chesspiece*>,std::string>* BaseChess::roc_output_check(BitypeVar<Chesspiece*> in_pe){
	/* fonction lancé suite a une demande de roc en ayant spécifié une piece sur deux */
	
	Chesspiece* in_piece;
	Trinome<Trinome<bool,bool,bool>*,BitypeVar<Chesspiece*>,std::string>* res;

	if (in_pe.get_state() == true){
		in_piece = in_pe.get_var();
								
		if(Roi* roi = dynamic_cast<Roi*>(in_piece)){
			if (roi->get_has_moved() == false){
				res = this->roc_first_pe_is_waiting(roi);
			}
			else{this->get_active_player()->send_msg(this->get_dico()->search(this->get_active_player()->get_langue(),"roc_king_no_perm_move"),true);}
		}
		
		else if(Tour* tour = dynamic_cast<Tour*>(in_piece)) {
			if (tour->get_has_moved() == false){
				res = this->roc_first_pe_is_waiting(tour);
			}
			else{this->get_active_player()->send_msg(this->get_dico()->search(this->get_active_player()->get_langue(),"roc_tower_no_perm_move"),true);}
		}
		
		else{this->get_active_player()->send_msg(this->get_dico()->search(this->get_active_player()->get_langue(),"roc_pe_imp"),true);}
		
	}
	// else case vide (d'office non-selectionnable !)
	
	return res;
}

void BaseChess::show_depl_possibles(Chesspiece* pe){
	/* fonction qui s'occupe d'afficher les liste de deplacements et de captures possibles
	 * paramètre d'entree : une piece d'echec
	 * */
	
	this->get_active_player()->send_msg(this->get_dico()->search(this->get_active_player()->get_langue(),this->get_liste_depl_symbol()),false);
	this->get_active_player()->send_msg(" : ",false);
	this->show_possible_mouvement(pe, "depl");
	
	this->get_active_player()->send_msg(this->get_dico()->search(this->get_active_player()->get_langue(),this->get_liste_capt_symbol()),false);
	this->get_active_player()->send_msg(" : ",false);
	this->show_possible_mouvement(pe, "capt");
	
}

void BaseChess::show_depl_possibles(std::string str_co){
	/* fonction qui s'occupe d'afficher les liste de deplacements et de captures possibles
	 * paramètre d'entree : une coordonée de piece d'echec
	 * */
	 
	BitypeVar<Chesspiece*> zone;
	Chesspiece* pe;
	
	MatPosi* mpos = new MatPosi(str_co);
	zone = this->get_plateau()->get_piece(mpos->to_pair());
	pe = zone.get_var();
	
	this->show_depl_possibles(pe);
	
}

Trinome<std::pair<std::string,BitypeVar<Chesspiece*>>,std::pair<std::string,BitypeVar<Chesspiece*>>,std::pair<bool,bool>>* BaseChess::ask_for_input(){
	/* fonction principale des inputs, en effet c'est la fonction qui gêre la demande d'input au joueur (in, out) */
	
	std::stringstream ss;
	ss<<this->get_active_player()<<" "<<this->get_dico()->search(this->get_active_player()->get_langue(),"your_turn")<<"!"<<std::endl;
	this->get_active_player()->send_msg(ss.str());
	
	Trinome<std::string,BitypeVar<Chesspiece*>,Trinome<bool,bool,bool>*>* out_p;
		
	Trinome<std::string,BitypeVar<Chesspiece*>,std::pair<bool,bool>>* in_p;
	
	std::string in,out;
	
	bool again = true;
	BitypeVar<Chesspiece*> adv_pe_out;
	BitypeVar<Chesspiece*> adv_pe_in;
	Trinome<bool,bool,bool>* trinome_out_info;
	
	std::pair<bool,bool> pair_in_info;
	
	
	bool switch_pos = false;
	bool end_game = false;
	while (again and not end_game){
		in_p = this->in_depl_input();
		in = in_p->get_first();
		adv_pe_in = in_p->get_second();
		
		pair_in_info = in_p->get_third();
		//go_back = pair_in_info.first; on peut le recup mais sera tjs false car return pas admis dans "in"
		end_game = pair_in_info.second;
		
		if (end_game == false){
		
			this->show_depl_possibles(in);
			
			out_p = this->out_input(in,adv_pe_in);
					
			out = out_p->get_first();
			adv_pe_out = out_p->get_second();
			
			trinome_out_info = out_p->get_third();
			again = trinome_out_info->get_first();
			switch_pos = trinome_out_info->get_second();
			end_game = trinome_out_info->get_third();
		}
		
	}
		
	std::pair<std::string,BitypeVar<Chesspiece*>> in_paire = std::make_pair(in,adv_pe_in);
	std::pair<std::string,BitypeVar<Chesspiece*>> out_paire = std::make_pair(out,adv_pe_out);
	
	Trinome<std::pair<std::string,BitypeVar<Chesspiece*>>,std::pair<std::string,BitypeVar<Chesspiece*>>,std::pair<bool,bool>>* result = new Trinome<std::pair<std::string,BitypeVar<Chesspiece*>>,std::pair<std::string,BitypeVar<Chesspiece*>>,std::pair<bool,bool>>(in_paire,out_paire,std::make_pair(end_game,switch_pos));
	
	return result;
}

bool BaseChess::verify_validity_input(std::string inp){
	/* fonction qui vérifie si un input est valide, c.a.d si elle est bien composé d'une partie lettre suivi d'une paretie chiffre,
	 * sans autres parasites */
	 
	MatPosi mpos;
	bool valid_coord = mpos.isvalid_coord(inp);
		
	bool res = false;
	if (valid_coord == true){
		if (this->verify_in_board(inp)){res = true;}
		else{
			std::stringstream ss_one;
			ss_one<<this->get_dico()->search(this->get_active_player()->get_langue(),"retry")<<", "<< this->get_dico()->search(this->get_active_player()->get_langue(),"co_ext")<<std::endl;
			this->get_active_player()->send_msg(ss_one.str());
		}
	}
	else{
		std::stringstream ss_two;
		ss_two<<this->get_dico()->search(this->get_active_player()->get_langue(),"retry")<<", "<< this->get_dico()->search(this->get_active_player()->get_langue(),"co_inv")<<std::endl;
		this->get_active_player()->send_msg(ss_two.str());
	}
	return res;
}

void BaseChess::change_active_player(){
	/* fonction qui change le joueur référencé par le titre "actif" qui veut dire "en train de jouer / ayant la main"*/
	if (this->get_active_player() == get_low_player()){set_active_player(get_high_player());}
	else if (this->get_active_player() == get_high_player()){set_active_player(get_low_player());}
	else{throw MyException(&mout, "probleme active player change");}
}

bool BaseChess::verify_in_board(std::string s){
	/* fonction qui vérifie si une coordonée se trouve bien dans les limites du plateau */
	MatPosi* mpos = new MatPosi(s);	
	return this->get_plateau()->verify_in_board(mpos->to_pair());
}

void BaseChess::print_mpos_vect(std::vector<MatPosi*>* vect,bool endline){
	/* fonction qui affiche un vecteur de MatPosi* */
	
	std::stringstream ss;
	
	ss<<"[";
	for(long long unsigned int i=0;i<vect->size();i++){
		
		ss<<((*vect)[i])->to_string();
		
		if (i<(vect->size()-1)){ss<<", ";}
		
	}
	ss<<"]";
	
	this->get_active_player()->send_msg(ss.str(),endline);
		
}

void BaseChess::print_mpos_vect(std::vector<MatPosi*>* vect){
	/* fonction surchargée qui permet d'ommetre de booléen qui indique si on veut un retour a la ligne */
	this->print_mpos_vect(vect,true);
	
}

BitypeVar<std::pair<MatPosi*,MatPosi*>>* BaseChess::sort_mpos_and_calc_roc_info(MatPosi* mpos_one,MatPosi* mpos_two){
	/* fonction qui trié des MatPosi reçu en paramètres et qui calcule les destination des 2 MatPosi suite a un roque */
	
	std::pair<MatPosi*,MatPosi*> sorted_mpos_pair = sort_two_mpos(mpos_one, mpos_two);
	MatPosi* mpos_gauche = sorted_mpos_pair.first;
	MatPosi* mpos_droite = sorted_mpos_pair.second;

	BitypeVar<std::vector<MatPosi>*>* bit_vect = this->calculate_zones_between_zones(mpos_gauche, mpos_droite);
	
	MatPosi* mpos_roi_dst;
	MatPosi* mpos_tour_dst;
	
	bool valid_roc = false;
	
	if (bit_vect->get_state() == true){
		
		std::vector<MatPosi>* between_vect = bit_vect->get_var();
		
		// si toutes les cases intermédiares sont vides: 
		long long unsigned int i=0;
		bool stop = false;
		while (i<between_vect->size() and stop == false){
			
			if(not(this->get_plateau()->is_empty_location(((*between_vect)[i]).to_pair()))){
				stop = true;
			};
			i++;
		}
		
		valid_roc = not(stop);
		if (valid_roc == true){
		
			BitypeVar<Chesspiece*> bit_chess_gauche = this->get_plateau()->get_piece(mpos_gauche->to_pair());
			if (bit_chess_gauche.get_state() == false){throw MyException(&mout,"recup chesspiece de case vide");}
			
			bool gauche_isking = verifier_type_pe<Roi>(bit_chess_gauche);
			
			std::pair<int,int> coords = calc_roc_destinations(gauche_isking,between_vect);
			int co_roi_dst = coords.first;
			int co_tour_dst = coords.second;
			
			mpos_roi_dst = &((*between_vect)[co_roi_dst]);
			mpos_tour_dst = &((*between_vect)[co_tour_dst]);
			
			std::stringstream ss_gauche;
			ss_gauche<<"gauche = "<<mpos_gauche->to_string()<<", droite = "<<mpos_droite->to_string()<<std::endl;
			this->get_active_player()->send_msg(ss_gauche.str());
			
			std::stringstream ss_droite;
			ss_droite<<"dst roi = "<<mpos_roi_dst->to_string()<<", dst tour = "<<mpos_tour_dst->to_string()<<std::endl;
			this->get_active_player()->send_msg(ss_droite.str());
			
			// si le roi n'est pas en danger avant le roque:
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
			this->get_active_player()->send_msg(ss_roc_av.str());
			
			if (valid_roc == true){
				
				// si le roi n'est pas en danger apres le roque:
				BitypeVar<MatPosi*>* dang_roi_ap = this->is_endangered(mpos_roi_dst,this->get_non_active_player());
				
				valid_roc = not(dang_roi_ap->get_state());
				
				std::stringstream ss_roc_ap;
				ss_roc_ap<<"valid roc dang ap"<<valid_roc<<std::endl;
				this->get_active_player()->send_msg(ss_roc_ap.str());
				
				if (valid_roc == true){
				
					std::vector<MatPosi*>* king_steps_vect = calc_king_move_path((verifier_type_pe<Roi>(bit_chess_gauche) == true),co_roi_dst,between_vect);
					// si les cases par lequel passe le roi ne sont pas en danger:
					
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
					this->get_active_player()->send_msg("etapes rois: ");
					this->print_mpos_vect(king_steps_vect);
					
					std::stringstream ss_king_steps;
					ss_king_steps<<"valid king steps ? "<<valid_roc<<std::endl;
					this->get_active_player()->send_msg(ss_king_steps.str(),true); // true ok car on souhaite une ligne d'espace
				}
			}
		}
	}
	else{throw MyException(&mout,"vecteur des zones entres 2 zones invalide");}
	
	BitypeVar<std::pair<MatPosi*,MatPosi*>>* res = new BitypeVar<std::pair<MatPosi*,MatPosi*>>();
	res->set_state(valid_roc);
	res->set_var(std::make_pair(mpos_roi_dst,mpos_tour_dst));
	
	return res; // retourner si roque ok (bool) et positions si ok
}

bool BaseChess::exec_roc(MatPosi* mpos_one,MatPosi* mpos_two){
	/* fonction d'execution du roque,test de validité puis mouvement si valide
	 * retourne si le roc était validé */
		
	BitypeVar<std::pair<MatPosi*,MatPosi*>>* info = this->sort_mpos_and_calc_roc_info(mpos_one,mpos_two);
	
	bool valid_roc = info->get_state();
	
	if (valid_roc == true){
		
		std::pair<MatPosi*,MatPosi*> dst_pair = info->get_var();
		MatPosi* mpos_roi_dst = dst_pair.first;
		MatPosi* mpos_tour_dst = dst_pair.second;
		
		bool one_isking = verifier_type_pe<Roi>(this->get_plateau()->get_piece(mpos_one->to_pair()));
		
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
		//rois --> dest tour, et tour --> dest roi, puis switch position (fait ce cette façon pour pouvoir plustard faire une sort de cinematique/ monter visuelmment l'inversion de place)
		this->exec_move(mpos_roi_ini, mpos_tour_dst);
		this->exec_move(mpos_tour_ini, mpos_roi_dst);
		
		this->get_plateau()->switch_positions(mpos_roi_dst->to_pair(),mpos_tour_dst->to_pair());
	}
	
	return valid_roc;
	
}

void BaseChess::exec_move(MatPosi* mpos_in, MatPosi* mpos_out, bool switch_mode){
	/* fonction d'execution du mouvement, un bool switch_mode permet a la fonction de savoir si elle doit faire un depl normal ou un roque
	 * version avec 2 MatPosi en entree */

	std::pair<int,int> pair_in = mpos_in->to_pair();
	std::pair<int,int> pair_out = mpos_out->to_pair();
	
	if (switch_mode == false){this->get_plateau()->move(pair_in,pair_out);}
	else{this->exec_roc(mpos_in,mpos_out);}
}

void BaseChess::exec_move(MatPosi* mpos_in, MatPosi* mpos_out){
	/* fonction surchargée, permettant d'ommetre le bool indiquant le deplacement ou le roque */
	
	this->exec_move(mpos_in, mpos_out, false);
}

void BaseChess::exec_move(std::string str_in, std::string str_out, bool switch_mode){
	/* fonction d'execution du mouvement, un bool switch_mode permet a la fonction de savoir si elle doit faire un depl normal ou un roque
	 * version avec 2 strings de coordonées en entree */
	
	MatPosi* mpos_in = new MatPosi(str_in);
	MatPosi* mpos_out = new MatPosi(str_out);
	
	this->exec_move(mpos_in, mpos_out, switch_mode);
}

void BaseChess::exec_move(std::string str_in, std::string str_out){
	/* fonction surchargée, permettant d'ommetre le bool indiquant le deplacement ou le roque */
	this->exec_move(str_in, str_out, false);
}

void BaseChess::exec_move(std::pair<int,int> pair_in, std::pair<int,int> pair_out, bool switch_mode){
	/* fonction d'execution du mouvement, un bool switch_mode permet a la fonction de savoir si elle doit faire un depl normal ou un roque
	 * version avec 2 paires de coordonees en entree */
	
	MatPosi* mpos_in = new MatPosi(pair_in);
	MatPosi* mpos_out = new MatPosi(pair_out);
	
	this->exec_move(mpos_in, mpos_out, switch_mode);
}

void BaseChess::exec_move(std::pair<int,int> pair_in, std::pair<int,int> pair_out){
	/* fonction surchargée, permettant d'ommetre le bool indiquant le deplacement ou le roque */
	this->exec_move(pair_in, pair_out, false);
}

bool BaseChess::verify_move(MatPosi* in, MatPosi* out, std::string mode){
	/* fonction vérifiant si un mouvement de piece est possible
	 * version avec 2 MatPosi en entree */
	
	BitypeVar<Chesspiece*> bi_t_in = this->get_plateau()->get_piece(in->to_pair());
	BitypeVar<Chesspiece*> bi_t_out = this->get_plateau()->get_piece(out->to_pair());
	
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

bool BaseChess::verify_move(MatPosi* in, MatPosi* out){
	/* fonction surchargée, permettant d'ommetre le string indiquant le mode de la verification */
	return this->verify_move(in, out, "");
}

bool BaseChess::verify_move(std::string in, std::string out, std::string mode){
	/* fonction vérifiant si un mouvement de piece est possible
	 * version avec 2 strings de coordonees en entree */
	
	MatPosi* mpos_in = new MatPosi(in);
	MatPosi* mpos_out = new MatPosi(out);
	
	return this->verify_move(mpos_in, mpos_out, mode);
}

bool BaseChess::verify_move(std::string in, std::string out){
	/* fonction surchargée, permettant d'ommetre le string indiquant le mode de la verification */
	return this->verify_move(in, out, "");
}

bool BaseChess::verify_move(std::pair<int,int> in, std::pair<int,int> out, std::string mode){
	/* fonction vérifiant si un mouvement de piece est possible
	 * version avec 2 paires de coordonees en entree */
	
	MatPosi* mpos_in = new MatPosi(in);
	MatPosi* mpos_out = new MatPosi(out);
	
	return this->verify_move(mpos_in, mpos_out, mode);
}

bool BaseChess::verify_move(std::pair<int,int> in, std::pair<int,int> out){
	/* fonction surchargée, permettant d'ommetre le string indiquant le mode de la verification */
	return this->verify_move(in, out, "");
}

std::vector<MatPosi*>* BaseChess::check_possible_mouvement(Chesspiece* pe ,std::string mode){
	/* fonction qui récupère tout les mouvements possiles d'une piece */
	
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

		keep = this->check_danger_mouvement_and_path(paire_origi, adv_tup, paire, mode); // verification concrète si ce déplacement est authorisé
		
		if (keep == true){
			res->push_back(elem);
		}
	}
	
	return res;
}

BitypeVar<std::vector<AdvTuple*>*>* BaseChess::find_linking_advtuple(std::pair<int,int> pair_in, std::pair<int,int> pair_out, std::string mode){
	/* fonction qui récupère trouve les Advtuples liant les 2 coordonées via la recheche de la 2e coordonnes dans la liste de deplacement de la premiere
	 * (il y a concervation de l'advtuple originel pour chaque deplacement possible généré) */
	BitypeVar<std::vector<AdvTuple*>*>* found;
	BitypeVar<Chesspiece*> tup_in = this->get_plateau()->get_piece(pair_in);
	
	std::vector<AdvTuple*>* res = new std::vector<AdvTuple*>();
	
	if (tup_in.get_state() == true){
		Chesspiece* pe_in = tup_in.get_var();
		
		MatPosi* mpos_out = new MatPosi(pair_out);
		
		std::vector<std::pair<std::pair<int,int>,AdvTuple>> vect = pe_in->algo(mode);
		
		found = new BitypeVar<std::vector<AdvTuple*>*>();
		found->set_state(false);
		
		long long unsigned int i=0;
		while(i<vect.size() and (found->get_state() == false)){
			MatPosi* mpos_elem = new MatPosi(vect[i].first);
			
			if (*mpos_elem == *mpos_out){
				//found->set_var(&(vect[i].second));
				if (found->get_state() == false){found->set_state(true);}
				res->push_back(&(vect[i].second));
			}
			
			i++;
		}
	}
	else{throw MyException(&mout, "demande de find_linking_advtuple() sur case vide en entree !");}
	
	found->set_var(res);
	
	return found;
}

bool BaseChess::complete_danger_test(std::pair<int,int> pair_in, std::pair<int,int> pair_out, std::string mode){
	/* fonction qui recerche si le mouvement d'une piece est sécurisé (en terme de danger d'être capturée) */
	bool keep = false;
	BitypeVar<std::vector<AdvTuple*>*>* bit_var = this->find_linking_advtuple(pair_in, pair_out, mode);
	
	//mout << "link advt state check";
	
	if (bit_var->get_state() == true){
		
		std::vector<AdvTuple*>* advtuples_vect = bit_var->get_var();

		long long unsigned int i=0;
		while (i<advtuples_vect->size() and keep == false){ // si un chemin sécurisé cela suffit
			
			AdvTuple adv_tup = *((*advtuples_vect)[i]);
			
			//mout << "link advt"<<adv_tup<<std::endl;
			
			keep = this->check_danger_mouvement_and_path(pair_in, adv_tup, pair_out, mode);
			//mout << "result keep"<<keep<<std::endl;
		
			i++;
		}
	}
	
	return keep;
	
}

void BaseChess::show_possible_mouvement(Chesspiece* pe ,std::string mode){
	/* fonction qui affiche les mouvements possibles d'une piece */
	
	std::vector<MatPosi*>* vect = this->check_possible_mouvement(pe, mode);
	
	std::vector<std::string>* stock = new std::vector<std::string>();
	
	std::stringstream ss;
	
	ss<<"[";
	for(long long unsigned int i=0;i<vect->size();i++){
		std::string temp = (*vect)[i]->to_string();
		if (not(is_in_vect(stock,temp))){
			if (i != 0){ss<<", ";}
			ss<<temp;
			stock->push_back(temp);
		}
	}
	ss<<"]";
	
	this->get_active_player()->send_msg(ss.str(),true);
}

Chesspiece* BaseChess::ask_evolution_input(std::vector<Chesspiece*>* vect){
	/* fonction demandant le choix d'évolution que l'on veut faire pour son pion
	 * recoit en paramètre une liste de type parmis lequel a choisir */
	
	Chesspiece* res;
	bool found = false;
	std::string in;
	while (found == false){
		
		std::stringstream deb_ss;
		
		deb_ss<<this->get_dico()->search(this->get_active_player()->get_langue(),"choix_evolve")<<": ";
		for(long long unsigned int i=0;i<vect->size();i++){
			
			std::stringstream temp_ss;
			temp_ss<<"Nom_"<<*((*vect)[i]);

			deb_ss<<this->get_dico()->search(this->get_active_player()->get_langue(),temp_ss.str());
			
			if (i < vect->size()-2){deb_ss<<", ";}
			else if (i == vect->size()-2){deb_ss<<" "<<this->get_dico()->search(this->get_active_player()->get_langue(),"et")<<" ";}
			else if (i == vect->size()-1){deb_ss<<std::endl;}
		
		}
		
		this->get_active_player()->send_msg(deb_ss.str());
		
		in = this->get_active_player()->recieve_msg();
		
		std::stringstream end_ss;
		
		long long unsigned int j=0;
		while ((found == false) and (j<vect->size())){
		
			std::stringstream ss;
			ss<<"Nom_"<<*((*vect)[j]);
			
			end_ss<<in<<"VS"<<this->get_dico()->search(this->get_active_player()->get_langue(),ss.str())<<std::endl;
			if (in == this->get_dico()->search(this->get_active_player()->get_langue(),ss.str())){
				found = true;
				res = (*vect)[j];
			}
			
			j++;
		}
		if (found == false){end_ss<<this->get_dico()->search(this->get_active_player()->get_langue(),"retry")<<std::endl;}
		
		this->get_active_player()->send_msg(end_ss.str());
		
	}
	return res;
}

void BaseChess::check_evolution(){
	/* fonction vérifiant si un pion peut évoluer et qui demande en quele type le pion doit obtenir */
	
	std::stringstream ss;
	
	ss<<"debut check_evolution() !"<<std::endl;
	int num_row = this->get_player_row(this->get_non_active_player());
	std::vector<BitypeVar<Chesspiece*>> lig = this->get_plateau()->get_row(num_row);
	
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
		
		Chesspiece* nv_pe = ask_evolution_input(chess_vect);
		
		nv_pe->set_owner(this->get_active_player());
		this->get_plateau()->set_piece(paire,nv_pe);
		
	}
	
	ss<<"fin check_evolution() !"<<std::endl;
	
	this->get_active_player()->send_msg(ss.str());
	
}

bool BaseChess::can_escape_position(Chesspiece* pe ,std::string mode){
	/* fonction qui verifie si une piece peut s'echapper de sa position actuelle
	 * c.a.d : se déplacer ailleur sans être menacée par une piece (qui pourrait la prendre a son tour) */
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

bool BaseChess::can_actif_player_move(){
	/* fonction implémenté en vue du pat */ 
	
	int taille = this->get_plateau()->get_taille();
		
	bool escape = false;

	int cnt = this->get_plateau()->begin_position();
	int end_cnt = this->get_plateau()->end_position();
		
	BitypeVar<int>* bit = new BitypeVar<int>(false,0);
	BitypeVar<int>* plat_size = new BitypeVar<int>(true,taille);

	while (cnt <= end_cnt and not escape){
		
		PlatPosi* ppos = new PlatPosi(cnt,*bit,*plat_size);
		std::pair<int,int> paire = ppos->to_pair();
		delete ppos;
		
		if (not(this->get_plateau()->is_empty_location(paire))){
			Chesspiece* pe = this->get_plateau()->get_piece(paire).get_var();
			if (this->get_active_player() == pe->get_owner()){
				
				escape = this->can_escape_position(pe ,"depl");
				if (not(escape)){escape = this->can_escape_position(pe ,"capt");}
				
			}
		}
		cnt++;
	}
	
	
	return escape;
	
}

bool BaseChess::more_dangers_part(std::pair<int,int> paire_zone, Player* limitator,int taille,std::string mode){
	/* fonction étant une sous-fonction de "check_more_than_one_danger"
	 * fonction qui vérifie si la piece est menacée par plus qu'une piece adverse
	 * (ou dans le cas d'une case vide si elle est menacée par n'importe qu'elle piece) */
		
	int count = 0;
	
	int cnt = this->get_plateau()->begin_position();
	int end_cnt = this->get_plateau()->end_position();
		
	BitypeVar<int>* bit = new BitypeVar<int>(false,0);
	BitypeVar<int>* plat_size = new BitypeVar<int>(true,taille);
	
	while (cnt <= end_cnt and count < 2){
				
		PlatPosi* ppos = new PlatPosi(cnt,*bit,*plat_size);
		std::pair<int,int> paire = ppos->to_pair();
		delete ppos;
		
		if (not(this->get_plateau()->is_empty_location(paire))){				
			if ((limitator->get_name() == "") or ((limitator->get_name() != "") and (limitator == this->get_plateau()->get_piece(paire).get_var()->get_owner()))){
				bool compl_danger = this->complete_danger_test(paire,paire_zone,mode);
				if (compl_danger == true){count +=1;}
			}
		}
		cnt++;
	}

	return (count >= 2);
}

BitypeVar<MatPosi*>* BaseChess::in_endangered_part(std::pair<int,int> paire_zone, Player* limitator,int taille,std::string mode){
	/* fonction étant une sous-fonction de "is_endangered"
	 * fonction qui vérifie si la piece est menacée par une piece adverse, si oui elle la retourne.
	 * (ou dans le cas d'une case vide si elle est menacée par n'importe qu'elle piece, si oui elle la retourne) */
	 
	BitypeVar<MatPosi*>* danger = new BitypeVar<MatPosi*>();

	int cnt = this->get_plateau()->begin_position();
	int end_cnt = this->get_plateau()->end_position();
		
	BitypeVar<int>* bit = new BitypeVar<int>(false,0);
	BitypeVar<int>* plat_size = new BitypeVar<int>(true,taille); // this->get_plateau()->get_taille()

	while (cnt <= end_cnt and danger->get_state() == false){
				
		PlatPosi* ppos = new PlatPosi(cnt,*bit,*plat_size);
		std::pair<int,int> paire = ppos->to_pair();
		MatPosi* mpos = ppos;
		delete ppos;
		
		if (not(this->get_plateau()->is_empty_location(paire))){
			if ((limitator->get_name() == "") or ((limitator->get_name() != "") and (limitator == this->get_plateau()->get_piece(paire).get_var()->get_owner()))){
				bool compl_danger = this->complete_danger_test(paire,paire_zone,mode);
				danger->set_state(compl_danger);
				danger->set_var(mpos);
			}
		}
		cnt++;
	}
	return danger;
}

BitypeVar<MatPosi*>* BaseChess::is_endangered(MatPosi* mpos_zone, Player* limitator){ // pe owner
	/* fonction qui vérifie si la piece est menacée par une piece adverse, si oui elle la retourne.
	 * (ou dans le cas d'une case vide si elle est menacée par n'importe qu'elle piece, si oui elle la retourne) */	
	 	
	int taille = this->get_plateau()->get_taille();
	std::pair<int,int> paire_zone = mpos_zone->to_pair();
	
	std::string mode;
	if (this->get_plateau()->is_empty_location(paire_zone)){mode = "depl";}
	else {mode = "capt";}
	
	return this->in_endangered_part(paire_zone, limitator, taille, mode);
}

BitypeVar<MatPosi*>* BaseChess::is_endangered(MatPosi* mpos_zone){
	/* fonction surchargée, permettant d'ommetre le Human indiquant le type de danger */
	
	Human* player = new Human();
	
	return this->is_endangered(mpos_zone,player);
}


bool BaseChess::check_more_than_one_danger(MatPosi* mpos_zone, Player* limitator){
	/* fonction qui vérifie si la piece est menacée par plus qu'une piece adverse
	 * (ou dans le cas d'une case vide si elle est menacée par n'importe qu'elle piece) */
	 	
	int taille = this->get_plateau()->get_taille();
	std::pair<int,int> paire_zone = mpos_zone->to_pair();
	
	std::string mode;
	if (this->get_plateau()->is_empty_location(paire_zone)){mode = "depl";}
	else {mode = "capt";}
	
	return this->more_dangers_part(paire_zone, limitator, taille, mode);
	
}

bool BaseChess::check_more_than_one_danger(MatPosi* mpos_zone){
	/* fonction surchargée, permettant d'ommetre le Human indiquant le type de danger */
		
	Human* player = new Human();
	
	return this->check_more_than_one_danger(mpos_zone, player);
}

std::vector<MatPosi*>* BaseChess::recup_zones_between_part(std::vector<std::pair<int,int>>* temp_vect, MatPosi* mposi_origi, MatPosi* mposi_end){
	/* fonction étant une sous-fonction de "recup_zones_between"
	 * fonction qui recupere les cases contenu entres 2 positions dans un plateau.
	 * utilisant l'Advtuple utile pour les reliès */
	
	std::vector<MatPosi*>* res = new std::vector<MatPosi*>();
		
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
	return res;
	
}

std::vector<MatPosi*>* BaseChess::recup_zones_between(std::pair<int,int> begin, AdvTuple adv_tup, std::pair<int,int> end){
	/* fonction qui recupere les cases contenu entres 2 positions dans un plateau. 
	 * utilisant l'Advtuple utile pour les reliès */
	
	std::vector<MatPosi*>* res = new std::vector<MatPosi*>();
	
	MatPosi* mposi_origi = new MatPosi(begin);
	MatPosi* mposi_end = new MatPosi(end);
	
	int limite = this->get_plateau()->get_taille();
	
	if (adv_tup.get_depl_type() == "translation"){
		std::vector<std::pair<int,int>>* temp_vect = adv_tup.get_res(limite,*mposi_origi);
		// get_res donnes toutes les positions sauf position actuelle!
				
		res = recup_zones_between_part(temp_vect, mposi_origi, mposi_end);
		
	}
	
	else if (adv_tup.get_depl_type() != "saut"){throw MyException(&mout, "type deplacement inconnu");}
	
	return res;	
	
}

std::vector<std::vector<MatPosi*>*>* BaseChess::get_zones_between(std::pair<int,int> begin, std::pair<int,int> end, std::string mode){
	/* fonction qui recupere les cases contenu entres 2 positions dans un plateau.
	 * en ayant cherché au préalable d'Advtuple utile pour les reliès*/
	
	std::vector<std::vector<MatPosi*>*>* result = new std::vector<std::vector<MatPosi*>*>();
	
	std::vector<MatPosi*>* res = new std::vector<MatPosi*>();
	
	BitypeVar<std::vector<AdvTuple*>*>* bit_adv = find_linking_advtuple(begin,end,mode); //
	
	if (bit_adv->get_state() == true){ //
		
		std::vector<AdvTuple*>* advtuples_vect = bit_adv->get_var();

		long long unsigned int i=0;
		while (i<advtuples_vect->size()){ // si un chemin sécurisé cela suffit
			
			AdvTuple* adv_tup = (*advtuples_vect)[i];
		
			res = this->recup_zones_between(begin, *adv_tup, end);
			result->push_back(res);
					
			i++;
		}
	}
	else{throw MyException(&mout,"mouvement impossible entre ces 2 positions!!!");}
	
	return result;		
}

bool BaseChess::check_between_is_empty_part(std::vector<std::pair<int,int>>* temp_vect, MatPosi* mposi_origi, MatPosi* mposi_end){
	/* fonction étant une sous-fonction de "check_between_is_empty"
	 * fonction qui vérifie que toutes les cases contenu entres 2 positions dans un plateau soient vides.
	 * utilisant l'Advtuple utile pour les reliès */
	 
	bool res = true;
	
	bool stop = false; // creer pour plus de comprehension avec res
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
		
		
		if (between == true){stop = not(this->get_plateau()->is_empty_location(paire_norm));}

		j++;
	}
	res = not(stop);
	
	return res;	
}

bool BaseChess::check_between_is_empty(std::pair<int,int> begin, AdvTuple adv_tup, std::pair<int,int> end){
	/* fonction qui vérifie que toutes les cases contenu entres 2 positions dans un plateau soient vides.
	 * utilisant l'Advtuple utile pour les reliès */
	
	bool res = true;
	
	MatPosi* mposi_origi = new MatPosi(begin);
	MatPosi* mposi_end = new MatPosi(end);
	
	int limite = this->get_plateau()->get_taille();
	
	if (adv_tup.get_depl_type() == "translation"){
		std::vector<std::pair<int,int>>* temp_vect = adv_tup.get_res(limite,*mposi_origi);
		// get_res donnes toutes les positions sauf position actuelle!
				
		res = check_between_is_empty_part(temp_vect, mposi_origi, mposi_end);
		
	}
	
	else if (adv_tup.get_depl_type() != "saut"){throw MyException(&mout, "type deplacement inconnu");}
	
	return res;	
	
}

bool BaseChess::check_non_active_player_king(Chesspiece* pe){
	/* fonction qui vérifie l'état du roi adverse sur le plateau
	 * (en echec, en echec et mat, coincé, ...) */
	
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
				
		escape = this->can_escape_position(pe ,"depl");
		
		// verifier si le roi peu s'écchapper --> tester toutes les methodes de déplacments
		//(sauf roc car si echec --> roc pas permis sinon inutile a verifier car roc ne peut pas empecher echec ou echec et mat (voir regles))
		
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
						
						BitypeVar<Chesspiece*> danger_bity = this->get_plateau()->get_piece(dangerception_mpos->to_pair());
						
						//impossible que ce soit le roi (déjà geré dans can_escape) !!!
						
						// menace peut être prise --> pas echec et mat !!!!						
							
					}
					else{mode_echec_et_mat = true;}
					
				}
				else{
					//allie peut-il s'interposer?
					
					
					std::vector<std::vector<MatPosi*>*>* zones_between_vect_vect = this->get_zones_between(mpos_menace->to_pair(), mpos->to_pair(), "capt");
					
					// plusieurs vecteur = plusieur chemin que la menace peut emprunté --> il faut tous pouvoir les bloquer
					// --> chercher les intersections !!!
					
					
					std::vector<MatPosi*>* intersect_vect = get_path_intesection(zones_between_vect_vect);

					bool blocked = false;
					long long unsigned int i=0;
					while(i<intersect_vect->size() and not(blocked)){
						
						MatPosi* mpos_zone = (*intersect_vect)[i];
						
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
		
		if (not(mode_echec_et_mat)){ss<<this->get_dico()->search(this->get_active_player()->get_langue(),"mode_echec")<<std::endl;}
		else{ss<<this->get_dico()->search(this->get_active_player()->get_langue(),"mode_echec_et_mat")<<std::endl;}
	}
	
	this->get_active_player()->send_msg(ss.str());
	
	return mode_echec_et_mat;
	
}

bool BaseChess::verify_kings(){
	/* fonction vérifiant la présence des roi des deux joueurs sur le plateau */
	
	std::vector<Chesspiece*>* vect = this->get_kings();
	Chesspiece* pe;
	this->get_active_player()->send_msg("DEB VERIFY KINGS:",true);
	
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
		ss<<this->get_dico()->search(this->get_active_player()->get_langue(),"vict")<<" "<<get_non_active_player()<<" ! (previson avant le deplacement reel)"<<std::endl;
		this->get_active_player()->send_msg(ss.str());
	}
	
	this->get_active_player()->send_msg("FIN VERIFY KINGS:",true);
	
	return mode_echec_et_mat;
	
}

std::vector<Chesspiece*>* BaseChess::get_kings(){
	/* fonction permettant de recuperer les roi des deux joueurs sur le plateau */
	
	std::vector<Chesspiece*>* res = new std::vector<Chesspiece*>();
	
	int cnt = this->get_plateau()->begin_position();
	int end_cnt = this->get_plateau()->end_position();
	
	for(;cnt <= end_cnt;cnt++){ // 1e case for vide --> ok, car pas besoin d'initialiser cnt car déjà fait avant (noter simplement cnt sert a rien et génère un warning)
		
		BitypeVar<Chesspiece*> dst = this->get_plateau()->get_piece(cnt);
		if (verifier_type_pe<Roi>(dst) == true){
			res->push_back(dst.get_var());
		}
	}
	return res;
}

bool BaseChess::check_danger_mouvement_and_path(std::pair<int,int> paire_origi, AdvTuple adv_tup, std::pair<int,int> paire, std::string mode){
	/* fonction verifiant qu'une piece peut effectuer le mouvement car ses mouvement possible le permettent
	 * ainsi que les cases qu'elle doit parcourir lors du mouvement soint vides */
	 
	bool keep = false;
	bool valid;
		
	valid = this->get_plateau()->isvalid_move(paire_origi, paire, mode);
	
	//mout << "valid"<<valid<<std::endl;
	
	if(valid == true){		
		keep = this->check_between_is_empty(paire_origi, adv_tup, paire);
		//mout << "bewteen"<<keep<<std::endl;
	}
	//else{keep = false;}
	
	return keep;
	
}
