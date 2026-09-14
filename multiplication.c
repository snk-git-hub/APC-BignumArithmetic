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

//this will append zero at end according to shift
Dlist *appent_zero(Dlist **head1, Dlist **tail1, int shift) {

	// this for loop will iterate from zero to  shift
	for (int i=0; i<shift; i++) {
		// dynamic  allocate a node
		Dlist *new_node =(Dlist *) malloc(sizeof(Dlist));
		// null check if its created or not
		if(new_node==NULL) {
			return  NULL;
		}
		// set '0' to the next_node of the data
		new_node->data = '0';
		// set  new_node -> NULL
		new_node->next = NULL;
		// check if head is null / if head is not pointing to anything before
		if (*head1==NULL) {
			//set new_node -> previous as NULL
			new_node->prev = NULL;
			// set new_node as the head
			*head1 = new_node;
		}
		// else is for if head is  not null and the new node is not the first node
		//*
		//
		//              head                      tail
		//               |                         |
		//               v                         v
	    //  NULL <---   ['1'] <----> ['3'] <----> ['7'] ---> NULL
		//
		//
	    //
		//           head                                                   tail
		//            |                                                      |
		//            v                                                     v
		// NULL <---['1'] <----> ['3'] <----> ['7'] <----> ['0'] <----> ['0'] ---> NULL
		//
		//
		//*//
		else {
			//  so now prev  point will be at the  right end

			//     head                            tail
			//      /                              \
			//     V                               V
			//    [1] <---> [2] <----> [3] <----> [4]--n-->                  <--p--[0]--n-->
			//                               // tail next to new node       // new node previous to tail
			new_node->prev = *tail1;
			//
			(*tail1)->next = new_node;
		}
		// set new_node as tail
		*tail1 = new_node;
	}

	return *head1;

}
Dlist *multiplication_of_single_list(Dlist *tail1,int digit,Dlist **partial_tail) {
        // make a node with null
		Dlist *result=NULL;
	   // global declaration to hold carry which is assigned as zero
		int carry = 0;
	// we start a while loop which goes till the Null ,
	// which fetch each digit of  list 1
	// we are iterating from back to front
		while (tail1!= NULL) {
            // here we extract fist node data from tail
			// - ' 0 ' will convert char digit to int
			// and store to num2
			int num2 = tail1->data - '0';
			// here we calculate the product , and add carry of the previous to  next
			int product = (digit * num2)+carry;
			// extract the ans without  carry  for eg : 12 it keeps 2, 12 mod 10 is 2
			int ans = product%10;
			// printf("%d",ans);
			// this will fetch carry  for eg  12 it willtake 1 ,  12 / 10 = 1 (1.2);
			carry = product/10;
			// now we dynamically allocate a new node
			Dlist *new_node =(Dlist *) malloc(sizeof(Dlist));
			// safety NULL check
			if (new_node==NULL) {
				// set partition tail as null becase there is no node to point
			    *partial_tail = NULL;
				// return null
				return NULL;
			}
			//  set answer to the new node
			new_node->data = ans+'0';
			// set new_node -> previous as null
			new_node->prev=NULL;
			// now  we will  tie new_node to the result
			new_node->next = result;
			// if result is null and there is no other before
			if (result!=NULL) {
				// set new_node as result_prev
				result->prev = new_node;
			}
			// set new_node as result the end
			result = new_node;

			// printf("%d * %d \n",num1,temp1 ->data -'0');
           // move  back ward
			tail1 = tail1 -> prev;
		}

// handling leftover carry as extra digit(S) at the front
while (carry > 0) {  // if final carry is missing (e.g. 9*9=81 -> leftover 8) was previously dropped entirely
Dlist *new_node = (Dlist * ) malloc(sizeof(Dlist));
	// same stuff that we have already done to insert  node on dll at front
	if (new_node == NULL) {
		*partial_tail = NULL;
		return NULL;
	}
	// take the 8 from 89
	new_node -> data = (carry % 10)+'0';
	// put new_node -> prev as NULL
	new_node -> prev = NULL;
	//  new_node ->next point to result
	new_node -> next = result;
	// null check
	if (result != NULL) {
		// put result -> prev to new_node;
		result->prev = new_node;
	}
	// make result as new_node
	result = new_node;
	//remove  the digit from carry
	carry /= 10;
}
	// null check if result is null partial_tail is null too
	if (result==NULL) {
		*partial_tail = NULL;
		return NULL;
	}
	// temp t   as result
	Dlist *t = result;
	// loop till end
	while (t->next != NULL) t = t->next;
	//and make last node as tail
	*partial_tail = t;
	// at last return result
	return result;
}
	



	int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR){
		/* Definition goes here */
	     // define result_head and result tail
	    // head point to first     tail point to last , node
	    Dlist *result_head=NULL;
	    Dlist *result_tail=NULL;

	    //  temp of tail2
		Dlist *temp2 = *tail2;
	    // shift will take care how much '0' to add
        int shift = 0;
	// iterate the temp2
		while (temp2!=NULL) {
			// we take right most digit of temp2
			int digit = temp2 ->data - '0';
			// we have made a partial_tail to  point to result tail
			Dlist *partial_tail = NULL;
			// partial head will take output from funtion output is result , and we passs
			// tail1  , digit , and the partial tail (passed the address)
			Dlist *partial_head = multiplication_of_single_list(*tail1, digit, &partial_tail);
             //check   is partial is pointed to tail
			if (partial_head==NULL) {
				// return fail
	              return FAILURE;
              }
			// we need to append zero for multiple number multiplication
			//   we pass partial_head , and tail ,number of zero to put (shift)
			 if (appent_zero(&partial_head,&partial_tail,shift)==NULL && shift!=0) {
				 return FAILURE;
			 }
			// a new_total
			 Dlist *new_total =NULL;
			// called addition  result head , result tail    partial head    partial tai;          new_total
			// at beginning  result head is NULL and tail is NULL , partial head will be the current result
			// after first  result head will be updated with sum previous multiplication  results
            int add_status= addition (&result_head, &result_tail,&partial_head, &partial_tail, &new_total);
			if (add_status!=SUCCESS) {
				return FAILURE;
			}

			// freee
			free_list(&result_head);
			free_list(&partial_head);

			// after addition call  result head as new_total
			result_head = new_total;
			result_tail = new_total;
			while (result_tail->next != NULL) result_tail = result_tail->next;
			 temp2=temp2->prev;
			shift++;

		}
	    *headR = result_head;

		return  SUCCESS;
	}

