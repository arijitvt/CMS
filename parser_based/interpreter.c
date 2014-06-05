#include "srcty.h"
#include "parser.h"

#include <stdio.h>
#include <stdlib.h>

int ex(OprNodeType *dealer_id, OprNodeType *node) {
	switch(node->opType) {
		case  POST:
			printf("This is the post operation \n");
			break;

		case  REVOKE:
			printf("This is revoke operation \n");
			break;

		case CHECK:
			printf("This is the check operation \n");
			break;

		case LIST:
			printf("This is the list operation \n");
			break;
                                          
		case AGGRESS:
			printf("This is aggress operation\n");
			break;

		default:
			printf("This is the default case with operation type %d\n",node->opType);
	}
	return 0;
}
