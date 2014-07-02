#include <Commands.h>


Command::Command(string suc_string,string fail_string) :success_string(suc_string),
	failure_string(fail_string) {
}

Command::~Command() {

}


PostCommand::PostCommand(string side, string cName,int amt,double prc)
	:Command("Success in Post Command","Failure in Post Command"){
	buyOrSell = side;
	commodityName = cName;
	commodityAmount = amt;
	commodityPrice = prc;
}

string PostCommand::execute(MarketPtr martket) {
	return success_string;
}

RevokeCommand::RevokeCommand(int id):
	Command("Success in Revoke","Failure in Revoke"){
	orderId = id;
}

string RevokeCommand::execute(MarketPtr market) {
	cout<<"Executing the Revoke command"<<endl;
 	return "";
}

ListCommand::ListCommand()
	:Command("",""){
}

ListCommand::ListCommand(string cName):Command("","") {
	commodityName = cName;
}

ListCommand::ListCommand(string cName,string dId):Command("","") {
	commodityName = cName;
	dealerId = dId;
}

string ListCommand::execute(MarketPtr market) {
	cout<<"Executing the List Command"<<endl;
	return "";
}

AggressCommand::AggressCommand(int numOfArgs,...) 
	:Command("Success in Aggress","Failure in Aggress"){
	va_list vararg;
	va_start(vararg,numOfArgs);
	for (int  i = 0 ; i  < numOfArgs; ++i) {
		int orderId = va_arg(vararg,int);
		int amount = va_arg(vararg,int);
		APair ap = { orderId,amount};
		apairList.push_back(ap);
	}
}

AggressCommand::AggressCommand(vector<APair> apArg) 
	:Command("Success in Aggress","Failure in Aggress"){
	apairList = apArg;
}


string AggressCommand::execute(MarketPtr market) {
	cout<<"Executing the Aggress Command with the arg size = "<<apairList.size()<< endl;
	return "";
}
