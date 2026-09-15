/*******************************************************************************************************************************************************************
*Title			: Division
*Description		: This function performs division of two given large numbers and store the result in the resultant list.
*Prototype		: int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
*Input Parameters	: head1: Pointer to the first node of the first double linked list.
			: tail1: Pointer to the last node of the first double linked list.
			: head2: Pointer to the first node of the second double linked list.
			: tail2: Pointer to the last node of the second double linked list.
			: headR: Pointer to the first node of the resultant double linked list.
*Output			: Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/
#include <stdlib.h>

#include "apc.h"
int is_zero(Dlist *head) {
	printf("iszero_called\n");
	Dlist *p= head;
	while (p != NULL) {
		if (p->data-'0' != 0) {
			printf("check: %d\n",p->data-'0');
			return 1;
		}
		p= p->next;
	}
 return 0;
}

int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR)
{
	printf("division function called from main \n");
	// here we are checking is divisor is zero
	if (is_zero(*head2)!=1) {
		printf("divisor is zero\n");
		return FAILURE;
	}

	// here we call function compare so that we can verify the divisor is bigger than dividend
	const int divisor_check= compare(*head1, *head2);
	if (divisor_check) {
		printf("head2 is big\n");
		return FAILURE;
	}
	Dlist *temp1= *head1;



	printf("head2 data\n");
	while (temp1 != NULL) {
		int num = (temp1)->data - '0';
		printf("head1 : %d\n",(temp1)->data-'0');
		temp1 = temp1->next;
		Dlist *temp_val = (Dlist *)malloc(sizeof(Dlist));
		if (temp_val == NULL) {
			return FAILURE;
		}

		temp_val->data = num;

		subtraction(head1,head2,head2,tail1,tail2);

	}

return SUCCESS;
}
