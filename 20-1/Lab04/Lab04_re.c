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
    int s_i = 0, s_p = 0 ;
    char bracket[26] = {0x0} ;
	int answer[5] = {0} ;

	FILE * fp = fopen("input", "r") ;

		fscanf(fp, "%s", pattern) ;
		for(int i= 0; i<5; i++)
			fscanf(fp, "%s", input[i]) ;

	fclose(fp) ;
/*/
	scanf("%s", pattern) ;
	for(int i= 0; i<5; i++)
		scanf("%s", input[i]) ;
*/
    int pos = 0 ;
    while (pos < 5)
    {
		printf("\npos = %d\n", pos+1) ;
        linkedlist_t * s = linkedlist_alloc(sizeof(int)) ;
        linkedlist_t * s_post = linkedlist_alloc(sizeof(int)) ;

        linkedlist_insert_last(s, &s_i) ;

		int i = 0 ;
        while(linkedlist_length(s) != 0 || linkedlist_length(s_post) != 0 ){


        	printf("\t%d\t%d", linkedlist_length(s), linkedlist_length(s_post)) ;
			
			

            if(linkedlist_length(s) == 0){
				while(!linkedlist_remove_first(s_post, &s_i))
					linkedlist_insert_last(s, &s_i) ;
				i += 1 ;
				memset(bracket, 0, sizeof(bracket)) ;
			}
            printf("\t%d\t%d", linkedlist_length(s), linkedlist_length(s_post)) ;
			printf("\t%c\t%d\t%d\t%c\t%ld\t%s\n", pattern[i], i, s_i, input[pos][s_i], strlen(bracket), bracket) ;
			
			if(i == strlen(pattern) && s_i == strlen(input[pos])){
							answer[pos] = 1 ;
							break ;
						}

            if(!linkedlist_remove_first(s, &s_i))
				s_p = s_i + 1 ;


			char temp = 0x0 ;
			if(pattern[i] == '['  || 0 < strlen(bracket)){
				while(pattern[i] != ']'){
					i += 1 ;
					if(pattern[i] != ']'){
						temp = pattern[i] ;
						strcat(bracket, &temp) ;
					}
				}
				for(int j=0; j<strlen(bracket); j++)
					if(bracket[j] == input[pos][s_i])
						linkedlist_insert_last(s_post, &s_p) ;
			}
          	else if('a' <= pattern[i] && pattern[i] <= 'z'){
                if(pattern[i] == input[pos][s_i])
				  linkedlist_insert_last(s_post, &s_p) ;
			}
            else if(pattern[i] == '*'){
				do{
					for(int j=s_i; j<=strlen(input[pos]); j++){
						linkedlist_insert_last(s_post, &j) ;
					}
				}while(!linkedlist_remove_last(s, &s_i)) ;
            }
            else if(pattern[i] == '!'){
                linkedlist_insert_last(s_post, &s_i) ;
                linkedlist_insert_last(s_post, &s_p) ;           
            }
            else if(pattern[i] == '?'){
                linkedlist_insert_last(s_post, &s_p) ; 
            }
        }
		
		s_i = 0 ;

		linkedlist_free(s) ;
		linkedlist_free(s_post) ;
		memset(bracket, 0, sizeof(bracket)) ;

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