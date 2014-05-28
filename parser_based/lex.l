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

[^+-][0-9]*\.[0-9]{1,}  {
			yylval.dval = atof(yytext);
	       	 	return TOK_DOUBLE;
		}

DB|JPM|UBS|RBC|BARX|MS|CITI|BOFA|RBS|HSBC    {
			yylval.string = strdup(yytext);
			return TOK_DELEAR_ID;            
		}

GOLD|SILV|PORK|OIL|RICE   {
		yylval.string = strdup(yytext);
		return TOK_COMMODITY;
	}
POST 							return TOK_POST;
REVOKE 	{
		printf("Token revoke %s\n",yytext);
		return TOK_REVOKE;
	}

CHECK 	{
		yylval.ival = atoi(yytext);
		return TOK_CHECK;
	}
LIST 	{
		return TOK_LIST;
	}
BUY|SELL   {     					
		yylval.ival = !strcmp(yytext,"BUY");
		return TOK_BUY;
	}

[ \n\t\r]+ /*Ignore whitespace*/
. 	yyerror("Parsing error\n");

%%
