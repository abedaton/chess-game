#include "abstractInterface.hpp"
#include "../../Gui/incl/FenPrincipale.hpp"



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

        int makeGui(int argc, char** argv);
    
    public:
        //FenPrincipale _gui;
};