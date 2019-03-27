#ifndef ABSTRACTCLIENT_HPP
#define ABSTRACTCLIENT_HPP

#include <string>

class AbstractInterface;

class AbstractClient{
	public:
		virtual ~AbstractClient() = default;
		//call by interface
		virtual void setInterface(AbstractInterface* interface) = 0;
		virtual bool letsRegister(std::string username,std::string password1, std::string password2, std::string email) = 0;
		virtual bool login(std::string username,std::string password) = 0;
		virtual void waitForMatch(int gameMod) = 0;

		virtual void sendMessage(std::string name,std::string msg) = 0;
		virtual void addFriend(std::string name) = 0;
		virtual void removeFriend(std::string name) = 0;
		virtual void acceptFriend(std::string name, bool accept) = 0;
		virtual void getFriendList() = 0;
		virtual void getFriendRequests() = 0;
		virtual void getOnlineFriendList() = 0;
		virtual void getUserInfo(std::string username) = 0;
		virtual void getMyInfo() = 0;

		virtual void recvFriendRequestsList(std::vector<std::string>) = 0;

		virtual void click(std::string square) = 0;
		virtual void exit() = 0;
		//call by server
		virtual void startingGame(bool playerTurn, std::string opponentName) = 0;
		virtual void opponentMov(std::string mov) = 0;
		virtual void recvMessage(std::string name,std::string msg) = 0;
		virtual void connectionError() = 0;
};

#endif