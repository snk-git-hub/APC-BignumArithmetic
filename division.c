/*******************************************************************************************************************************************************************
*Title		: Division
*Description		: This function performs division of two given large numbers and store the result in the resultant list.
*Prototype		: int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
*Input Parameters	: head1: Pointer to the first node of the first double linked list (dividend).
			: tail1: Pointer to the last node of the first double linked list (dividend).
			: head2: Pointer to the first node of the second double linked list (divisor).
			: tail2: Pointer to the last node of the second double linked list (divisor).
			: headR: Pointer to the first node of the resultant double linked list (quotient).
*Output		: Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/
#include <stdlib.h>
#include "apc.h"

//Returns 1 if the number is nonzero, 0 if it is exactly zero.
int is_nonzero(Dlist *head)
{
    Dlist *p = head;
    while (p != NULL) {
        if (p->data - '0' != 0) {
            return 1;
        }
        p = p->next;
    }
    return 0;
}

// Appends a single ASCII digit node to the end of the list pointed at by *head/*tail.
static int append_digit(Dlist **head, Dlist **tail, int digit)
{
    Dlist *node = (Dlist *)malloc(sizeof(Dlist));
    if (node == NULL) {
        return FAILURE;
    }
    node->data = digit + '0';
    node->next = NULL;
    node->prev = *tail;

    if (*head == NULL) {
        *head = node;
        *tail = node;
    } else {
        (*tail)->next = node;
        *tail = node;
    }
    return SUCCESS;
}

/*Frees every node in a list; leaves head/tail NULL.
  Renamed from free_list -> free_dlist_pair: apc.h already declares a
  single-argument free_list(Dlist **head), so a static two argument
  function with the same name here was a conflicting redeclaration
  that would not compile. */

static void free_dlist_pair(Dlist **head, Dlist **tail)
{
    Dlist *p = *head;
    while (p != NULL) {
        Dlist *next = p->next;
        free(p);
        p = next;
    }
    *head = NULL;
    if (tail != NULL) {
        *tail = NULL;
    }
}

// Deep-copies a list, returning new head or tail via out params.
static int copy_list(Dlist *src, Dlist **out_head, Dlist **out_tail)
{
    *out_head = NULL;
    *out_tail = NULL;
    while (src != NULL) {
        if (append_digit(out_head, out_tail, src->data - '0') == FAILURE) {
            free_dlist_pair(out_head, out_tail);
            return FAILURE;
        }
        src = src->next;
    }
    return SUCCESS;
}

// Strips leading '0' digits from a list (but keeps at least one digit).
static void strip_leading_zeros(Dlist **head, Dlist **tail)
{
    while (*head != NULL && (*head)->next != NULL && (*head)->data - '0' == 0) {
        Dlist *old = *head;
        *head = (*head)->next;
        (*head)->prev = NULL;
        free(old);
    }
    if (*head == NULL) {
        // shouldn't happen, but guard anyway
        append_digit(head, tail, 0);
    }
}

int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR)
{


    // Check divisor is not zero
    if (is_nonzero(*head2) != 1) {

        return FAILURE;
    }

    *headR = NULL;
    Dlist *tailR = NULL;

    // Special case: dividend smaller than divisor -> quotient is 0
    if (compare(*head1, *head2)) {

        if (append_digit(headR, &tailR, 0) == FAILURE) {
            return FAILURE;
        }
        return SUCCESS;
    }

    // remainder starts empty; we build it up digit by digit
    Dlist *remHead = NULL, *remTail = NULL;

    Dlist *temp1 = *head1;
    while (temp1 != NULL) {
        int digit = temp1->data - '0';

        /* Bring down the next digit: remainder = remainder * 10 + digit.
           This must happen unconditionally -- the previous version only
           appended when the remainder was already non-zero, which silently
           dropped digits whenever the running remainder was exactly 0. */
        if (append_digit(&remHead, &remTail, digit) == FAILURE) {
            free_dlist_pair(headR, &tailR);
            free_dlist_pair(&remHead, &remTail);
            return FAILURE;
        }
        strip_leading_zeros(&remHead, &remTail);

        // count how many times divisor fits into remainder
        int quotient_digit = 0;
        while (!compare(remHead, *head2)) {
            /*  remHead >= *head2, so we can subtract.
                subtraction()'s real signature is (head1, tail1, head2, tail2, headR):
                head1/tail1 -> the remainder (minuend)
                head2/tail2 -> the divisor, passed straight through from division()
                headR       -> where the difference's head is written
                subtraction() does not hand back a tail for its result, so we
                walk diffHead ourselves to find remTail afterward. */
            Dlist *diffHead = NULL;

            if (subtraction(&remHead, &remTail, head2, tail2, &diffHead) == FAILURE) {
                free_dlist_pair(headR, &tailR);
                free_dlist_pair(&remHead, &remTail);
                return FAILURE;
            }

            free_dlist_pair(&remHead, &remTail);
            remHead = diffHead;
            remTail = remHead;
            while (remTail != NULL && remTail->next != NULL) {
                remTail = remTail->next;
            }
            strip_leading_zeros(&remHead, &remTail);

            quotient_digit++;
        }

        if (append_digit(headR, &tailR, quotient_digit) == FAILURE) {
            free_dlist_pair(&remHead, &remTail);
            return FAILURE;
        }

        temp1 = temp1->next;
    }

    strip_leading_zeros(headR, &tailR);
    free_dlist_pair(&remHead, &remTail);

    return SUCCESS;
}