/*
Implementation of Sparse Matrices. 

Implementation - 1
Array of rows and cols consisting of pointers to Nodes. 
*/

#include <stdio.h>
#include <stdlib.h>

#define NUM_ROWS 100
#define NUM_COLS 75

typedef struct SM_Node_tag{
    float data;
    int row;
    int col;
    struct SM_Node_tag* right;
    struct SM_Node_tag* down;
}SM_Node;

typedef struct SM_tag{
    SM_Node* rows[NUM_ROWS];
    SM_Node* cols[NUM_COLS];
}SparseMatrix;

SM_Node* createNode(float data, int row, int col){
    SM_Node* newNode = (SM_Node*)malloc(sizeof(SM_Node));
    if(!newNode){
        printf("Memory Allocation Failed\n");
    }
    else{
        newNode -> data = data;
        newNode -> row = row;
        newNode -> col = col;
        newNode -> right = NULL;
        newNode -> down = NULL;
    }
    return newNode;
}

SparseMatrix* createMatrix(){
    SparseMatrix* matrixptr = (SparseMatrix*)malloc(sizeof(SparseMatrix));
    if(!matrixptr){
        printf("Memory Allocation Failed\n");
    }
    return matrixptr;
}

void insertValue(float data, int row, int col, SparseMatrix* matrixptr){
    SM_Node *prev_row, *row_ptr, *prev_col, *col_ptr;
    row_ptr = matrixptr -> rows[row];
    col_ptr = matrixptr -> cols[col];
    while(row_ptr && row_ptr -> col < col){
        prev_row = row_ptr;
        row_ptr = row_ptr -> right;
    }
    while(col_ptr && col_ptr -> row < row){
        prev_col = col_ptr;
        col_ptr = col_ptr -> down;
    }
    if(row_ptr == col_ptr && row_ptr && col_ptr){
        // In case node already exists
        if(!data){
            if(row_ptr == matrixptr -> rows[row]){
                matrixptr -> rows[row] = row_ptr -> right;
            }
            else{
                prev_row -> right = row_ptr -> right;
            }
            if(col_ptr == matrixptr -> cols[col]){
                matrixptr -> cols[col] = col_ptr -> down;
            }
            else{
                prev_col -> down = col_ptr -> down;
            }
            free(row_ptr);
            row_ptr = NULL;
            col_ptr = NULL;
        }
        else{
            row_ptr -> data = data;
        }
    }
    else if(data){
        SM_Node* newNode = createNode(data,row,col);
        if(newNode){
            if(row_ptr == matrixptr -> rows[row]){
                matrixptr -> rows[row] = newNode;
            }
            else{
                prev_row -> right = newNode;
            }
            newNode -> right = row_ptr;
            if(col_ptr == matrixptr -> cols[col]){
                matrixptr -> cols[col] = newNode;
            }
            else{
                prev_col -> down = newNode;
            }
            newNode -> down = col_ptr;
        }
    }
}

void displayMatrix(SparseMatrix* matrixptr){
    if(matrixptr){
        printf("Matrix Entries :- \n");
        for(int i=0 ; i<NUM_ROWS ; i++){
            SM_Node* row_ptr = matrixptr -> rows[i];
            for(int j=0 ; j<NUM_COLS ; j++){
                if(row_ptr && row_ptr -> col == j){
                    printf("%f ", row_ptr -> data);
                    row_ptr = row_ptr -> right;
                }
                else{
                    printf("%f ", 0.0);
                }
            }
            printf("\n");
        }
    }
}

