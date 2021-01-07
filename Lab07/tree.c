#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tree.h"

node_t * 
tree_create_node (char data[64]) 
{
	node_t * root ;
	root = (node_t *) malloc(sizeof(node_t)) ;
	strcpy(root->data, data) ;
	root->child = 0x0 ;
	root->sibling = 0x0 ; 
	return root ;
}

node_t *
tree_add_child (node_t * parent, node_t * child)
{
	if (parent->child == 0x0) {
		parent->child = child ;
	}
	else {
		node_t * curr ;
		for (curr = parent->child ; curr->sibling != 0x0 ; curr = curr->sibling) ;
		// curr->sibling == 0x0  
		curr->sibling = child ;

	}
	return parent ;
}

int
tree_height(tree_t * t) 
{
	int max = 0 ; 
	node_t * c ;
	for (c = t->child ; c != 0x0 ; c = c->sibling) {
		int h = tree_height(c) ;
		max = (max < h) ? h : max ;
	}
	return max + 1 ;
}

node_t *
tree_search (node_t * t, char key[64])
{
	if(!strcmp(t->data, "-"))
		return tree_create_node(key) ;
	else if (!strcmp(t->data, key))
		return t ;

	for (node_t * i = t->child ; i != 0x0 ; i = i->sibling) {
		node_t * r ;
		r = tree_search(i, key) ;
		if (r != 0x0) 
			return r ;		
	}

	return 0x0 ;
}

void
_tree_print (node_t * t, int level)
{
	for (int i = 0 ; i < level ; i++){
		if(i == level -1)
			printf("+--") ;
		else
			printf("   ") ;
	}
	printf("%s\n", t->data) ;
	
	node_t * curr ;
	for (curr = t->child ; curr != 0x0 ; curr = curr->sibling) 
		_tree_print(curr, level + 1) ;

	if(level==0 && t->sibling != 0x0){
		printf("%s\n", t->sibling->data) ;
		for (curr = t->sibling->child ; curr != 0x0 ; curr = curr->sibling) 
			_tree_print(curr, level + 1) ;
	}		
}

void
tree_print (tree_t * t)
{
	_tree_print(t, 0) ;
}
