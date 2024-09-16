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


/*
Open/close parens [parentheses]: ()
Open/close curly braces: {}
Open/close [square] brackets: []
< Less-Than Sign
> Graeter-Than Sign

*/
typedef enum{
	OPEN_PARENS, CLOSE_PARENS, OPEN_CURLY, CLOSE_CURLY, OPEN_SQUARE, CLOSE_SQURE, OPEN_THAN, CLOSE_THAN
} bracket ;

char brackets[] = {
	'(', ')', '{', '}', '[', ']','<', '>' };

#define length 100

int
main () 
{
	stack_t * st ;
	
	char input[length] ;

	scanf("%s", &input) ;

	st = create_stack(strlen(input), sizeof(char)) ;

	char present ;

	int max = 0, saveMax = 0 ;

	int boolean = 0 ; 	//0 is NonErroe
	
	char top;

	bracket b ;
	

	for(int i = 0; i < strlen(input) ; i++){
		
		present = input[i] ;

		if(get_size(st) != 0)			//top
			get_element(st, get_size(st)-1, &top) ;
		else
			top = 'N' ;									// N is a nothing

		switch (present){			//0~3 OPEN	4~7	CLOSE
		case '(' : 			b = OPEN_PARENS ; 			break;
		case ')' : 			b = CLOSE_PARENS ; 			break;
		case '{' : 			b = OPEN_CURLY ; 			break;
		case '}' : 			b = CLOSE_CURLY ; 			break;
		case '[' : 			b = OPEN_SQUARE ; 			break;
		case ']' : 			b = CLOSE_SQURE ; 			break;
		case '<' :			b = OPEN_THAN ;				break;
		case '>' : 			b = CLOSE_THAN ; 			break;
		}


		if(top == 'N' || b%2 == 0){
			push(st, &present) ;
			max += 1 ;
			if(saveMax < max)
				saveMax = max ;
			present = 'N' ;
		}
		else if(top == brackets[b-1]){
			pop(st, &top)  ;
			if(saveMax < max)
				saveMax = max ;
			max -= 1 ;
			present = 'N' ;
		}
		
		if(present != 'N')
			boolean = 1 ;
	}


	delete_stack(st) ;


	switch (boolean){
	case 0 :
		printf("%d", saveMax) ;
		break;
	default :
		printf("invalid") ;
		break;
	}  

	return 0;
}