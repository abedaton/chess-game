
#include <iostream>
#include <string>

#include "../../../Bot/Bot.cpp"

class Message{	
	public:
        Message() noexcept = default; //*< Constructor
        virtual ~Message() noexcept = default; //Destructor
        Message(const Message&) noexcept = default;
        Message& operator= (const Message&) noexcept = default;
        
        virtual void send_msg(Player*,std::string,bool) = 0;
        virtual void send_msg(Player*,std::string) = 0;
        virtual std::string recieve_msg(Player*) = 0;
};
