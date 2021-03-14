#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef 
	struct {
		void * buffer ;
		int unit ;
		int capacity ;
		int front ;
		int rear ;
		int full ;
	} 
	queue ;

	
int 
is_empty (queue * que) ;

int 
is_full (queue * que) ;

queue * 
create_queue (int capacity, int unit) 
{
	queue * que = malloc(sizeof(queue)) ;
	que->capacity = capacity ;
	que->unit = unit ;
	que->buffer = calloc(capacity, unit) ;
	que->front = 0 ;
	que->rear = 0 ;
	que->full = 0 ;
	return que ;
}

void
delete_queue (queue * que) 
{
	if (que->buffer != 0x0)
		free(que->buffer) ;
	free(que) ;
}

int 
enqueue (queue * que, void * elem)
{
	if (is_full(que))
		return 1 ;

	memcpy(que->buffer + ((que->rear) * (que->unit)), elem, que->unit) ;
	que->rear = (que->rear + 1) % que->capacity ;

	if (que->rear == que->front)
		que->full = 1 ;

	return 0 ;
}

int
dequeue (queue * que, void * elem)
{
	if (is_empty(que)) 
		return 1 ;
	
	memcpy(elem, que->buffer + que->front * que->unit, que->unit) ;
	que->front = (que->front + 1) % que->capacity ;
	if (que->front == que->rear)
		que->full = 0 ;

	return 0;
}

int 
is_empty (queue * que) 
{
	return (que->front == que->rear) && (que->full == 0) ;
}

int 
is_full (queue * que) 
{
	return que->full ;
}

void
print_queue (queue * que, void (* print_element)(void * elem)) 
{
	int i ;
	if (que->front == que->rear && que->full == 0)
		return ;

	for (i = que->front ; i != que->rear ; i = (i + 1) % (que->capacity)) {
		printf("[") ;
		print_element(que->buffer + i * que->unit) ;
		printf("] ") ;
	}
	printf("\n") ;
}


void
print_int (void * p)
{
	int * elem = (int *) p ; 
	printf("%d", *elem) ;
}


typedef struct {
	int x ;
	int y ;
} land ;

const int d[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}} ;



int W, H ;

int
main () 
{
	queue * que ;
	land curr ;

	scanf("%d %d", &W, &H) ;

	que = create_queue(W*H, sizeof(land)) ;

	int count = 0, size = 0, max = 0, min = H*W, x_pos = 0, y_pos = 0;

	int visited[H][W] ;

	for(int j=0; j < H ; j++){
		for(int i=0; i < W; i++){
			scanf("%d", &visited[j][i]) ;
			
		}
	}
		
	curr.x = 0 ;
	curr.y = 0 ;

	while(y_pos < H){
		
		if (visited[curr.y][curr.x]){
			visited[curr.y][curr.x] = 0 ;
			size += 1 ;
			enqueue(que, &curr) ;
		}

		while(!is_empty(que)){
			dequeue(que, &curr) ;
			for (int i = 0 ; i < 4 ; i++) {
				land next ;
				next.x = curr.x + d[i][0] ;
				next.y = curr.y + d[i][1] ;

				if (0 <= next.x && next.x < W && 0 <= next.y && next.y < H && visited[next.y][next.x]) {
					size += 1;
					//printf("\t%d\t%d\t%d\n", next.x, next.y, next.m) ;
					visited[next.y][next.x] = 0 ;
					enqueue(que, &next) ;
				}
			}			
			if(is_empty(que)){
				if(max < size)
					max = size ;
				if(size < min)
					min = size ;
				count += 1 ;
			}
		}

		if(x_pos < W-1){
			x_pos += 1 ;
		}
		else{
			x_pos = 0 ;
			y_pos += 1 ;
		}

		curr.x = x_pos ;
		curr.y = y_pos ;
		size = 0 ;
	}

	print_queue(que, print_int) ;
	printf("%d %d %d\n", count, min, max) ;

	delete_queue(que) ;

	return 0 ;
}