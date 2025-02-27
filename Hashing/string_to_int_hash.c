#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CAPACITY 103
 
// Linked List node
struct node {
    // key is string
    char* key;
    // value is also string
    char* value;
    struct node* next;
};
 
// Creating a node
void setNode(struct node* node, char* key, char* value)
{
    node->key = key;
    node->value = value;
    node->next = NULL;
    return;
};

struct hashMap {
 
    // Current number of elements in hashMap
    // and capacity of hashMap
    int numOfElements, capacity;
 
    // hold base address array of linked list
    struct node** arr;
};
 
// like constructor
void initializeHashMap(struct hashMap* mp)
{
 
    // Default capacity in this case
    mp->capacity = MAX_CAPACITY;
    mp->numOfElements = 0;
 
    // array of size = 1
    mp->arr = (struct node**)malloc(sizeof(struct node*)
                                    * mp->capacity);
    return;
}

int hashFunction(struct hashMap* mp, char* key)
{
    int bucketIndex;
    int sum = 0, factor = 31;
    for (int i = 0; i < strlen(key); i++) {
 
        // sum = sum + (ascii value of
        // char * (primeNumber ^ x))...
        // where x = 1, 2, 3....n
        sum = ((sum % mp->capacity)
               + (((int)key[i]) * factor) % mp->capacity)
              % mp->capacity;
 
        // factor = factor * prime
        // number....(prime
        // number) ^ x
        factor = ((factor % __INT16_MAX__)
                  * (31 % __INT16_MAX__))
                 % __INT16_MAX__;
    }
 
    bucketIndex = sum;
    return bucketIndex;
}

void insert(struct hashMap* mp, char* key, char* value)
{
 
    // Getting bucket index for the given
    // key - value pair
    int bucketIndex = hashFunction(mp, key);

    // Creating a new node
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
 
    // Setting value of node
    setNode(newNode, key, value);
 
    // Bucket index is empty....no collision
    if (mp->arr[bucketIndex] == NULL) {
        mp->arr[bucketIndex] = newNode;
    }
 
    // Collision
    else {
        // Adding newNode at head of bucketIndex Linked-list
        newNode->next = mp->arr[bucketIndex];
        mp->arr[bucketIndex] = newNode;
    }
}
 
void delete (struct hashMap* mp, char* key)
{
 
    // Getting bucket index for the
    // given key
    int bucketIndex = hashFunction(mp, key);
 
    struct node* prevNode = NULL;
    struct node* currNode = mp->arr[bucketIndex];
    int flag = 0;
    while (currNode != NULL && !flag) {
 
        // Key is matched at delete this
        // node from linked list
        if (strcmp(key, currNode->key) == 0) {
 
            // Head node
            // deletion
            if (currNode == mp->arr[bucketIndex]) {
                mp->arr[bucketIndex] = currNode->next;
            }
 
            // Last node or middle node
            else {
                prevNode->next = currNode->next;
            }
            free(currNode);
            flag = 1;
        }
        prevNode = currNode;
        currNode = currNode->next;
    }
}
 
char* search(struct hashMap* mp, char* key)
{
 
    // Getting the bucket index
    // for the given key
    
    char* ret_val;
    int bucketIndex = hashFunction(mp, key);
    int found = 0;
    struct node* bucketHead = mp->arr[bucketIndex];
    while (bucketHead != NULL && !found) {
 
        // Key is found in the hashMap
        if (bucketHead->key == key) {
            ret_val = (char*)malloc(strlen(bucketHead->value) + 1);
            ret_val = bucketHead->value;
            found = 1;
        }
        bucketHead = bucketHead->next;
    }
 
    // If no key found in the hashMap
    // equal to the given key
    if(!found){
        ret_val = (char*)malloc(sizeof(char) * 25);
        ret_val = "Oops! No data found.\n";
    }
    return ret_val;
}
 
// Drivers code
int main()
{
 
    // Initialize the value of mp
    struct hashMap* mp
        = (struct hashMap*)malloc(sizeof(struct hashMap));
    initializeHashMap(mp);
 
    insert(mp, "Binod", "Tharu");
    insert(mp, "Raj", "Khanna");
    insert(mp, "Actor", "SRK");
    insert(mp, "School", "ISWK");
    insert(mp, "nonone", "unknown");
 
    printf("%s\n", search(mp, "Actor"));
    printf("%s\n", search(mp, "Binod"));
    printf("%s\n", search(mp, "nonoe"));
  
    // Key is not inserted
    printf("%s\n", search(mp, "Rohan"));
 
    printf("\nAfter deletion : \n");
 
    // Deletion of key
    delete (mp, "Raj");
    // Will display key not found
    printf("%s\n", search(mp, "Raj"));
 
    return 0;
}
