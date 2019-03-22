#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "../srcs/request.cpp"
#include "../srcs/terminal.cpp"
#include "../../Gui/incl/FenPrincipale.hpp"
#include "../game/Gestion/Pendule/Pendule.cpp"
#include "../game/Gestion/TempsReel/TempsReel.cpp"
#include "../game/Gestion/TourParTour/TourParTour.cpp"

#include "abstractPlayer.hpp" //tmp

class Client: public AbstractPlayer, public AbstractClient{
	private:
		AbstractInterface* _interface;
		Request* _server;
		TempsReel* _game;

		int _gameMod;
	public:
		//Client(const char* ip, bool interface);
		Client(const char* ip, bool interface, int argc, char** argv);

		~Client();
		
		//call by interface
		bool letsRegister(std::string username,std::string password, std::string email) override;
		bool login(std::string username,std::string password) override;
		void waitForMatch(int gameMod) override;

		void sendMessage(std::string name,std::string msg) override;
		void addFriend(std::string name) override;
		void removeFriend(std::string name) override;
		void acceptFriend(std::string name, bool accept) override;
		void getFriendList() override;
		void getFriendRequests() override;
		void getOnlineFriendList() override;
		void getUserInfo() override;

		void click(std::string square) override;
		void exit() override;
		//call by server
		void startingGame(bool playerTurn, std::string opponentName) override;
		void opponentMov(std::string mov) override;
		void recvMessage(std::string name,std::string msg) override;
		void connectionError() override;
		//call by game
		void mov(std::string mov) override;
		void win() override;
		void lose() override;

		int showGui(int argc, char** argv);
};

#endif
