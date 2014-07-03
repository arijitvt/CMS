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


%token TOK_ENDL

%token <ival> 	TOK_INTEGER  
%token <dval> 	TOK_DOUBLE
%token <string> TOK_DEALER_ID 
%token <string> TOK_COMMODITY
%token TOK_POST TOK_REVOKE TOK_CHECK TOK_LIST TOK_AGGRESS
%token TOK_LEFT_SQ_BRACE TOK_RIGHT_SQ_BRACE
%token <ival> 	TOK_BUY

%type <nodeTy> INPUT_MESSAGE 
%type <nodeTy> COMMAND 
%type <nodeTy> POST_COMMAND 
%type <nodeTy> REVOKE_COMMAND 
%type <nodeTy> CHECK_COMMAND 
%type <nodeTy> LIST_COMMAND 
%type <nodeTy> ORDER_ID 
%type <opType> SIDE COMMODITY AMOUNT PRICE
%type <opType> DEALER_ID
%%

QRY : /* */
    | QRY INPUT_MESSAGE {
    	#ifdef DEBUG
   	printf("This is the input Message \n");
	#endif
    }
;

INPUT_MESSAGE: DEALER_ID COMMAND TOK_ENDL {
	       ex($1,$2);
	     }
;	     

DEALER_ID: TOK_DEALER_ID {
	    	#ifdef DEBUG
	        	printf("The dealer id \n");
		#endif
		Operator *node = (Operator*)malloc(sizeof(Operator));
		node->type = 2;
		node->i=$1;
		$$ = node;
	 }
;

COMMAND: POST_COMMAND {
       		$$ = $1;
       } 
       | REVOKE_COMMAND {
        	$$ = $1;
	}
       | CHECK_COMMAND {
       		$$ = $1;
       }
       | LIST_COMMAND {
       		$$ = $1;
       }
;

POST_COMMAND: TOK_POST SIDE COMMODITY AMOUNT PRICE
	    {
	    	#ifdef DEBUG
			printf("This is the message \n");	    	
		#endif
	    	        $$ = opr(POST,4,$2,$3,$4,$5);
	    }
;

REVOKE_COMMAND:TOK_REVOKE ORDER_ID
	      {
	    	#ifdef DEBUG
		      	printf ("Invoking revoke command\n");
		#endif
		        $$ = opr(REVOKE,1,$2);
	      }
;

CHECK_COMMAND:TOK_CHECK ORDER_ID 
	     {
	    	#ifdef DEBUG
	     		printf("Invoking check command \n");
		#endif
		$$ = opr(CHECK,1,$2);
	     }
;

LIST_COMMAND: TOK_LIST COMMODITY DEALER_ID 
	    {
	    	printf("Largest list command\n");
		$$ = opr(LIST,1,$2);
	    }  
;



SIDE: TOK_BUY 
    {
	#ifdef DEBUG
    		printf("Token buy or sell %d\n",$1);
	#endif
	Operator *node = (Operator*)malloc(sizeof(Operator));
	node->type = 0;
	node->i=$1;
	$$  = node;
    }
;

COMMODITY : TOK_COMMODITY
	{
	    	#ifdef DEBUG
	        	printf("The token commodity \n");
		#endif
		Operator *node = (Operator*)malloc(sizeof(Operator));
		node->type = 2;
		node->i=$1;
		$$ = node;
	}
;


AMOUNT: TOK_INTEGER
	{
	    	#ifdef DEBUG
        		printf("The  Amount \n");
		#endif
		Operator *node = (Operator*)malloc(sizeof(Operator));
		node->type = 0;
		node->i=$1;
		$$ = node;
	}
;

PRICE: TOK_DOUBLE
	{
	    	#ifdef DEBUG
        		printf("The  Price \n");
       		#endif
		Operator *node = (Operator*)malloc(sizeof(Operator));
		node->type = 1;
		node->i=$1;
		$$ = node;
	}
;

ORDER_ID:TOK_INTEGER
	{
	    	#ifdef DEBUG
        		printf("The  Order Id \n");
		#endif
		Operator *node = (Operator*)malloc(sizeof(Operator));
		node->type = 0;
		node->i=$1;
		$$ = node;
	}
;

%%

OprNodeType *opr(OperationType opType, int nops,...) 
{
	printf("Calling function %s\n",__func__);
	va_list  ap;
	OprNodeType *node;
	node = (OprNodeType*) malloc(sizeof(OprNodeType));
	if(node == NULL) {
		yyerror("Out of memory \n");
	}	
	#ifdef DEBUG
		printf("Operation type is  %d\n", opType);
	#endif
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
	#ifdef DEBUG
		printf("Sending node %d\n",node);
	#endif
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
