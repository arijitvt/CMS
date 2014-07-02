#include <Commands.h>


Command::~Command() {

}


PostCommand::PostCommand(string side, string cName,int amt,double prc) {
	buyOrSell = side;
	commodityName = cName;
	commodityAmount = amt;
	commodityPrice = prc;
}

int PostCommand::execute(MarketPtr martket) {
	cout<<"Executing post command"<<endl;
	return 0;
}

RevokeCommand::RevokeCommand(int id) {
	orderId = id;
}

int RevokeCommand::execute(MarketPtr market) {
	cout<<"Executing the Revoke command"<<endl;
 	return 0;
}

ListCommand::ListCommand() {}
ListCommand::ListCommand(string cName) {
	commodityName = cName;
}

ListCommand::ListCommand(string cName,string dId) {
	commodityName = cName;
	dealerId = dId;
}

int ListCommand::execute(MarketPtr market) {
	cout<<"Executing the List Command"<<endl;
	return 0;
}

AggressCommand::AggressCommand(int numOfArgs,...) {
	va_list vararg;
	va_start(vararg,numOfArgs);
	for (int  i = 0 ; i  < numOfArgs; ++i) {
		int orderId = va_arg(vararg,int);
		int amount = va_arg(vararg,int);
		APair ap = { orderId,amount};
		apairList.push_back(ap);
	}
}

AggressCommand::AggressCommand(vector<APair> apArg) {
	apairList = apArg;
}


int AggressCommand::execute(MarketPtr market) {
	cout<<"Executing the Aggress Command with the arg size = "<<apairList.size()<< endl;
	return 0;
}
