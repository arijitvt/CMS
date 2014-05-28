%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include "srcty.h"

void yyerror(const char *);
OprNodeType* opr(OperationType opType, int nops,...);
%}

%start QRY

%union{
	int ival;      
	double dval;
	char *string;
	struct OprNodeType *nodeTy;
	struct Operator *opType;
};


%token <ival> 	TOK_INTEGER  
%token <dval> 	TOK_DOUBLE
%token <string> TOK_DELEAR_ID 
%token <string> TOK_COMMODITY
%token TOK_POST TOK_REVOKE TOK_CHECK TOK_LIST 
%token <ival> 	TOK_BUY

%type <nodeTy> INPUT_MESSAGE 
%type <nodeTy> COMMAND 
%type <nodeTy> POST_COMMAND 
%type <nodeTy> REVOKE_COMMAND 
%type <nodeTy> CHECK_COMMAND 
%type <nodeTy> ORDER_ID 
%type <opType> SIDE COMMODITY AMOUNT PRICE
%type <string> DELEAR_ID
%%

QRY : /* */
    | QRY INPUT_MESSAGE {
    	printf("This is the input Message \n");
    }
;

INPUT_MESSAGE: DELEAR_ID COMMAND  {
	       ex($1,$2);
	     }
;	     

DELEAR_ID: TOK_DELEAR_ID {
		$$ = $1;
	 }
;

COMMAND: POST_COMMAND {
       		$$ = $1;
       } 
       | REVOKE_COMMAND {
       		printf("Coming to the revoke command\n");
        	$$ = $1;
	}
       | CHECK_COMMAND {
       		$$ = $1;
       }
;

POST_COMMAND: TOK_POST SIDE COMMODITY AMOUNT PRICE
	    {
			printf("This is the message \n");	    	
	    	        $$ = opr(POST,4,$2,$3,$4,$5);
	    }
;

REVOKE_COMMAND:TOK_REVOKE ORDER_ID
	      {
		      	printf ("Invoking revoke command\n");
		        $$ = opr(REVOKE,1,$2);
	      }
;

CHECK_COMMAND:TOK_CHECK ORDER_ID 
	     {
	     	printf("Invoking check command \n");
		$$ = opr(CHECK,1,$2);
	     }
;

SIDE: TOK_BUY 
    {
    	printf("Token buy or sell %d\n",$1);
	Operator *node = (Operator*)malloc(sizeof(Operator));
	node->type = 0;
	node->i=$1;
	$$  = node;
    }
;

COMMODITY : TOK_COMMODITY
	{
        	printf("The token commodity \n");
		Operator *node = (Operator*)malloc(sizeof(Operator));
		node->type = 2;
		node->i=$1;
		$$ = node;
	}
;


AMOUNT: TOK_INTEGER
	{
        	printf("The  Amount \n");
		Operator *node = (Operator*)malloc(sizeof(Operator));
		node->type = 0;
		node->i=$1;
		$$ = node;
	}
;

PRICE: TOK_DOUBLE
	{
        	printf("The  Price \n");
		Operator *node = (Operator*)malloc(sizeof(Operator));
		node->type = 1;
		node->i=$1;
		$$ = node;
	}
;

ORDER_ID:TOK_INTEGER
	{
        	printf("The  Order Id \n");
		Operator *node = (Operator*)malloc(sizeof(Operator));
		node->type = 0;
		node->i=$1;
		$$ = node;
	}
;

%%

OprNodeType *opr(OperationType opType, int nops,...) 
{
	va_list  ap;
	OprNodeType *node;
	node = (OprNodeType*) malloc(sizeof(OprNodeType));
	if(node == NULL) {
		yyerror("Out of memory \n");
	}	
	printf("Operation type is  %d\n", opType);
	node->opType = opType;
	node->nops = nops;
	va_start(ap,nops);
	int i;
	for(i  =0 ; i <  nops; ++i) {
		Operator *op = (Operator*)(malloc(sizeof(Operator)));
		op = va_arg(ap,Operator*);
		node->ops[i]=op;
	}
	va_end(ap);
	printf("Sending node %d\n",node);
	return  node;
}

void yyerror(const char *msg) 
{
	fprintf(stderr,"error in parsing: %s \n",msg);	
}

int yywrap() 
{
	return 1;
}


main() 
{
	yyparse();
}
