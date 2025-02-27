#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define HASH_SIZE 1003

typedef enum { FAILURE, SUCCESS } status_code;

typedef struct hash_node_tag {
    int data;
    int frequency;
    struct hash_node_tag* next;
} hash_node;

hash_node* create_hash_node(int input_data) {
    hash_node* node_pointer = (hash_node*) malloc(sizeof(hash_node));
    if (node_pointer == NULL) {  // Check for malloc failure
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    node_pointer->data = input_data;
    node_pointer->frequency = 1;
    node_pointer->next = NULL;
    return node_pointer;
}

int hash_function(int data) {
    int hash_key = data % HASH_SIZE;
    return hash_key;
}

status_code initialise_hashtable(hash_node* hashtable[]) {
    for (int index = 0; index < HASH_SIZE; index++) {
        hashtable[index] = NULL;
    }
    return SUCCESS;
} 

status_code add_to_hashtable(int input_data, hash_node* hashtable[]) {
    status_code done = FAILURE;
    bool added = false;
    // Corrected: use 'input_data' (the function parameter) instead of undefined 'data'
    int hash_key = hash_function(input_data);

    if (hashtable[hash_key]) {
        hash_node* current_pointer = hashtable[hash_key];
        hash_node* tail_pointer = NULL;
        while (current_pointer && !added) {
            if (current_pointer->data == input_data) {
                current_pointer->frequency += 1;
                added = true;
                done = SUCCESS;
            } else {
                tail_pointer = current_pointer;
                current_pointer = current_pointer->next;
            }
        }
        if (!added) {
            hash_node* node_pointer = create_hash_node(input_data);
            tail_pointer->next = node_pointer;
            added = true;
            done = SUCCESS;
        }
    } else { // Slot is empty
        hash_node* new_node_pointer = create_hash_node(input_data);
        hashtable[hash_key] = new_node_pointer;
        done = SUCCESS;
    }
    return done;
}

bool search_in_hashtable(hash_node* hashtable[], int input_data, int* frequency) {
    bool found = false;
    // Corrected: use 'input_data' instead of undefined 'data'
    int key_index = hash_function(input_data);

    if (hashtable[key_index]) {
        hash_node* current_node_pointer = hashtable[key_index];
        while (current_node_pointer && !found) {
            if (current_node_pointer->data == input_data) {
                *frequency = current_node_pointer->frequency;
                found = true; // Set found to true rather than toggling it
            } else {
                current_node_pointer = current_node_pointer->next;
            }
        }
    }
    if (!found) {
        *frequency = 0;
    }
    return found;
}
