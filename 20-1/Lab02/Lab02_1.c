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


void
print_stack (stack * st)
{
	int i ;
	for (i = 0 ; i < get_size(st) ; i++) {
		int num ;
		get_element(st, i, &num) ;
		printf("[%d]", num) ;
	}
	printf(".\n") ;
}


int Pow(int num1, int num2){
	int result = 1;

	for(int i=0; i < num2; i++)
		result *= num1 ;

	return result ;
}

int
main ()
{
	stack * st ;
	st = create_stack(100, sizeof(int)) ;
    int boolean = 0 ;

	char tok[8] ;
	do {

		//print_stack(st) ;
        if(boolean != 0)
            break ;

		scanf("%s", tok) ;

		if (tok[0] == ';') 
			break ;

		if (isdigit(tok[0])) {
			int num = atoi(tok) ;
			push(st, &num) ;
		}
		else /* operator */ {
            int k ;
            get_element(st, get_size(st)-1, &k) ;
            if(tok[0] == '/' && k == 0 || tok[0] == '^' && k < 0){
                boolean = -1 ;
                break ;
            }
                
			switch (tok[0]) {
				case '+' : {
					int n1, n2, res ;
					if(pop(st, &n2))
                        boolean += 1 ;
					if(pop(st, &n1))
                        boolean += 1 ;
					res = n1 + n2 ;
					push(st, &res) ;
					break ;
				} 

				case '-' : {
					int n1, n2, res ;
					if(pop(st, &n2))
                        boolean += 1 ;
					if(pop(st, &n1))
                        boolean += 1 ;
					res = n1 - n2 ;
					push(st, &res) ;
					break ;
				}

				case '*' : {
					int n1, n2, res ;
					if(pop(st, &n2))
                        boolean += 1 ;
					if(pop(st, &n1))
                        boolean += 1 ;
					res = n1 * n2 ;
					push(st, &res) ;
					break ;
				}

				case '/' : {
					int n1, n2, res ;
					if(pop(st, &n2))
                        boolean += 1 ;
					if(pop(st, &n1))
                        boolean += 1 ;
					res = n1 / n2 ;
					push(st, &res) ;
					break ;
				}
                case '^' : {
					int n1, n2, res ;
					if(pop(st, &n2))
                        boolean += 1 ;
					if(pop(st, &n1))
                        boolean += 1 ;
					res = Pow(n1, n2);
					push(st, &res) ;
					break ;
				}
                case '~' : {
					int n1, res ;
					if(pop(st, &n1))
                        boolean += 1 ;
                    n1 *= -1 ;
					push(st, &n1) ;
					break ;
				}
                default :
                    boolean += 1 ;
			}
		}
	} while (tok[0] != ';') ;

	int result ;
	
	if(1 < st->top && boolean != -1)
		boolean = 1 ;

	pop(st, &result) ;

    switch(boolean){
    case 0 :
        printf("%d", result) ;
        break ;
    case -1 :
        printf("undefined") ;
        break ;
    default :
        printf("invalid") ;
        break ;
    }
	printf("\n") ;
	delete_stack(st) ;
	return 0 ;
}