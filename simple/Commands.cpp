#include <Commands.h>
#include <Utility.h>

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
	//	assert(0 && "This is impossible case for the Post command");
		throw CMSException("This is impossible case for the POST command");
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
	Command("Success in Revoke",ErrorMsgs::UN_ORDER){
	orderId = id;
}

string RevokeCommand::execute(MarketPtr market,string dealer_id) {
	cout<<"Executing the Revoke command"<<endl;
	try {
		OrderInfoPtr order = market->cancel_order(orderId,dealer_id);
		if(order) {
			success_string= boost::lexical_cast<string>(orderId)+" HAS BEEN REVOKED";
			return success_string;
		}else {
			return failure_string;
		}    
	}catch(CMSException &ex) {
		return ex.what();
	}

 	return "";
}

//-------------------Check Command------------------------------------------------
CheckCommand::CheckCommand(int id):
	Command("Success from Check command","Failure from Check command") , 
	_order_id(id) {

}


string CheckCommand::execute(MarketPtr market, string dealer_id) {
	cout<<"Executing Check command by "<<dealer_id<<endl;
	OrderInfoPtr order = market->check_order(_order_id,dealer_id);
	if(order && order->get_commodity_list_size() == 0 ) {
		success_string = boost::lexical_cast<string>(order->get_order_id())+
					" HAS BEEN FILLED";
	}else if (order) {
		success_string = order->to_string();
	} else {
		return ErrorMsgs::UN_AUTH;
	}
	return success_string;
}

//-------------------List Command------------------------------------------------
ListCommand::ListCommand()
	:Command("",""){
}

ListCommand::ListCommand(string cName):Command("","") {
	commodityName = cName;
}

ListCommand::ListCommand(string cName,string f_did):Command("","") {
	commodityName 		= cName;
	filter_dealer_id 	= f_did;
}


string ListCommand::execute(MarketPtr market,string dealer_id) {
	cout<<"Executing the List Command for "<<dealer_id<<endl;
	vector<OrderInfoPtr> order_list = market->get_order_list();
	for(auto  order : order_list) {
		if(commodityName != "" && commodityName.size() != 0
				&& commodityName != order->get_commodity_name()) {
			continue;
		}
		if( filter_dealer_id != "" && filter_dealer_id.size() != 0 
				&& filter_dealer_id != order->get_dealer_id()) {
			continue;
		}
		success_string += order->to_string();
		success_string += "\n";
	}
	success_string += "END OF LIST";
	return success_string;
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
	//cout<<"Executing the Aggress Command with the arg size = "<<apairList.size()<< endl;
	string successful_aggress_orders="";
	for(auto arg : apairList) {
		OrderInfoPtr order  = market->aggress_order(arg.orderId,arg.amount);
		if(order) {
			string action = order->get_commodity_side() == "BUY"? "SOLD":"BOUGHT";
			string amount = boost::lexical_cast<string>(arg.amount);
			string commodity_name = order->get_commodity_name();
			string price = Utility::convert_double_to_string(order->get_commodity_price());
			string source_dealer_id =  order->get_dealer_id();
			successful_aggress_orders +=
				action+"  "+ amount+" "+commodity_name+" @ "+price+" FROM "+source_dealer_id+"\n";
		}else {
			return ErrorMsgs::UN_ORDER;
		}
	}
	return successful_aggress_orders;
}
