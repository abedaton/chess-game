
#include <iostream>
#include <string>

#include "StandardMessage/StandardMessage.cpp"

class LocalMessage: public StandardMessage{

	public:
        LocalMessage() noexcept = default; //*< Constructor
        virtual ~LocalMessage() noexcept = default; //Destructor
        LocalMessage(const LocalMessage&) noexcept = default;
        LocalMessage& operator= (const LocalMessage&) noexcept = default;
            
        using StandardMessage::send_msg;
        virtual void send_msg(Player*,std::string,bool) override;
        virtual std::string recieve_msg(Player*) override;
};
