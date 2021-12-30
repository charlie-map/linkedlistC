#include <stdio.h>
#include <stdlib.h>

#include "ll.h"

int printNumber(void *num) {
	printf("The number: %d\n", *(int *) num);

	return 0;
}

int destroyNumber(void *num) {
	free((int *) num);

	return 0;
}

int main() {
	// simple normal linked list with no weight
	ll_t *ll_head = makeLL("");

	int num1 = 1;
	int num2 = 2;
	int num3 = 3;
	int num4 = 4;

	// enter a p in the third parameter to have it print this value
	insertLL(ll_head, &num1, "p", printNumber);
	insertLL(ll_head, &num2, "p", printNumber);
	insertLL(ll_head, &num3, "p", printNumber);

	// print the current list
	printf("First print\n");
	printLL(ll_head);

	// reverse the list
	reverseLL(ll_head);

	// insert the 4th value
	insertLL(ll_head, &num4, "p", printNumber);

	// print again
	printf("\nSecond print\n");
	printLL(ll_head);

	// insert a allocated integer with a delete function
	int *allocNum5 = malloc(sizeof(int));
	*allocNum5 = 5;
	// note that the order of the "p" and "d" does not matter as long
	// as the functions are in the same order
	insertLL(ll_head, allocNum5, "pd", printNumber, destroyNumber);

	// print a last check
	printf("\nThird print\n");
	printLL(ll_head);

	// destroy
	destroyLL(ll_head);

	return 0;
}