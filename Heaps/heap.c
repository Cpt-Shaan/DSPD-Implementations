/*
Implementing a Heap in C
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 50

typedef struct Heap{
    int top;
    int arr[MAX_SIZE];
}Heap;

Heap* createMaxHeap(){
    Heap* maxHeap = (Heap*)malloc(sizeof(Heap));
    maxHeap -> top = MAX_SIZE;
    return maxHeap;
}

int left(int i, int offset){
    return (2*(i - offset) + 1 + offset);
}

int right(int i, int offset){
    return (2*(i - offset) + 2 + offset);
}

int parent(int i){
    return (i-1)/2;
}

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void maxHeapify(Heap* maxHeap, int i, int n){
    int largest;
    int l = left(i,maxHeap -> top), r = right(i, maxHeap -> top), size = n;
    if(l < size && maxHeap -> arr[i] < maxHeap -> arr[l]){
        largest = l;
    }
    else{
        largest = i;
    }
    if(r < size && maxHeap -> arr[largest] < maxHeap -> arr[r]){
        largest = r;
    }
    if(largest != i){
        swap(&maxHeap -> arr[largest],&maxHeap -> arr[i]);
        maxHeapify(maxHeap,largest,n);
    }
}

void push(Heap* maxHeap, int val){
    if(maxHeap -> top){
        (maxHeap -> top)--;
        maxHeap -> arr[maxHeap -> top] = val;
        maxHeapify(maxHeap,maxHeap -> top,MAX_SIZE);
    }
    else{
        printf("Heap is full\n");
    }
}

int top(Heap* maxHeap){
    int ret_val = 0;
    if(maxHeap -> top != MAX_SIZE) ret_val = (maxHeap -> arr[maxHeap -> top]);
    return ret_val;
}

void pop(Heap* maxHeap){
    (maxHeap -> top)++;
    maxHeapify(maxHeap,maxHeap -> top,MAX_SIZE);
}

int sizeHeap(Heap* maxHeap){
    return (MAX_SIZE - (maxHeap -> top));
}

int main(){
    Heap* maxHeap = createMaxHeap();
    int done = 0;
    while(!done){
        printf("Enter the choice: ");
        printf("\n1. Push\n2. Pop\n3. Top\n4. Size\n5. Exit\n");
        int choice,val;
        printf("Enter here (1/2/3): ");
        scanf("%d", &choice);
        switch(choice){
            case 1:
                printf("Enter the value to push: ");
                scanf("%d", &val);
                push(maxHeap,val);
                break;
            case 2:
                pop(maxHeap);
                break;
            case 3:
                val = top(maxHeap);
                printf("The value at top is : %d\n", val);
                break;
            case 4:
                printf("The size of the heap is %d\n", sizeHeap(maxHeap));
                break;
            case 5:
                done = 1;
                break;
            default:
                printf("Wrong Choice Entered\n");
                break;
        }
    }
    return 0;
}

