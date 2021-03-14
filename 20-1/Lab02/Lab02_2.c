#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef 
	struct {
		char * buffer ; // capacity X unit
		int unit ; // size of an element
		int capacity ;
		int top ;
	} 
	stack ;

int 
is_empty (stack * st) ;

int 
is_full (stack * st) ;

stack * 
create_stack (int capacity, int unit) 
{
	stack * st = malloc(sizeof(stack)) ;
	st->capacity = capacity ;
	st->unit = unit ;
	st->top = 0 ;
	st->buffer = calloc(capacity, unit) ;
	return st ;
}

void
delete_stack (stack * st) 
{
	if (st->buffer != 0x0)
		free(st->buffer) ;
	free(st) ;
}

int 
push (stack * st, void * elem)
{
	if (is_full(st))
		return 1 ;

	memcpy(st->buffer + ((st->top) * (st->unit)), elem, st->unit) ;
	st->top += 1 ;

	return 0 ;
}

int
pop (stack * st, void * elem)
{
	if (is_empty(st)) 
		return 1 ;
	
	memcpy(elem, st->buffer + (st->top - 1) * st->unit, st->unit) ;
	st->top -= 1 ;
	return 0;
}

int 
is_empty (stack * st) 
{
	return (st->top == 0) ;
}

int 
is_full (stack * st) 
{
	return (st->top == st->capacity) ;
}

int
get_size (stack * st) 
{
	return st->top ;
}

int
get_element (stack * st, int index, void * elem)
{
	if (st->top <= index)
		return 1 ;

	memcpy(elem, st->buffer + index * st->unit, st->unit) ;
	return 0 ;
}




typedef enum { Value, Molecular, Open } token_type ;

char toke_tt [] = {'V', 'M', '('} ;

typedef struct {
    int value ;
    int mole ;      //molecular weight
	token_type type ;
} token_t ;

void
print_stack (stack * st)
{
	int i ;
	for (i = 0 ; i < get_size(st) ; i++) {
		token_t num ;
		get_element(st, i, &num) ;
		printf("%c: ", toke_tt[num.type]) ;
		if(num.type == Value)
			printf("[%d]", num.value) ;
		else if(num.type == Molecular)
			printf("[%d]", num.mole) ;
	}
	printf(".\n%d\n", get_size(st)) ;
}

int
main () {
	stack * st ;
	token_t tok ;

	st = create_stack(101, sizeof(token_t)) ;

	tok.type = Open ;
	push(st, &tok) ;

	char buf[101] ;

	scanf("%s", buf) ; 

	for(int i = 0; i <= strlen(buf) ; i++){
		print_stack(st) ;

		printf("> read %c.\n", buf[i]) ;

		token_t tok ;
		if (buf[i] == '(') {
			tok.type = Open ;
			push(st, &tok) ;
		}
		else if (isdigit(buf[i])) {
			tok.value = atoi(&buf[i]) ;
			tok.type = Value ;
			push(st, &tok) ;
		}
		else if (buf[i] == 'C' || buf[i] == 'H' || buf[i] == 'O') {
			tok.type = Molecular ;
			switch (buf[i]) {
				case 'C':
					tok.mole = 12 ;
					break ;
				case 'H':
					tok.mole = 1 ;
					break ;
				case 'O':
					tok.mole = 16 ;
					break ;
				} 
			push(st, &tok) ;
		}else if (buf[i] == ')' || i == strlen(buf) ){
            token_t first, next, over, res, top ;
            do{
                res.type = Molecular ;
                pop(st, &first) ;
                if(pop(st, &next)){				//괄호가 추가적으로 들어갔을때 
					push(st, &first) ;
					break ;
				}
                if(first.type == Value && next.type == Molecular){
					res.mole = first.value * next.mole ;
                    printf("\t1\t%d\t%d\t%d\n", first.value, next.mole, res.mole) ;
				}
                else if(first.type == Molecular && next.type == Molecular){
                    res.mole = first.mole + next.mole ;
					printf("\t2\t%d\t%d\t%d\n", first.mole, next.mole, res.mole) ;
				}
                else if(first.type == Molecular && next.type == Value){
                    pop(st, &over) ;
                    res.mole = (next.value * over.mole) + first.mole;
					printf("\t3\t%d\t%d\t%d\t%d\n", first.mole, next.value, over.mole, res.mole) ;
                }
                pop(st, &top) ;
                if(top.type != Open)
                    push(st, &top) ;
				
                push(st, &res) ;
            }while(top.type != Open ) ; 
		}
	}
	
	token_t result ;
	pop(st, &result) ;
	printf("%d\n", result.mole) ;

	delete_stack(st) ;

    return 0 ;
}
