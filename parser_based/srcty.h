#ifndef TYPES_HH
#define TYPES_HH

#include <string.h>
#include <stdio.h>

/*Type Information*/
typedef enum {
       TypeConsInt,
       TypeConstDouble,
       TypeConstString
       
}BBType;


/**/
typedef enum {
	POST,
	REVOKE,
	CHECK,
	LIST,
	AGRESS                                        	
} OperationType;

extern int sym[26];

typedef struct {
	BBType type;
	union {
		double d;
		int i ;
		char *str;
	};
} Operator;

typedef struct {
	OperationType opType;
	int nops;	
	Operator *ops[10];	
}OprNodeType;

OprNodeType* opr(OperationType opType, int nops,...);
int ex(char *dealer_id,OprNodeType *);

#endif
