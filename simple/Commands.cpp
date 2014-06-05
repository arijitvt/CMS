#include <Commands.h>


Command::~Command() {

}


PostCommand::PostCommand(string side, string cName,int amt,double prc) {
	buyOrSell = side;
	commodityName = cName;
	commodityAmount = amt;
	commodityPrice = prc;
}

int PostCommand::execute() {
	cout<<"Executing post command"<<endl;
	return 0;
}

RevokeCommand::RevokeCommand() {

}

int RevokeCommand::execute() {
 	return 0;
}
