
#include <iostream>
#include <string>

#include "Message/Message.hpp"

class StandardMessage: public Message{	
	public:
        StandardMessage() noexcept = default; //*< Constructor
        virtual ~StandardMessage() noexcept = default; //Destructor
        StandardMessage(const StandardMessage&) noexcept = default;
        StandardMessage& operator= (const StandardMessage&) noexcept = default;
        
        virtual void send_msg(Player*,std::string,bool) override;
        virtual void send_msg(Player*,std::string) override;
        virtual std::string recieve_msg(Player*) override;
};
