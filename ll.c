#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

#include "ll.h"

typedef struct LinkedList {
	void *payload;

	// possible pointer for printing (use "p" in the inserLL param to add a print function)
	int (*print)(void *);
	// possible destruction for this pointer (use "d")
	int (*destroy)(void *);

	struct LinkedList *next;
	struct LinkedList *prev;
} ll_load_t;

ll_load_t *new_ll_load(void *payload) {
	ll_load_t *new_ll = (ll_load_t *) malloc(sizeof(ll_load_t));

	new_ll->payload = payload;

	new_ll->print = NULL;
	new_ll->destroy = NULL;

	new_ll->next = NULL;
	new_ll->prev = NULL;

	return new_ll;
}

struct LinkedListPointer {
	ll_load_t *head;

	// tells the direction of the linked list
	// used for reversing the list
	// 1: normal linked list direction
	// 0: reverse linked list direction
	int direction;

	// weight for if the linked list is ordered
	int (*weight)(void *, void *);
};

ll_t *makeLL(char *param, ...) {
	va_list extra_input;
	va_start(extra_input, param);

	ll_t *new_ll_p = (ll_t *) malloc(sizeof(ll_t));

	// default parameter settings to start
	new_ll_p->head = NULL;
	new_ll_p->direction = 1; // default behavior
	new_ll_p->weight = NULL;

	for (int check_param = 0; param[check_param]; check_param++) {
		// "w" for weight
		if ((int) param[check_param] == 119)
			new_ll_p->weight = va_arg(extra_input, int (*)(void *, void *));
	}

	return new_ll_p;
}

int insertLL(ll_t *ll_p, void *payload, char *param, ...) {
	ll_load_t *new_ll = new_ll_load(payload);

	va_list extra_input;
	va_start(extra_input, param);

	// check for print or destroy functions
	for (int check_param = 0; param[check_param]; check_param++) {
		// "d" for "d"estroy
		if ((int) param[check_param] == 100)
			new_ll->destroy = va_arg(extra_input, int (*)(void *));

		// "p" for "p"rint
		if ((int) param[check_param] == 112)
			new_ll->print = va_arg(extra_input, int (*)(void *));
	}

	// find position in the linked list
	// based on factors such as weighting
	ll_load_t *curr_ll_load = ll_p->head;

	// no head, add as head
	if (!curr_ll_load) {
		ll_p->head = new_ll;
		return 0;
	}

	// check for insertion as head (for weighted insertion)
	// for normal list weight should return true
	if (ll_p->weight && ll_p->direction && ll_p->weight(payload, curr_ll_load->payload)) {
		// splice in the new_ll as the head of the list
		// normal insertion
		ll_p->head->prev = new_ll;
		ll_p->head = new_ll;
		new_ll->next = curr_ll_load;

		return 0;
	// for reverse, the weight should return false
	} else if (ll_p->weight && !ll_p->direction && !ll_p->weight(payload, curr_ll_load->payload)) {
		// reverse the ordering of "prev" and "next"
		ll_p->head->next = new_ll;
		ll_p->head = new_ll;
		new_ll->prev = curr_ll_load;

		return 0;
	}

	// find position in linked list normal nexting
	while (ll_p->direction && curr_ll_load->next && (!ll_p->weight || !ll_p->weight(payload, curr_ll_load->payload)))
		curr_ll_load = curr_ll_load->next;

	// find position in linked list reverse nexting
	while (!ll_p->direction && curr_ll_load->prev && (!ll_p->weight || ll_p->weight(payload, curr_ll_load->payload)))
		curr_ll_load = curr_ll_load->prev;

	// if the placement is due to weight, curr_ll_load needs to move over by 1
	if (ll_p->direction && curr_ll_load->next)
		curr_ll_load = curr_ll_load->prev;
	else if (!ll_p->direction && curr_ll_load->prev)
		curr_ll_load = curr_ll_load->next;

	// splice in as curr_ll_load->next for normal nexting
	// if there is already a value at next, need to correct that value to
	// point at this new_ll
	if (ll_p->direction) {
		if (curr_ll_load->next) {
			curr_ll_load->next->prev = new_ll;
			new_ll->next = curr_ll_load->next;
		}

		curr_ll_load->next = new_ll;
		new_ll->prev = curr_ll_load;
	} else {
		if (curr_ll_load->prev) {
			curr_ll_load->prev->next = new_ll;
			new_ll->prev = curr_ll_load->prev;
		}

		curr_ll_load->prev = new_ll;
		new_ll->next = curr_ll_load;
	}

	return 0;
}

// returns the payload at the head of the list
void *peekheadLL(ll_t *ll_p) {
	return ll_p->head ? ll_p->head->payload : NULL;
}

void *popheadLL(ll_t *ll_p) {
	// check existence
	if (!ll_p->head)
		return NULL;

	// grab payload
	void *payload = ll_p->head->payload;

	// get next (if exists)
	ll_load_t *next = ll_p->direction ? ll_p->head->next : ll_p->head->prev;

	// delete current head
	free(ll_p->head);

	// update head
	ll_p->head = next;

	// ensure next->next or next->prev points to NULL
	if (ll_p->direction)
		ll_p->head->prev = NULL;
	else
		ll_p->head->next = NULL;

	return payload;
}

// because the linked list is doubly linked,
// just find the end of the list and change
// the direction of the list
int reverseLL(ll_t *ll_p) {
	ll_load_t *curr = ll_p->head;

	if (!curr) // empty list
		return 0;

	// normal search for tail
	while (ll_p->direction && curr->next)
		curr = curr->next;

	// reverse search for tail
	while (!ll_p->direction && curr->prev)
		curr = curr->prev;

	// update head from wherever curr ended
	ll_p->head = curr;

	// update direction
	ll_p->direction = ll_p->direction ? 0 : 1;

	return 0;
}

int printLL(ll_t *ll_p) {
	ll_load_t *curr = ll_p->head;

	// loop through each value and print to the console:
	while (curr) {
		// check for existence
		if (curr->print)
			curr->print(curr->payload);

		// normal print
		if (ll_p->direction)
			curr = curr->next;
		else // reverse print
			curr = curr->prev;
	}

	return 0;
}

int destroyLL(ll_t *ll_p) {
	ll_load_t *curr = ll_p->head;

	// loop through each link and destroy
	while (curr) {
		// check for existence of destroy
		if (curr->destroy)
			curr->destroy(curr->payload);

		// free the curr pointer
		ll_load_t *next = ll_p->direction ? curr->next : curr->prev;

		free(curr);

		curr = next;
	}

	free(ll_p);
	ll_p = NULL;

	return 0;
}