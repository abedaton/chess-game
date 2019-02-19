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

#include "../../ClassicChess/ClassicChess.cpp"

class User: public Human{
	public:
		User(int client_sock);
		virtual ~User() = default;		
		User() noexcept = default; //*< Constructor
        User(const User&);
        User& operator= (const User&) noexcept = default;
	
	private:
		int _clientSock;
		
		static void* run(void* tmp);
		void startGame();
		std::string in();
		void out(std::string str);
		void exit();

		void sendInt(int num);
        int recvInt();
		void sendStr(std::string);
        std::string recvStr();
        
        void launch_classic_game(User*, User*, std::string);
		
	public: // temporaire plustard private (sauf in et out biensur!)

        virtual std::string next_input() override;
        virtual void send_msg(std::string,bool) override;
        using Human::send_msg;
    
    private:
		virtual std::string get_type_prefix() const override;
		
};

#endif
