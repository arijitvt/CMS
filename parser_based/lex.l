%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

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
		yylval.string = strdup(yytext);
#ifdef DEBUG
		printf("Dealer id is %s\n",yytext);
#endif
		return TOK_DEALER_ID;            
	}

GOLD|SILV|PORK|OIL|RICE {                                                                           
		yylval.string = strdup(yytext);
		return TOK_COMMODITY;
	}
POST 	 {
		return TOK_POST;
	}
REVOKE 	{
		return TOK_REVOKE;
	}
CHECK 	{
		return TOK_CHECK;
	}
LIST 	{
		return TOK_LIST;
	}
AGGRESS {
		return TOK_AGGRESS;
	}

BUY|SELL {     					
		yylval.ival = !strcmp(yytext,"BUY");
		return TOK_BUY;
	}

"[" 	return TOK_LEFT_SQ_BRACE;

"]" 	return TOK_RIGHT_SQ_BRACE;

[ \n\t\r]+ /*Ignore whitespace*/
. 	yyerror("Parsing error\n");

%%
