
#include "../../Bot/Bot.cpp"

MyOstream mout("logfile.txt");

int main(){
	
	Human* player = new Human("player1");
	
	player->send_msg(" ... message du client ...");
	
	mout<<std::endl<<std::endl;
	
	return 0;
}
