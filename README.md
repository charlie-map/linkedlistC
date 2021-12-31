# linked list
###### Charlie Hall

This is an implementation of a linked list that utilizes all features of linked lists, and includes generalizable weighting schemes, specified print and destroy functions for each input, and constant time reversing of the list.
The following functions are the core components of this implementation:

1. [Linked List Creation - `makeLL()`](#create-linked-list)
2. [Linked List Insertion - `insertLL()`](#insert-into-linked-list)
3. [Linked List Peek - `peakheadLL()`](#peek-at-linked-list)
4. [Linked List Pop - `popheadLL()`](#pop-off-linked-list)
5. [Linked List Reverse - `reverseLL()`](#reverse-linked-list)
6. [Linked List Print - `printLL()`](#print-linked-list)
7. [Linked List Destroy - `destroyLL()`](#destroy-linked-list)

# create linked list
Creating a linked list is relatively straightforward. Declare an `ll_t *` variable and then use the function `makeLL()` to have a linked list pointer created for you. There are some optional parameters you can use if you wish for certain features.

***Note:*** if no arguments are needed, an empty `char *` should be passed in as the argument. This would be a regular non-weighted linked list:

```C
ll_t *ll_head = makeLL("");
```

The current features utilizable are:

1. `w`: this parameter can be used for creating a weighted linked list. Each element that gets inserted will then use an inputted weight function to decide its position (versus always placing the element last). Based on `w` in the `param` input, the weight function should follow in a similar fashion (follows the general design of `printf`). The parameter would look something like the following where `weight` is a function declared as an `int (*)(void *, void *);`:
```C
ll_t *ll_weightedhead = makeLL("w", weight);
```
The first element for this function is always the payload that is being inputted. If the linked list is supposed to go from minimum to maximum, then the function should return `true` when the first input to the `weight()` is less than the second input.

*Please post issues for more features that should be considered*

# insert into linked list
Insertion will take a pointer to the head of a linked list and a `void *` payload. The third parameter works similarly to the previously mentioned strategy in [creation](#create-linked-list). A normal insertion (for either weighted or unweighted) would look like:

```C
insertLL(ll_head, (void *) somePayload, "");
```

Additional function features include:
1. `p`: an `int (*)(void *)` that can be modified to print the type of data held at that location in the linked list
2. `d`: an `int (*)(void *)` that can be created to easily free allocated memory within the linked list.

Using a single one of these features would look the same as the linked list creation, however using both (like `printf`) assumes that the functions are inputted in the same order as the character in the `char *param`. Using both would look like:

```C
insertLL(ll_head, (void *) somePayload, "pd", printSomePayload, destroySomePayload);
```

The order does not matter for either parameter as long as each matches with the character order in the `char *param`

*Please post issues for more features that should be considered*

# peek at linked list


# pop off linked list


# reverse linked list


# print linked list


# destroy linked list
