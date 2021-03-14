#include <iostream>
#include <cstring>

using namespace std ;

struct node_{
    char name[11] ; //  name consists of English alphabet (at most 10 char)
    float score ;   //  score(0.0, 100.0) is key.
} ;

typedef struct animal_{
    node_ n[31] ;   // 1 ~ 30  /  1:root / 2-left, 3-right / 
    int heapSize ;  // maxinum heap size = 30
}animal ;


void minHeapify(animal & A, int i) ; 
node_ extractMin(animal & A) ;
void heapDecreaseKey(animal & A, int i, node_ key);
void minHeapInsert(animal & A, node_ key) ;

int main(){

    bool recursive = true ;

    animal A ;
    A.heapSize = 0 ;

    char menu ;
    int index ;
    
    while(recursive){
        printf("\n*********** MENU ****************\n") ;
        printf("I : Insert new element into queue.\n") ;
        printf("D : Delete element with smallest key from queue.\n") ;
        printf("C : Decrease key of element in queue.\n") ;
        printf("P : Print out all elements in queue.\n") ;
        printf("Q : Quit\n\n") ;

        printf("Choose menu: ") ;
        scanf("%c", &menu) ;   

        node_ temp ;

        switch(menu){
            case 'I': case 'i':
                printf("Enter name of element: ") ;
                scanf("%s", temp.name) ;
                printf("Enter key value of element: ") ;
                scanf("%f", &temp.score) ;

                minHeapInsert(A, temp) ;
                printf("New element [%s, %4.1f] is inserted.\n", temp.name, temp.score) ;
                break  ;
                
            case 'D': case 'd':
                temp = extractMin(A) ;
                printf("[%s, %4.1f] is deleted.\n", temp.name, temp.score) ;
                break ;

            case 'C': case 'c':
                printf("Enter index of element: " ) ;
                scanf("%d", &index) ;
                printf("Enter new key value: ") ;
                scanf("%f", &temp.score) ;
                strcpy(temp.name, A.n[index].name) ;
                heapDecreaseKey(A, index, temp) ;
                break ;

            case 'P': case 'p':
                for(int i = 1 ; i <= A.heapSize ; i++)
                    printf("[%s, %4.1f] ", A.n[i].name, A.n[i].score) ;
                printf("\n") ;
                break ;

            case 'Q': case 'q':
                printf("Thank you. Bye!\n") ;
                recursive = false ;     // break loop ;
                break;
            default:
                break ;
        }
        getchar() ;
    }
    return 0 ;
}


void minHeapify(animal & A, int i){
    int l, r, smallest ;
    l = i * 2;
    r = i * 2 + 1 ;

    if(l <= A.heapSize && A.n[l].score < A.n[i].score)
        smallest = l ;
    else
        smallest = i ;

    if(r <= A.heapSize && A.n[r].score < A.n[smallest].score)
        smallest = r ;

    if(smallest != i){
        node_ temp = A.n[i] ;
        A.n[i] = A.n[smallest] ;
        A.n[smallest] = temp ;
        
        minHeapify(A, smallest) ;
    }
}

node_ extractMin(animal & A){
    node_ min ;
    if(A.heapSize < 1){
        printf("heap underflow") ;
        return min ;
    }

    min = A.n[1] ;

    A.n[1] = A.n[A.heapSize] ;
    A.heapSize -= 1 ;
    
    minHeapify(A, 1) ; 

    return min ;
}

void heapDecreaseKey(animal & A, int i, node_ key){
    if(key.score > A.n[i].score){
        printf("new key is smaller than current key") ;
        return ;
    }

    A.n[i] =  key ;

    while (i > 1 && A.n[i/2].score > A.n[i].score){
        node_ temp = A.n[i] ;
        A.n[i] = A.n[i/2] ;
        A.n[i/2] = temp ; 
        i = i/2 ;
    }     
}

void minHeapInsert(animal & A, node_ key){
    A.heapSize += 1 ;
    A.n[A.heapSize].score = 9999 ; //equal infinity 
    heapDecreaseKey(A, A.heapSize, key) ;
}