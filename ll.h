#ifndef __LL_T__
#define __LL_T__

typedef struct LinkedListPointer ll_t;

ll_t *makeLL(char *param, ...);

// p is in reference to "p"ointer
void *insertLL(ll_t *ll_p, void *payload, char *param, ...);
void *peekheadLL(ll_t *ll_p);
void *popheadLL(ll_t *ll_p);

void *nextLL(void *ll_p)
int reverseLL(ll_t *ll_p);

int printLL(ll_t *ll_p);

int destroyLL(ll_t *ll_p);

#endif