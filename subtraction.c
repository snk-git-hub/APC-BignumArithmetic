/*******************************************************************************************************************************************************************
*Title			: Subtraction
*Description		: This function performs subtraction of two given large numbers and store the result in the resultant list.
*Prototype		: int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
*Input Parameters	: head1: Pointer to the first node of the first double linked list.
			: tail1: Pointer to the last node of the first double linked list.
			: head2: Pointer to the first node of the second double linked list.
			: tail2: Pointer to the last node of the second double linked list.
			: headR: Pointer to the first node of the resultant double linked list.
*Output			: Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/

#include <stdlib.h>

#include "apc.h"

int compare(const Dlist *head_a, const Dlist *head_b) {
	Dlist sig1 = *head_a;
	Dlist sig2 = *head_b;

	int len1 =0;
	for (Dlist *p = &sig1;p!=NULL;p=p->next) len1++;
	int len2 =0;
	for (Dlist *p = &sig2;p!=NULL;p=p->next) len2++;
	// flag to check is list2 is bigger
	int list2_bigger=0;
	// checking which is bigger
	if (len1<len2) {
		// if list2 is bigger set flag to 1
		list2_bigger =1;
	}
	// else if both are of sme lenght
	else if (len1==len2) {
		Dlist *p1 = &sig1,*p2 = &sig2;
		// "So we just iterate from left to right and check in which list the digit
		// in the highest place (digit of num1 or num2) is bigger."
		while (p1!=NULL){
			if (p1->data>p2->data) {list2_bigger=0;break;}
			if (p1->data<p2->data) {list2_bigger=1;break;}
			p1=p1->next;
			p2=p2->next;
		}
	}
	return list2_bigger;
}



int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR) {
	/* Definition goes here */
	// skipping leading zeros
	Dlist *sig1 = *head1;
	while (sig1->data =='0'&& sig1->next!=NULL) sig1=sig1->next;
	Dlist *sig2 = *head2;
	while (sig2->data =='0'&& sig2->next!=NULL) sig2=sig2->next;
    //


	int list2_bigger = compare(sig1,  sig2);

	// here we set temp1 as biggest according to list2 is bigger or not
	Dlist *temp1 =list2_bigger? *tail2: *tail1;
	Dlist *temp2 =list2_bigger? *tail1: *tail2;


	Dlist *tempR = NULL;
	int flag = 0;

   // substraction started
	while (temp1!=NULL || temp2!=NULL) {
		int d1 = (temp1!=NULL)?(temp1)->data -'0':0;
		int d2 = (temp2!=NULL)?(temp2)->data -'0':0;
// if flag is 1
		if (flag==1) {
			d1=d1-1;
			flag=0;
		}
		int sub;
		// if greater we need to borrow
		if (d1<d2) {
			flag = 1;
			// if num1 is 2 nd num2 is 3 we need to borrow
			// so we just make num1 + 10 so we will get 12
			// and we set flag to 1
			sub = (d1+10)-d2;
		}else {
			// else normal substraction
			sub = d1-d2;
		}

		// result storing
		// and once we get the result the next step is to store that in list
		// that's what we are doing here

		// step1:  we  have dynamically allocated a node  which named as newnode
		Dlist *new_node=(Dlist *)malloc(sizeof(Dlist));
		// and if it's not allocated it will be null se we just checked that here and if its true return FALURE
		if (new_node==NULL) {
			 free_list(&tempR);
			return FAILURE;
		}
		// set new_node data as result +'0'(char to int)

		new_node->data=sub+'0';
		// set new_node prev s null              NULL<--p--[newnode]
		new_node->prev=NULL;
		//   [new_node ]---n--->  [tempR]
		new_node->next=tempR;
		// check if new node is not NULL
		if (tempR!=NULL) {

			//  |        |           |     |
 			//  |new_node|---n--->   |tempR|
			//  |        |  <---p--- |     |

			tempR->prev = new_node;
		}
		// made tempR as new node   {tempR}
		//                             |
		//							   V
		//                         \new_node\

		tempR= new_node;

		//  move
		if (temp1!=NULL)temp1 = temp1->prev;
		if (temp2!=NULL)temp2 = temp2->prev;
	}


	    // removing  trailing zero
	while (tempR->data=='0'&&tempR->next!=NULL) {
		Dlist *tofree = tempR;
		tempR=tempR->next;
		tempR->prev= NULL;
		free(tofree);
	}

	  //  set sign
	if (list2_bigger&& tempR->data!='0') {
		Dlist *sign_node=(Dlist *)malloc(sizeof(Dlist));
		if (sign_node==NULL) {
			free_list(&tempR);
			return FAILURE;
		}
		sign_node->data= '-';
		sign_node->prev=NULL;
		sign_node->next=tempR;
		tempR->prev=sign_node;
		tempR=sign_node;

	}

	*headR=tempR;

	return SUCCESS;
}