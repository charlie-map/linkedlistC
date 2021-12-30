#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "ll.h"

int printInt(void *test) {
	printf("\tPrint test: %d\n", *(int *) test);

	return 0;
}

int destroyInt(void *test) {
	free((int *) test);

	return 0;
}

// assumes int *
int weight(void *firstElement, void *secondElement) {
	return *(int *) firstElement < *(int *) secondElement;
}

int test() {

	// unstructured input with no weight
	ll_t *ll_1 = makeLL("");
	assert(ll_1);

	// some simple int * tests with no print or destroy
	int test1 = 50;
	insertLL(ll_1, &test1, "");
	int test2 = 500;
	insertLL(ll_1, &test2, "");
	int test3 = 750;
	insertLL(ll_1, &test3, "");

	assert(*(int *) peekheadLL(ll_1) == 50);
	// reverse
	reverseLL(ll_1);
	assert(*(int *) peekheadLL(ll_1) == 750);
	assert(*(int *) popheadLL(ll_1) == 750);

	// malloced value with a destroy function
	int *test4 = malloc(sizeof(int));
	*test4 = 30;
	insertLL(ll_1, test4, "d", destroyInt);

	assert(*(int *) peekheadLL(ll_1) == 500);

	// normal
	reverseLL(ll_1);
	assert(*(int *) peekheadLL(ll_1) == 30);
	assert(*(int *) popheadLL(ll_1) == 30);
	free(test4);

	assert(*(int *) peekheadLL(ll_1) == 50);

	destroyLL(ll_1);


	// next a weighted linked list
	ll_t *ll_2 = makeLL("w", weight);

	// use a malloced weights in semi-structured format
	int **integerArray = malloc(sizeof(int *) * 550);
	// insert backwards to ensure weighting function is working
	for (int enterValues = 549; enterValues >= 0; enterValues--) {
		integerArray[enterValues] = malloc(sizeof(int));

		*integerArray[enterValues] = enterValues;

		// use both print and destroy
		if (enterValues <= 499)
			insertLL(ll_2, integerArray[enterValues], "pd", printInt, destroyInt);
	}

	assert(*(int *) peekheadLL(ll_2) == 0);
	assert(*(int *) popheadLL(ll_2) == 0);
	free(integerArray[0]);

	for (int deleteSomeValue = 1; deleteSomeValue < 100; deleteSomeValue++) {
		assert(*(int *) peekheadLL(ll_2) == deleteSomeValue);
		assert(*(int *) popheadLL(ll_2) == deleteSomeValue);
		free(integerArray[deleteSomeValue]);
	}

	// test reverse
	reverseLL(ll_2);
	assert(*(int *) peekheadLL(ll_2) == 499);
	assert(*(int *) popheadLL(ll_2) == 499);
	free(integerArray[499]);
	assert(*(int *) peekheadLL(ll_2) == 498);

	// insert the rest of the items
	for (int addFinal50 = 549; addFinal50 >= 500; addFinal50--) {
		// should theoretically be inserted as the first 50
		insertLL(ll_2, integerArray[addFinal50], "pd", printInt, destroyInt);
	}

	assert(*(int *) peekheadLL(ll_2) == 549);
	
	// test normal
	reverseLL(ll_2);

	// check current smallest
	assert(*(int *) peekheadLL(ll_2) == 100);

	destroyLL(ll_2);
	free(integerArray);

	return 0;
}

int main() {
	// run tests
	test();

	// running with valgrind can also ensure no memory leakage
	printf("\nALL TESTS PASSED\n");

	return 0;
}