#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef 
	struct {
		char * buffer ; // capacity X unit
		int unit ; // size of an element
		int capacity ;
		int top ;
	} 
	stack_t ;

int 
is_empty (stack_t * stack) ;

int 
is_full (stack_t * stack) ;


stack_t * 
create_stack (int capacity, int unit) 
{
	stack_t * stack = (stack_t *) malloc(sizeof(stack_t)) ;
	stack->capacity = capacity ;
	stack->unit = unit ;
	stack->top = 0 ;

	stack->buffer = (char *) calloc(capacity, unit) ;
	
	return stack ;
}

void
delete_stack (stack_t * stack) 
{
	free(stack->buffer) ;
	free(stack) ;
}

int 
push (stack_t * stack, void * elem)
{
	if (is_full(stack))
		return 1 ;
	
	memcpy((void *) stack->buffer + stack->top * stack->unit, elem, stack->unit) ;
	stack->top += 1 ;
	return 0 ;
}

int
pop (stack_t * stack, void * elem)
{
	if (is_empty(stack)) 
		return 1 ;
	
	memcpy(elem, stack->buffer + (stack->top - 1) * stack->unit, stack->unit) ;
	stack->top -= 1 ;
	return 0;
}

int 
is_empty (stack_t * stack) 
{
	return (stack->top == 0) ;
}

int 
is_full (stack_t * stack) 
{
	return (stack->top == stack->capacity) ;
}

int
get_size (stack_t * stack) 
{
	return stack->top ;
}

int
get_element (stack_t * stack, int index, void * elem)
{
	if (stack->top <= index)
		return 1 ;

	memcpy(elem, stack->buffer + index * stack->unit, stack->unit) ;
	return 0 ;
}



int
main () 
{
	stack_t * st ;

    int N, C ;

	scanf("%d%d", &N, &C) ;

	int trainNum[N] ;

	st = create_stack(C, sizeof(int)) ;
	
	for(int i = 0; i < N; i++){

		scanf("%d", &trainNum[i]) ;

	}
	
	int top = 0, boolean = 0 ;	//0 is NonErroe
	int num = 1; 
	int ti = num-1 ;		//trainIndex

	while(ti < N){

		if(get_size(st) != 0)			//top
			get_element(st, get_size(st)-1, &top) ;
		else
			top = 0 ;

		while(num < trainNum[ti]){
			boolean += push(st, &num) ;
			num += 1 ;
		}
		if(num == trainNum[ti]) ;
		else if(trainNum[ti] == top){
			pop(st, &top)  ;
			ti += 1 ;
			continue ;
		}
		else if(num > trainNum[ti] && trainNum[ti] < top)
			boolean += 1 ;

		if(num < N)
			num += 1 ;
		if(ti <= num -1)
			ti += 1 ;
	}


	delete_stack(st) ;


	switch (boolean){
	case 0 :
		printf("true") ;
		break;
	default :
		printf("false") ;
		break;
	}

	return 0;
}