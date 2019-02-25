
#include "common.hpp"

bool is_prime(int n ){
	/* fonction calculant si un nombre n est premier */
	
	bool res;
	if (n > 9){
		res = true;
		int a = 2,b;
		while ((a<9) and (res == true)){
			b = n%a;
			if (b == 0){res = false;}
			a+=1;
		}
	}
	else{res = ((n==2) or (n==3) or (n==5) or (n==7));}
	
	return res;
}

bool isvalid_coord(std::string s){
	/* fonction calculant si un string s est est une coordonée matricielle valide */
	
	bool res = false;
	
	std::string alph = "ABCDEFGHIJKLMNPQRSTUVWXYZ";
	
	if (s.size() >= 2) {
	
		std::string letter = std::string(1, s[0]); //zero
		std::size_t colonne = alph.find(letter);
		if (colonne != std::string::npos){
			std::string reste = s.substr(1);
			try {
				int ligne = std::stoi(reste) - 1;
				(void)ligne;
				res = true;
			}
			catch (const std::invalid_argument& ia) {
				(void)ia;
				res = false;
			}
		}
	}
	
	return res;
}
	
std::vector<std::string>* os_list_dir(const std::string& name){
	/* fonction équivalent a os.listdir() en python:
	 * --> parcours les fichiers et dossiers d'un dossier donné et retorune un vecteur de leurs noms
	 * les noms "."(dossier actuel) et ".."(dossier père) sont exclus */
	
	std::vector<std::string>* vect = new std::vector<std::string>();
	
    DIR* dirp = opendir(name.c_str());
    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL) {
		std::string to_ins;
		to_ins = dp->d_name;
		if (to_ins != "." and to_ins != ".."){vect->push_back(dp->d_name);}
    }
    closedir(dirp);
    
    return vect;
}

std::string get_first_file_of_dir(const std::string& name,std::string extention){
	/* fonction recherchant dans un dossier le premier fichier contenant l'extension donnée
	 * en réalité l'extension ne doit pas être une extension mais peut-être juste une serie de caractères a rechercher
	 * par conséquent les noms de dossiers peuvent aussi êtres trouvés dans ces cas présis */
	 
	std::vector<std::string>* vect;
	vect = os_list_dir(name);
	
	std::string res = "";
	long long unsigned int i=0;
	while (i<vect->size() and res == ""){
		std::string elem = (*vect)[i];
		
		if (elem.find(extention) != std::string::npos){res = elem;}
		i++;
	}
	
	return res;
}
