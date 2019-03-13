#pragma once
#ifndef USER_HPP
#define USER_HPP

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <thread>
#include <vector>
#include <string>
#include <pthread.h>
#include <iostream>
#include <mutex>

#include "../srcs/database.cpp"
#include "../srcs/matchMaking.cpp"



class User: public AbstractUser{
	public:
		User(int client_sock, Database* db, MatchMaking* match);
		virtual ~User() = default;		
        User(const User&) = delete;
        User& operator= (const User&) noexcept = delete;

		void startGame(TempsReel*, AbstractUser*, bool) override;
		void opponentMov(std::string mov)override;
		void surrend() override;
		void sendMsg(std::string msg) override;
		void exit();

		void sendfriendRequestNotification(User *userAdding); 
		void removeFromFriends(User *userToRemove);
		void addFriendToList(User *new_friend);
		void sendMessage(std::string sender, std::string message);
		std::string getName(); //a changer apres avoir compilé
		std::string get_name() const override;
	
	private:
		int _clientSock;
		Database* _db;
		MatchMaking* _match;
		TempsReel* _game;
		AbstractUser* _opponent;
		bool _myTurn;

		std::mutex _mutex;
		std::string name;
		
		void handleClient();
		void checkLogin();
		void letsRegister();
		void chat();
		void waitForMatch();
		void mov();
		
		inline void waitForProcess();
		inline void endProcess();
		void sendInt(int num);
        int recvInt();
		int recvInt(int flag);
		void sendStr(std::string);
        std::string recvStr();

		static void* run(void* tmp);
		

		void updateInfo(); // update le nom et socket dans la database
		void updateInfoDisc(); // quand le client se deconnecte
		void updateInfoMatch(); 
		
		User *findUserByName(std::string name);
        void listOnlineFriends();
        void addFriend();
        void removeFriend();
		void recvFriendRequestAnswer();
		std::vector<User*> friends;
};



enum Protocol : int {
    PASS = 0, REGISTER, LOGIN, CHAT, WAITFORMATCH, MOV, SURREND, 
    LISTONLINEFRIENDS, ADDFRIEND, REMOVEFRIEND, NEWFRIENDREQUEST, 
    FRIENDREQUESTANSWER, RECVMESSAGE, SENDMESSAGE
};

extern std::vector<User*> onlineUsers;

#endif
