
#include "../../LocalMessage/LocalMessage.cpp"

MyOstream mout("logfile.txt");

int main(){
	
	Human* player = new Human("player1");
	
	LocalMessage* local_msg = new LocalMessage();
	
	local_msg->send_msg(player," ... message du client ...");
	
	mout<<std::endl<<std::endl;
	
	//ServerMessage* serv_msg = new ServerMessage();
	
	//serv_msg->send_msg(player," ... message du client ...");
	
	return 0;
}
