#include <iostream>

//enum GAME_TYPE

//retourne dans l'ordre de game_types le jeu choisi
unsigned int ChooseGameType()
{
	unsigned int res = 0;
	const char *game_types[] =  {"Jeu d'echec classique", "Trappist chess","Dark chess", "Anti chess" };

	std::cout << "Veuillez choisir un mode de jeu: " << std::endl;
	
	for(int i = 0; i < 4 ;i++)
		std::cout << i+1 << ") " << game_types[i] << ":" << std::endl;

	std::cin >> res;
	while(res == 0 || res > 4)
	{	
		std::cout << "Choix invalide veuillez réessayer:" << std::endl;
		std::cin >> res;
	}

	std::cout << "Vous avez choisi: " << game_types[res-1] << std::endl;
	return res;
}

//retourne dans l'ordre de multiplayer_modes le mode de recherche choisi
unsigned int ChooseMultiplayerResearchMode()
{
	unsigned int res = 0;
	const char *multiplayer_modes[] = {"Matchmaking", "Partie privée" };

	std::cout << "Veuillez choisir le moyen de recherche d'adversaire: " << std::endl;
	std::cout << "1) Matchmaking: " << std::endl;
	std::cout << "2) Partie privée: " << std::endl;

	std::cin >> res;
	while(res == 0 || res > 2)
	{	
		std::cout << "Choix invalide veuillez réessayer:" << std::endl;
		std::cin >> res;
	}

	std::cout << "Vous avez choisi: " << multiplayer_modes[res-1] << std::endl;
	return res;
}


int main()
{
	unsigned int game_type = ChooseGameType();
	unsigned int multiplayer_mode = ChooseMultiplayerResearchMode();
	return 0;
}