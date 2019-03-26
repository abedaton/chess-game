#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "../srcs/request.cpp"
#include "../srcs/terminal.cpp"
#include "../../Gui/incl/FenPrincipale.hpp"
#include "../game/GameTypes/SuperGame/SuperGame.cpp"

class Client: public AbstractPlayer, public AbstractClient{
	private:
		AbstractInterface* _interface;
		Request* _server;
		SuperGame* _game;

		int _gameMod;
		void lose();
		void win();
	public:
		//Client(const char* ip, bool interface);
		Client(const char* ip, bool interface, int argc, char** argv);

		~Client();
		
		//call by interface
		bool letsRegister(std::string username,std::string password1, std::string password2, std::string email) override;
		bool login(std::string username,std::string password) override;
		void waitForMatch(int gameMod) override;

		void sendMessage(std::string name,std::string msg) override;
		void addFriend(std::string name) override;
		void removeFriend(std::string name) override;
		void acceptFriend(std::string name, bool accept) override;
		void getFriendList() override;
		void getFriendRequests() override;
		void getOnlineFriendList() override;
		void getUserInfo(std::string) override;
		void getMyInfo() override;

		void click(std::string square) override;
		void exit() override;
		//call by server
		void startingGame(bool playerTurn, std::string opponentName) override;
		void opponentMov(std::string mov) override;
		void recvMessage(std::string name,std::string msg) override;
		void connectionError() override;
		//call by game
		void mov(std::string mov) override;
		void movPossibleUpdate(std::vector<std::string> listMov) override;

		int showGui(int argc, char** argv);
};

#endif
