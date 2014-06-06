#ifndef COMMANDS_HH
#define COMMANDS_HH


#include <iostream>
#include <string>
#include <vector>
#include <cstdarg>
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
		explicit RevokeCommand(int id);
		int execute();

	private:
		int orderId;
};


class ListCommand:public Command {
	public:
		ListCommand();
		ListCommand(string);
		ListCommand(string,string);
		int execute();

	private:
		string commodityName;
		string dealerId;

};

class AggressCommand:public Command {
	public:
		struct APair{
			int orderId;
			int amount;
		} ;
		typedef struct APair APair;

	public:
		AggressCommand(int numOfArgs,...);
		AggressCommand(vector<APair> apArg);
		int execute();


	private:

		vector<APair> apairList;

};

#endif
