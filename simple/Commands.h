#ifndef COMMANDS_HH
#define COMMANDS_HH


#include <iostream>
using namespace std;


class Command {  
	public:
		virtual ~Command();
		virtual int execute() = 0;
};

class PostCommand:public Command {
	public:
		explicit PostCommand(string,string,int ,double);
		int execute();

	private:
		string buyOrSell;
		string commodityName;
		int commodityAmount;
		double commodityPrice;
};

class RevokeCommand:public Command {
  	public:
		RevokeCommand();
		int execute();
};


#endif
