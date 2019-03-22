#include "abstractInterface.hpp"
#include "../../Gui/incl/FenPrincipale.hpp"
#include "client.hpp"



class Client;
class FenPrincipale;

class Graphic: public AbstractInterface{
    public:
        Graphic(AbstractClient* client, int argc, char** argv);
        ~Graphic();
        void connectionError() override;
		void gameStart(std::string opponent) override;
		void recvMessage(std::string name, std::string mov) override;
        void pingForUpdate() override;
        void win() override;
        void lose() override;

        bool loginGUI(std::string username,std::string password);

        int makeGui(int argc, char** argv);
    
    public:
        FenPrincipale* _gui;
        AbstractClient* _client;
};