/*
Heapsort in C using maxHeaps
Implemented on arrays, visualised as binary-trees

Property of maxHeaps - element at root > both its children, and the property is recursively true. 
*/

#include <stdio.h>

#define MAX_SIZE 100

int left(int i){
    return (2*i + 1);
}

int right(int i){
    return (2*i + 2);
}

int parent(int i){
    return (i-1)/2;
}

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void maxHeapify(int A[], int n, int i){
    int l = left(i), r = right(i), largest, size = n;
    if((l < size) && (A[i] < A[l])){
        largest = l;
    }
    else{
        largest = i;
    }
    if((r < size) && (A[largest] < A[r])){
        largest = r;
    }
    if(largest != i){
        swap(&A[i],&A[largest]);
        maxHeapify(A,n,largest);
    }
}

void buildMaxHeap(int A[], int n){
    int i;
    int t = (n-1)/2;    // Start from the last non-leaf node
    for(i=t ; i>=0 ; i--){
        maxHeapify(A,n,i);
    }
}

void heapSort(int A[], int n){
    int i;
    buildMaxHeap(A,n);
    for(i=n-1; i>=0 ; i--){
        swap(&A[i],&A[0]);  // Always put max element (i.e the one at the top of heap) to the end
        n--;    // reduce size to not include the max element in next iteration
        maxHeapify(A,n,0);
    }
}

int main(){
    int n;
    int arr[MAX_SIZE];
    printf("Enter the no of elements: ");
    scanf("%d", &n);
    printf("Enter the array elements : ");
    for(int i=0 ; i<n ; i++){
        scanf("%d", &arr[i]);
    }
    heapSort(arr,n);
    printf("Sorted Array : ");
    for(int i=0 ; i<n ; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}