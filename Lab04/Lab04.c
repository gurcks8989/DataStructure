#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct node {
	void * element ;
	struct node * left ; 
	struct node * right ;
} ;

typedef struct node node_t ;
typedef struct node linkedlist_t ;

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
linkedlist_free (linkedlist_t * l)
{
	node_t * curr ;
	node_t * next ;

	curr = l->right ;
	while (curr != l) {
		next = curr->right ;
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


int 
main () 
{
	char pattern[128] = {0x0} ;
	char input[5][128] = {0x0} ;
	char present = 0x0 ;
	char matched[128] = {0x0} ;
	char matched_next[128] = {0x0} ;
	int answer[5] = {1, 1, 1, 1, 1} ;
	char temp[128] = {0x0} ;

	FILE * fp = fopen("input", "r") ;

		fscanf(fp, "%s", pattern) ;
		for(int i= 0; i<5; i++)
			fscanf(fp, "%s", input[i]) ;

	fclose(fp) ;
/*
	scanf("%s", pattern) ;
	for(int i= 0; i<5; i++)
		scanf("%s", input[i]) ;
*/
	int pos = 0 ;
	while(pos < 5){	
	//	printf("pos = %d\n", pos+1) ;

		linkedlist_t * pattern_queue = linkedlist_alloc(sizeof(char)) ;
		linkedlist_t * present_queue  = linkedlist_alloc(sizeof(char)) ;
		linkedlist_t * matched_queue = linkedlist_alloc(sizeof(char) * 128) ;
		linkedlist_t * matched_next_queue = linkedlist_alloc(sizeof(char) * 128) ;

		for(int i=0; i< strlen(pattern); i++)
			linkedlist_insert_last(pattern_queue, &pattern[i]) ;

		linkedlist_insert_last(matched_queue, input[pos]) ;
		
		char pattern_i ;
		char bracket[26] = {0x0};
		linkedlist_remove_first(pattern_queue, &pattern_i) ;
		while(linkedlist_length(matched_queue) != 0 || linkedlist_length(matched_next_queue) != 0){
			//printf("\n\t%d\t%d", linkedlist_length(matched_queue), linkedlist_length(matched_next_queue)) ;
			if(linkedlist_length(matched_queue) == 0){
				while(!linkedlist_remove_first(matched_next_queue, matched_next))
					linkedlist_insert_last(matched_queue, matched_next) ;
				back :
				if(linkedlist_remove_first(pattern_queue, &pattern_i))
					break ;
				memset(bracket, 0, sizeof(bracket)) ;
			}
			//printf("\t%d\t%d\t", linkedlist_length(matched_queue), linkedlist_length(matched_next_queue)) ;
			linkedlist_remove_first(matched_queue, matched) ;
			
			for(int i=0; i< strlen(matched); i++)
				linkedlist_insert_last(present_queue, &matched[i]) ;
				
			//printf("*%s*\t", matched) ;
			memset(temp, 0, sizeof(temp)) ;
			memset(matched, 0, sizeof(matched)) ;
		//	printf("|%c ", pattern_i) ;
			if('a' <= pattern_i && pattern_i <= 'z'){
				linkedlist_remove_first(present_queue, &present) ;
				//printf("=%c|", present) ;
				if(pattern_i == present){		//matching
					while(linkedlist_length(present_queue) != 0){		//!empty
						linkedlist_remove_first(present_queue, temp) ;
						strcat(matched, temp) ;
					}
					if(strcmp(matched, ""))
						linkedlist_insert_last(matched_next_queue, matched) ;	//push
					else{
						linkedlist_insert_last(matched_next_queue, " ") ;
						if(linkedlist_length(pattern_queue) == 0){
							present = ' ' ;
						//	printf("*%c*", present) ;
							goto back ;
						}
					}
				}
				linkedlist_free(present_queue) ;
				present_queue  = linkedlist_alloc(sizeof(char)) ;		
			}
			else if(pattern_i == '[' || 0 < strlen(bracket)){
				while(pattern_i != ']'){
					linkedlist_remove_first(pattern_queue, &pattern_i) ;
					if(pattern_i != ']')
						strcat(bracket, &pattern_i) ;
				}
				//printf("%s", bracket) ;
				linkedlist_remove_first(present_queue, &present) ;
				if(present == ' '){
					present = 0x0 ;
					continue ;
				}
				for(int i=0; i<strlen(bracket); i++)
					if(bracket[i] == present){		//matching
						if(linkedlist_length(present_queue) != 0)		//!empty
							for(int j=0; j<linkedlist_length(present_queue); j++){
								linkedlist_get(present_queue, j, temp) ;
								strcat(matched, temp) ;
							}
					//	printf("*%s*", matched) ;
						if(strcmp(matched, ""))
							linkedlist_insert_last(matched_next_queue, matched) ;	//push
						else{
							linkedlist_insert_last(matched_next_queue, " ") ;
							if(linkedlist_length(pattern_queue) == 0){
								present = ' ' ;
							//	printf("*%c*", present) ;
								goto back ;
							}
						}
					}
				linkedlist_free(present_queue) ;
				present_queue  = linkedlist_alloc(sizeof(char)) ;
			}
			else{
				int count = 0 ;
				switch (pattern_i){
					case '*':
						linkedlist_insert_last(matched_next_queue, " ") ;		//empty ""
						while(!linkedlist_remove_last(present_queue, &present)){
							strcpy(temp, matched) ;
							memset(matched, 0, sizeof(matched)) ;
							strncpy(matched, &present, 1) ;
							strcat(matched, temp) ;
						//	printf("\t%s", matched) ;
							linkedlist_insert_last(matched_next_queue, matched) ;
						}
					//	printf("\n") ;
						if(linkedlist_length(pattern_queue) == 0){
								present = ' ' ;
								//printf("*%c*", present) ;
								goto back ;
							}
						break;
					case '!':
						count = linkedlist_length(present_queue) ;
						while(!linkedlist_remove_last(present_queue, &present)){
							strcpy(temp, matched) ;
							memset(matched, 0, sizeof(matched)) ;
							strncpy(matched, &present, 1) ;
							strcat(matched, temp) ;
							if(strlen(matched) >= count-1){
							//	printf("\t%s", matched) ;
								linkedlist_insert_last(matched_next_queue, matched) ;
							}
						}
						if(count == 1 && linkedlist_length(pattern_queue) == 0){
							present = ' ' ;
						//	printf("*%c*", present) ;
							goto back ;
						}
						//printf("\n") ;
						break ;
					case '?':
						linkedlist_remove_first(present_queue, &present) ;

						while(!linkedlist_remove_first(present_queue, temp))
							strcat(matched, temp) ;
					//	printf("*%s*", matched) ;
						if(strcmp(matched, ""))
							linkedlist_insert_last(matched_next_queue, matched) ;	//push
						else{
							linkedlist_insert_last(matched_next_queue, " ") ;
							if(linkedlist_length(pattern_queue) == 0){	
								present = ' ' ;
						//		printf("*%c*", present) ;
								goto back ;
							}
						}
						break;
				}
			
			}
		}
		char c1, c2 ;
		linkedlist_get(pattern_queue, 0, &c1) ;
		linkedlist_get(pattern_queue, 1, &c2) ;

	//	printf("\n%d\t*%c*\t*%c*\t*%c*\n", linkedlist_length(pattern_queue), c1, c2, present) ;
		
		if(linkedlist_length(pattern_queue) != 0 || present != ' ')
			answer[pos] = 0 ;

		linkedlist_free(matched_queue) ;
		linkedlist_free(matched_next_queue) ;
		linkedlist_free(pattern_queue) ;
		linkedlist_free(present_queue) ;

		pos += 1 ;
	}
  
	for(int i=0; i<5; i++){
		if(answer[i])		// 1
			printf("true") ;
		else				// 0
			printf("false") ;
		printf("\n") ;
        }
  	return 0 ;

}
