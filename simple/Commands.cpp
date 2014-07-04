#include <Commands.h>

//-------------------Command------------------------------------------------
Command::Command(string suc_string,string fail_string) 
	:success_string(suc_string),
		failure_string(fail_string) {
}

Command::~Command() {

}
	

//-------------------Post Command------------------------------------------------
PostCommand::PostCommand(string side, string cName,int amt,double prc)
	:Command("Success in Post Command","Failure in Post Command"){
	buyOrSell = side;
	commodityName = cName;
	commodityAmount = amt;
	commodityPrice = prc;
}

string PostCommand::execute(MarketPtr market,string dealer_id) {
	OrderInfoPtr order;
	if(buyOrSell == "BUY") {
		order  = market->buy_commodity(*this,dealer_id);
	}else if(buyOrSell == "SELL") {
		order = market->sale_commodity(*this,dealer_id);
	}else {
		assert(0 && "This is impossible case for the Post command");
	}
	success_string =order->to_string()+" HAS BEEN POSTED";
	return success_string;
}

string PostCommand::get_buy_or_sell() {
	return buyOrSell;
}
                                                              
string PostCommand::get_commodity_name() {
	return commodityName;
}

int PostCommand::get_commodity_amount() {
	return commodityAmount;
}


double PostCommand::get_commodity_price() {
	return commodityPrice;
}

//-------------------Revoke Command------------------------------------------------
RevokeCommand::RevokeCommand(int id):
	Command("Success in Revoke","Failure in Revoke"){
	orderId = id;
}

string RevokeCommand::execute(MarketPtr market,string dealer_id) {
	cout<<"Executing the Revoke command"<<endl;
	OrderInfoPtr order = market->cancel_order(orderId,dealer_id);
	if(order) {
		success_string= boost::lexical_cast<string>(orderId)+" HAS BEEN REVOKED";
		return success_string;
	}
 	return "";
}

//-------------------Check Command------------------------------------------------
CheckCommand::CheckCommand(int id):
	Command("Success from Check command","Failure from Check command") , 
	_order_id(id) {

}


string CheckCommand::execute(MarketPtr market, string dealer_id) {

}

//-------------------List Command------------------------------------------------
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

string ListCommand::execute(MarketPtr market,string dealer_id) {
	cout<<"Executing the List Command"<<endl;
	return "";
}

//-------------------Aggress Command------------------------------------------------
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


string AggressCommand::execute(MarketPtr market,string dealer_id) {
	cout<<"Executing the Aggress Command with the arg size = "<<apairList.size()<< endl;
	return "";
}
