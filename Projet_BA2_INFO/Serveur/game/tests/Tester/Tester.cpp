
#include "Tester.hpp"

extern MyOstream mout;

Tester::Tester(Chesspiece* piece,std::string nom,Plateau* plat,std::vector<Trinome<std::string,std::string,BitypeVar<bool>>> act,std::string ini) : pe(piece), name(nom), plateau(plat), actions(act), posi_ini(ini){} //*< Constructor

std::ostream& operator <<(std::ostream &s,Tester &c){
	/* affchage d'un Tester */
    s<<"Tester("<<c.get_name()<<")";
    return s;
}

std::string Tester::get_name(){
	return this->name;
}

Chesspiece* Tester::get_pe(){
	return this->pe;
}

Plateau* Tester::get_plateau(){
	return this->plateau;
}

std::vector<Trinome<std::string,std::string,BitypeVar<bool>>> Tester::get_actions(){
	return this->actions;
}

std::string Tester::get_posi_ini(){
	return this->posi_ini;
}

Paire<int,int> Tester::execute(){
	
	std::string langue = "francais";
	
	Human* test_player = new Human("Test_player",langue);
	
	this->get_pe()->set_owner(test_player);
	
	Dico* dict = make_dico("../../csv");
	
	Affichage* aff = new Affichage(this->get_plateau(), dict,"Symbole_","",langue,test_player, test_player,"*" ,"");
	
	int tot_cnt = 0;
	int passed_cnt = 0;
	
	mout<<std::endl;
	
	mout<<this->get_name()<<std::endl;
	
	Chesspiece* piece = this->get_pe();
	mout<<*(piece)<<std::endl;
	mout<<std::endl;
	
	Plateau* plat;
	plat = this->get_plateau();
	
	//mout<<*(plat)<<std::endl;
	mout<<aff->get_affichage()<<std::endl;
	mout<<std::endl;
	
	MatPosi* mpos_initial = new MatPosi(this->get_posi_ini());
	Paire<int,int> transf_ini = mpos_initial->to_pair();
	
	plat->set_piece(transf_ini,this->get_pe()); // !
	
	//mout<<*(plat)<<std::endl;
	mout<<aff->get_affichage()<<std::endl;
	mout<<std::endl;
	
	Paire<int,int> transf_action_in;
	MatPosi* mpos_in;
	Paire<int,int> transf_action_out;
	MatPosi* mpos_out;
	
	for(long long unsigned int i=0;i<this->get_actions().size();i++){
		
		Trinome<std::string,std::string,BitypeVar<bool>> action = (this->get_actions())[i];
		
		bool rep;
		
		mpos_in = new MatPosi(action.get_first());
		transf_action_in = mpos_in->to_pair();
		
		mpos_out = new MatPosi(action.get_second());
		transf_action_out = mpos_out->to_pair();
		
		rep = plat->move(transf_action_in,transf_action_out); // !
		
		if (rep == true) {mout<<"MOUVEMENT : la piece se deplace!"<<std::endl;}
		else {mout<<"IMMOBILE : pas de mouvement!"<<std::endl;}
		
		if (action.get_third().get_state() != false){
			mout<<"comportement attendu? ";
			tot_cnt += 1;
			
			if(action.get_third().get_var() == rep){
				mout<<"OK!"<<std::endl;
				passed_cnt += 1;
				}
			else {mout<<"PAS OK!"<<std::endl;}
			
		}
	
	mout<<std::endl;
	//mout<<*(plat)<<std::endl;
	mout<<aff->get_affichage()<<std::endl;
	mout<<std::endl;
		
	}
	
	mout<<std::endl<<"********************************************************************************************************************"<<std::endl;
	mout<<std::endl;
	mout<<"RECAP: "<<passed_cnt<<" tests reussi sur "<<tot_cnt<<std::endl;
	mout<<std::endl<<"********************************************************************************************************************"<<std::endl;
	mout<<std::endl;
	
	Paire<int,int>* paire = new Paire<int,int>(passed_cnt,tot_cnt);
	return *paire;
	
}
