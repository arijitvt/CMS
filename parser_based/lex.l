%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

#define ECHO fwrite(yytext, yyleng, 1, yyout)

	void yyerror(const char *);
%}

%%

[1-9][0-9]* 	{
			yylval.ival = atoi(yytext);
			return TOK_INTEGER;			
		}

[^+-][0-9]*\.[0-9]{1,} { 
		yylval.dval = atof(yytext);
		return TOK_DOUBLE;
	}

DB|JPM|UBS|RBC|BARX|MS|CITI|BOFA|RBS|HSBC {
		ECHO;
		yylval.string = strdup(yytext);
#ifdef DEBUG
		printf("Dealer id is %s\n",yytext);
#endif
		return TOK_DEALER_ID;            
	}

GOLD|SILV|PORK|OIL|RICE {                                                                           
		ECHO;
		yylval.string = strdup(yytext);
		return TOK_COMMODITY;
	}
POST 	 {
		ECHO;
		return TOK_POST;
	}
REVOKE 	{
		ECHO;
		return TOK_REVOKE;
	}
CHECK 	{
		ECHO;
		return TOK_CHECK;
	}
LIST 	{
		ECHO;
		return TOK_LIST;
	}
AGGRESS {
		ECHO;
		return TOK_AGGRESS;
	}

BUY|SELL {     					
		ECHO;
		yylval.ival = !strcmp(yytext,"BUY");
		return TOK_BUY;
	}
\n 	{
	return TOK_ENDL;
}


[ \t\r]+ 	ECHO; /*Ignore whitespace*/
. 	yyerror("Parsing error\n");

%%
