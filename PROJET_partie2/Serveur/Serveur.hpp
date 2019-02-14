#pragma GCC diagnostic ignored "-Wzero-as-null-pointer-constant"
#ifndef SERVEUR_HPP
#define SERVEUR_HPP

#include "user.hpp"

#include <iostream>
#include <string>
#include <vector>

#include "../ClassicChess/ClassicChess.cpp"

#include "includes/database.hpp"
#include "includes/matchMaking.hpp"

class Serveur {
    public:
        Serveur();
        Serveur(std::string ip, short unsigned int port);
        //Serveur(const Serveur&);
        
        
        int get_player_socket(std::string);
        
        void kickClient(int);
        
        std::string recvStr(int);
        std::string recvStr(std::string);
        void sendStr(int, std::string);
        void sendStr(std::string, std::string);
        void sendInt(int, int);
        
        // mettre ClassicChess,HumanServ, ServerMessage en friend ?
        // --> permetterait normalment de mettre tous les send et recv (et get_player_socket) en private
        
        void execute();
       
	//private:
		void launch_classic_game(std::string);
        
        
        
    private:
        void sShutdown();
        void mainLoop();
        void setup();
        void* handleCommand();
 

        std::string _ip;
        short unsigned int _port;
        struct sockaddr_in _address;
        int _serv_sock;
        unsigned int _addrlen;

        std::vector<int*> _clients;

        Database* db;
        sqlite3_stmt* stmt;
        std::string sql;
        char* zErrMsg = 0; // voir site sqlite

        MatchMaking* match = new MatchMaking();
        

};

#endif


class HumanServ: public Human{
	
	private:
		Serveur* serveur;
	
	public:
        HumanServ(std::string,Serveur*); //*< Constructor
        HumanServ() noexcept = default; //*< Constructor
        virtual ~HumanServ() noexcept = default; //Destructor
        HumanServ(const HumanServ&);
        HumanServ& operator= (const HumanServ&) noexcept = default;
        
        Serveur* get_serveur();
        
        std::string next_input() override;
        
	private:
		virtual std::string get_type_prefix() const override;
};

class ServerMessage: public LocalMessage{
	private:
		Serveur* serveur;
	
	public:
        ServerMessage(Serveur*); //*< Constructor
        virtual ~ServerMessage() noexcept = default; //Destructor
        ServerMessage(const ServerMessage&) noexcept = default;
        ServerMessage& operator= (const ServerMessage&) noexcept = default;
        
        Serveur* get_serveur();
            
        using LocalMessage::send_msg;
        virtual void send_msg(Player*,std::string,bool) override;
};


#ifndef USER_HPP
#define USER_HPP

class User{
	public:
		User(int* client_sock, Database* db,MatchMaking* match,Serveur*);
		~User() = default;
		void startGame(AbstractGame* game);
	private:
		int* _clientSock;
		Database* _db;
		MatchMaking* _match;
		AbstractGame* _game;
		Serveur* serveur;
		
		std::string name;
		bool isLog;
		bool inGame;

		void handleClient();
		void exit();
		void checkLogin();
		void letsRegister();
		void chat();
		void waitForMatch();
		void getMov(); //tmp
		void mov(); //tmp

		void sendInt(int num);
        int recvInt();
		void sendStr(std::string);
        std::string recvStr();

		static void* run(void* tmp);
		
};


#endif
