//JUSTE POUR TEST

#include "../includes/abstractInterface.hpp"

class Graphyque: public AbstractInterface{
    public:
        Graphyque(AbstractClient*){}
        ~Graphyque(){}
        void connectionError() override{}
		void gameStart(std::string opponent) override{}
		void recvMessage(std::string name, std::string mov) override{}
        void pingForUpdate() override{}
        void win() override{}
        void lose() override{}
};