/*******************************************************************************************************************************************************************
*Title			: Multiplication
*Description		: This function performs multiplication of two given large numbers and store the result in the resultant list.
*Prototype		: int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
*Input Parameters	: head1: Pointer to the first node of the first double linked list.
			: tail1: Pointer to the last node of the first double linked list.
			: head2: Pointer to the first node of the second double linked list.
			: tail2: Pointer to the last node of the second double linked list.
			: headR: Pointer to the first node of the resultant double linked list.
*Output			: Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/
#include <stdlib.h>

#include "apc.h"
Dlist *appent_zero(Dlist **head1, Dlist **tail1, int shift) {
	for (int i=0; i<shift; i++) {
		Dlist *new_node =(Dlist *) malloc(sizeof(Dlist));
		if(new_node==NULL) {
			return  NULL;
		}
		new_node->data = '0';
		new_node->next = NULL;
		if (*head1==NULL) {
			new_node->prev = NULL;
			*head1 = new_node;
		}
		else {
			new_node->prev = *tail1;
			(*tail1)->next = new_node;
		}
		*tail1 = new_node;
	}
	return *head1;

}
Dlist *multiplication_of_single_list(Dlist *tail1,int digit,Dlist **partial_tail) {

		Dlist *result=NULL;


		int carry = 0;
		while (tail1!= NULL) {

			int num2 = tail1->data - '0';
			int product = (digit * num2)+carry;
			int ans = product%10;
			// printf("%d",ans);
			carry = product/10;
			Dlist *new_node =(Dlist *) malloc(sizeof(Dlist));
			if (new_node==NULL) {
			*partial_tail = NULL;
				return NULL;
			}
			new_node->data = ans+'0';
			new_node->prev=NULL;
			new_node->next = result;
			if (result!=NULL) {
				result->prev = new_node;
			}
			result = new_node;

			// printf("%d * %d \n",num1,temp1 ->data -'0');

			tail1 = tail1 -> prev;
		}



	
		Dlist *t = result;
	     if (t==NULL) {
		     return NULL;
	     }
		while (t->next != NULL) t = t->next;
		*partial_tail = t;
		return  result;
	}


	int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR){
		/* Definition goes here */
	     Dlist *result_head=malloc(sizeof(Dlist));
	     result_head->data = '0';
		 result_head->prev = NULL;
		 result_head->next = NULL;
	     Dlist *result_tail= result_head;
		Dlist *temp2 = *tail2;
        int shift = 0;
		while (temp2!=NULL) {
			int digit = temp2 ->data - '0';
			Dlist *partial_tail = NULL;
			Dlist *partial_head = multiplication_of_single_list(*tail1, digit, &partial_tail);

			 appent_zero(&partial_head,&partial_tail,shift);
			 Dlist *new_total =(Dlist *) malloc(sizeof(Dlist));
             addition (&result_head, &result_tail,&partial_head, &partial_tail, &new_total);
			result_head = new_total;
			result_tail = new_total;
			while (result_tail->next != NULL) result_tail = result_tail->next;
			 temp2=temp2->prev;
			shift++;

		}
	    *headR = result_head;

		return  SUCCESS;
	}

