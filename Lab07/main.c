#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#define max_name_size 64

//char s[256] = "1(2(3(4,5),6),7(8),9(10(11),12,13))" ;

tree_t *
read_a_tree(tree_t * t, char *s)
{
	char advisor[max_name_size], advisee[max_name_size] ;

	strcpy(advisor, strtok(s, " ")) ;
	strcpy(advisee, strtok(NULL, " ")) ;

	node_t * parent = tree_search(t, advisor) ;
	node_t * child = tree_search(t, advisee) ;
	
	if(parent == 0x0 && child == 0x0){
 		parent = tree_create_node(advisor) ;
		child = tree_create_node(advisee) ;
		t->sibling = parent ;
		tree_add_child(parent, child) ;
		return t ;
	}
	if(parent == 0x0)
		parent = tree_create_node(advisor) ;
	else if(parent != 0x0 && t != parent && child == 0x0){
		child = tree_create_node(advisee) ;
		tree_add_child(parent, child) ;
		return t ;
	}
	if(child == 0x0)
		child = tree_create_node(advisee) ;
	
	return tree_add_child(parent, child) ;
}

int
main ()
{
	//char s[256] = "1(2(3(4,5),6),7(8),9(10(11),12,13))" ;
	//char newline ;
	//scanf("%255[^\n]", s, &newline) ;
	int N, M ;
	//N (0 < N < 100) and M (0 < M < 10000)
	scanf("%d %d", &N, &M) ;
	
	tree_t * t =  tree_create_node("-") ;
	
	char s[max_name_size*2+1] ;
	char newline ;

	for(int i=0; i<M; i++){
		scanf(" %255[^\n]", s, &newline) ;
		t = read_a_tree(t, s) ;

	}

	tree_print(t) ;

	//printf("height: %d\n", tree_height(t)) ;

	//tree_print(tree_search(t, 3)) ;

	return 0 ;
}
