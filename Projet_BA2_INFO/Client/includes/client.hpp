#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "../srcs/request.cpp"
#include "../srcs/terminal.cpp"
#include "../../Gui/incl/FenPrincipale.hpp"
#include "../game/GameTypes/SuperGame/SuperGame.cpp"

<<<<<<< HEAD
#define PORT 5555


class Client: AbstractClient {
    public:
        Client(const char* ip);
        ~Client();
        void connectionError() override;
		void startingGame(bool playerTurn) override;
		void opponentMov(std::string mov) override;
		void printMessage(std::string) override;
		
		bool get_inverted() const override;
		void set_inverted(bool) override;
		
		bool get_ennemy_inverted() const override;
		void set_ennemy_inverted(bool) override;
		
		std::string get_ennemy_name() const override;
		void set_ennemy_name(std::string) override;
		
	private:
		Request* _request;
		TempsReel* _game; // TempsReel est une classe commune entre TempsReel, TourParTour et Pendule -quentin
		std::string _username;
		bool _gameStart;
		bool _myTurn;
		int _gameMod;
		bool _isInverted;
		bool _isEnnemyInverted;
		std::string _ennemyName;
=======
class Client: public AbstractPlayer, public AbstractClient{
	private:
		Request* _server;
		SuperGame* _game;
		AbstractInterface* _interface;
>>>>>>> Partie_Serveur

		int _gameMod;
		std::string _name;
		void lose();
		void win();
	public:
		//Client(const char* ip, bool interface);
		Client(const char* ip, bool interface, int argc, char** argv);

		~Client();
		
		//call by interface
		void setInterface(AbstractInterface* interface) override;
		bool letsRegister(std::string username,std::string password1, std::string password2, std::string email) override;
		bool login(std::string username,std::string password) override;
		void waitForMatch(int gameMod) override;

		void sendMessage(std::string name,std::string msg) override;
		void addFriend(std::string name) override;
		void removeFriend(std::string name) override;
		void acceptFriend(std::string name, bool accept) override;
		void getFriendList() override;
		void getFriendRequests() override;
		void getUserInfo(std::string) override;
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
		void movPossibleUpdate(std::vector<std::string> listMov) override;

		void recvFriendRequestsList(std::vector<std::string> vec) override;
		void recvFriendList(std::vector<std::pair<std::string, bool> > frendList) override;
		void recvInfo(std::string username, int nbrgames, int win, int elo) override;

		int showGui(int argc, char** argv);
};

#endif
