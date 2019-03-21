#ifndef ABSTRACTCLIENT_HPP
#define ABSTRACTCLIENT_HPP

#include <string>

class AbstractClient{
	public:
		//call by interface
		virtual bool letsRegister(std::string username,std::string password, std::string email) = 0;
		virtual bool login(std::string username,std::string password) = 0;
		virtual void waitForMatch(int gameMod) = 0;

		virtual void sendMessage(std::string name,std::string msg) = 0;
		virtual void addFriend(std::string name) = 0;
		virtual void removeFriend(std::string name) = 0;
		virtual void getFriendList() = 0;
		virtual void getOnlineFriendList() = 0;
		virtual void getUserInfo() = 0;

		virtual void click(std::string square) = 0;
		virtual void exit() = 0;
		//call by server
		virtual void startingGame(bool playerTurn, std::string opponentName) = 0;
		virtual void opponentMov(std::string mov) = 0;
		virtual void recvMessage(std::string name,std::string msg) = 0;
		virtual void connectionError() = 0;
};

#endif