/**************************************************************************************************************************************************************
*Title		: main function(Driver function)
*Description	: This function is used as the driver function for the all the functions
***************************************************************************************************************************************************************/
#include <stdlib.h>

#include "apc.h"
int _CRT_glob = 0;
int print_answer(Dlist **headR)
{
	if (headR == NULL) return FAILURE;

	Dlist *tempR = *headR;
	while (tempR != NULL) {
		printf("%c", tempR->data);
		tempR = tempR->next;
	}
	printf("\n");

	return SUCCESS;
}
void free_list(Dlist **head) {
	Dlist *temp;
	while (*head != NULL) {
		temp = *head;
		*head = (*head)->next;;
		free(temp);
	}
}

void createDlist(Dlist **head, Dlist **tail,const char *str) {
	for (int i = 0;str[i]!='\0';i++) {
		 Dlist *new_node = (Dlist *) malloc(sizeof(Dlist));
		if (new_node==NULL) {
			exit(1);
		}
		new_node->data =(unsigned char) str[i];
		new_node->next = NULL;
		new_node->prev = NULL;

		if (*head == NULL) {
			*head = new_node;
			*tail = new_node;
		}else {
			new_node->prev = *tail;
			(*tail)->next = new_node;
			*tail = new_node;
		}

	}

}

int validate_numbers( char *str) {
	if (str == NULL || str[0] == '\0' ) {
		return 0;
	}

	for (int i=0;str[i]!='\0';i++) {
		if (!isdigit((unsigned char)str[i])) {
           return FAILURE;
		}
	}
   return SUCCESS;
}
int validate_number_cla(int argc, char *argv[])
{
	// printf("argc = %d\n", argc);
	// printf("argv[1] = %s\n", argv[1]);
	// printf("argv[2] = %s\n", argv[2]);
	// printf("argv[3] = %s\n", argv[3]);
	// printf("operator = %c\n", argv[2][0]);

	if (argv[2][0] != '+' &&
		argv[2][0] != '-' &&
		argv[2][0] != '*' &&
		argv[2][0] != '/')
	{
		printf("usage: %s [number] [operator] [number]\n", argv[0]);
		return FAILURE;
	}

	return SUCCESS;
}
int main(int argc, char *argv[])
{
	if (validate_number_cla(argc, argv) != SUCCESS) {
		return 1;
	}

	if (validate_numbers(argv[1])!=SUCCESS||validate_numbers(argv[1])!=SUCCESS) {
		return 1;
	}




	/* Declare the pointers */
	Dlist *head1=NULL, *tail1=NULL;
	Dlist *head2=NULL, *tail2=NULL;
	Dlist *headR=NULL;
	char option, operator;

	 createDlist(&head1, &tail1, argv[1]);
	 createDlist(&head2, &tail2, argv[3]);

	do
	{
		/* Code for reading the inputs */

		/* Function for extracting the operator */
		operator = argv[2][0];
		switch (operator)
		{
			case '+':
				/* call the function to perform the addition operation */
                addition(&head1, &tail1, &head2, &tail2, &headR);
				printf("answer:\n");
				print_answer(&headR);
				free_list(&headR);
				break;
			case '-':
				subtraction(&head1,&tail1,&head2,&tail2,&headR);
				printf("answer:\n");
				print_answer(&headR);
				free_list(&headR);
				break;
				break;
			case '*':	
				/* call the function to perform the multiplication operation */
				multiplication(&head1,&tail1,&head2,&tail2,&headR);
				printf("answer:\n");
				print_answer(&headR);
				free_list(&headR);
				break;
			case '/':	
				/* call the function to perform the division operation */
				division(&head1,&tail1,&head2,&tail2,&headR);
				printf("answer:\n");
				print_answer(&headR);
				free_list(&headR);
				break;
			default:
				printf("Invalid Input:-( Try again...\n");
		}
		printf("Want to continue? Press [yY | nN]: ");
		scanf("\n%c", &option);
	}while (option == 'y' || option == 'Y');
	free_list(&head1);
	free_list(&head2);
	return 0;
}
