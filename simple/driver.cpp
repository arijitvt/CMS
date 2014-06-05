#include <Lexer.h>


int CurTok; 
Parser *parser;

void handle_nums() {
	CurTok=GetToken();
}

void handle_string() {
	CurTok= GetToken();

}




void MainLoop() {
	while(1) {
		fprintf(stderr , "ready> ");
		switch(CurTok) { 

			case 	TOK_INTEGER:
			case 	TOK_DOUBLE:
				handle_nums();
				break;

			case 	TOK_DEALER_ID:
			case	TOK_COMMODITY:
			case 	TOK_SIDE:
				handle_string();
				break;

			case 	TOK_COMMAND:
				handle_command();
				break;

			default:
				cout<<"Failure to act\n";
				return ;
		}
	}

}


int main() {
	fprintf(stderr , "ready> " );
	CurTok = GetToken();
	MainLoop();
	return 0;
}
