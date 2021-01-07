#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

linkedlist_t * 
linkedlist_alloc (int unit) 
{
	linkedlist_t * l = (linkedlist_t *) malloc(sizeof(linkedlist_t)) ;
	l->left = l  ;	
	l->right = l ;
	l->element = malloc(sizeof(int)) ;
	int * u = (int *) l->element ;
	*u = unit ;

	return l ;
}

void
linkedlist_free (linkedlist_t * l, void (* free_element)(void * e))
{
	node_t * curr ;
	node_t * next ;

	curr = l->right ;
	while (curr != l) {
		next = curr->right ;
		if (free_element != 0x0)
			free_element(curr->element) ;
		free(curr->element) ;
		free(curr) ;
		curr = next ;
	}
	free(l->element) ;
	free(l) ;
}

int 
linkedlist_length (linkedlist_t * l)
{
	int len = 0 ;

	node_t * curr = l->right ;
	while (curr != l) {
		len += 1 ;
		curr = curr->right ; 
	}
	return len ; 
}

void
linkedlist_print (linkedlist_t * l, void (* print_element)(void * e))
{
	node_t * curr ;
	node_t * next ;

	curr = l->right ;
	while (curr != l) {
		print_element(curr->element) ;
		curr = curr->right ;
	}
}

void 
linkedlist_insert (node_t * left, void * e, int unit)
{
	node_t * _new = (node_t *) malloc(sizeof(node_t)) ;
	_new->element = malloc(unit) ;
	memcpy(_new->element, e, unit) ;

	node_t * right = left->right ;

	_new->left = left ;
	_new->right = right ;

	left->right = _new ;
	right->left = _new ;
}

void
linkedlist_insert_first (linkedlist_t * l, void * e)
{
	linkedlist_insert(l, e, *((int *)(l->element))) ;
}

void
linkedlist_insert_last (linkedlist_t * l, void * e)
{
	linkedlist_insert(l->left, e, *((int *)(l->element))) ;
}

int
linkedlist_remove (linkedlist_t * l, node_t * n)
{
	if (l->left == l)
		return 1 ;

	n->left->right = n->right ;
	n->right->left = n->left ;

	free(n->element) ;
	free(n) ;
	return 0 ;
}

int 
linkedlist_remove_first (linkedlist_t * l, void * e)
{
	if (l->right == l)
		return 1 ;

	memcpy(e, l->right->element, *((int *)(l->element))) ;
	linkedlist_remove(l, l->right) ;
	return 0 ;
}

int
linkedlist_remove_last (linkedlist_t * l, void * e)
{
	if (l->left == l)
		return 1 ;

	memcpy(e, l->left->element, *((int *)(l->element))) ;
	linkedlist_remove(l, l->left) ;
	return 0 ;
}

int 
linkedlist_get (linkedlist_t * l, int pos, void * e)
{
	if (pos < 0)
		return 1 ;

	int unit = *((int *) l->element) ;
	int i = 0 ;
	node_t * curr = l->right ;
	while (i < pos && curr != l) {
		curr = curr->right ;
		i += 1 ;
	}
	if (i != pos)
		return 1 ;

	memcpy(e, curr->element, unit) ;
	return 0 ;
}

void
linkedlist_sort (linkedlist_t * l, int ( cmp_elements)(void * e1, void * e2)) 
{
	node_t * i, * j, * m ;

	int unit = *((int *)(l->element)) ;

	for (i = l->right ; i != l ; i = i->right) {
		m = i ;
		for (j = i->right ; j != l ; j = j->right) {
			if (cmp_elements(j->element, m->element) < 0)
				m = j ;
		}

		void * t = i->element ;
		i->element = m->element ;
		m->element = t ;
	}
}

int 
linkedlist_pos (linkedlist_t * l, node_t * begin, node_t * end)
{
	int len = 1 ;
	
	while (begin != end) {
		len += 1 ;
		begin = begin->right ; 
	}
	return len ; 
}

void
_linkedlist_qsort (linkedlist_t * l, int (* cmp_elements)(void * e1, void * e2), node_t * begin, node_t * end)
{
	int leng = linkedlist_pos(l, begin, end) ;

	if (0 >= leng - 1)
		return ;
		
	void * t ;
	node_t * pivot = begin ;
	//int pivot_pos = 0 ;
	node_t * lbound = begin->right ;
	int lbound_pos = 1 ;
	node_t * rbound = end ;
	int rbound_pos = leng - 1 ;// length -1 == end
	
	while (lbound_pos <= rbound_pos){
		while (lbound_pos <= leng - 1 && cmp_elements(lbound->element, pivot->element) <= 0){
			lbound = lbound->right ;
			lbound_pos += 1  ;
		}
			
		while (0 < rbound_pos && cmp_elements(pivot->element, rbound->element) < 0){
			rbound = rbound->left ;
			rbound_pos -= 1 ;
		}
		
		if (lbound_pos <= rbound_pos) {
			t = lbound->element ;
			lbound->element = rbound->element ;
			rbound->element = t ;

			lbound = lbound->right ;
			lbound_pos += 1  ;
			rbound = rbound->left ;
			rbound_pos -= 1 ;
		}
	}
	t = rbound->element ;
	rbound->element = pivot->element ;
	pivot->element = t ;

	if (rbound != end) {
		_linkedlist_qsort(l, cmp_elements, begin, rbound) ;
		_linkedlist_qsort(l, cmp_elements, rbound->right, end) ;
	}
	else {
		_linkedlist_qsort(l, cmp_elements, begin, rbound) ;
	}
}

void
linkedlist_qsort (linkedlist_t * l, int ( cmp_elements)(void * e1, void * e2))
{
	/* TODO */
	_linkedlist_qsort(l, cmp_elements, l->right, l->left) ;
}
