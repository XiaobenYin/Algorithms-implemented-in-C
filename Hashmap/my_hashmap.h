// =================== Support Code =================
// Hashmap 
//
// - Implement each of the functions to create a working hashmap.
// - Do not change any of the function declarations
//   - (i.e. hashmap_t* hashmap_create() should not have additional arguments)
// - You should not have any 'printf' statements in your functions other 
//   than functions that explicitly ask for printf output. 
//   - (You may consider using these printf statements to debug,
//     but they should be removed from your final version)
// - You may add any helper functions that you think you need
//   (if any, or otherwise for debugging)
// ==================================================
#ifndef MY_HASHMAP_T
#define MY_HASHMAP_T

#include <stdlib.h>
#include <string.h>


// An entry consisting of a key-value pair.
// This is specifically for a (char*, char*) key-value pair
typedef struct pair {
    char* key;
    char* value;
} pair_t;

// Each node holds a key and a value
typedef struct node {
    pair_t* kv; // key/value pair
    struct node* next;
} node_t;


// Simple hash function that will put a key into a bucket
// You should not modify this
int stringHash(char* myKey, int numberOfBuckets){
    return strlen(myKey) % numberOfBuckets;
}

// Create a function prototype to a function that takes
// in a char* and an int.
typedef int(*hashFunctionPointer)(char*, int); 

// Chained implementation of a hashmap
typedef struct hashmap {
    unsigned int buckets;   // i.e. size of the hashmap
    node_t** arrayOfLists;  // An array of linked lists for our buckets
                            // Read another way -- an array of node_t*

    // A function pointer to a hash function
    // The hash_function must take in a 'char*' as a key, and have a
    // second parameter specifying the number of buckets.
    hashFunctionPointer hashFunction;
} hashmap_t;

// Creates a new hashmap
// Allocates memory for a new hashmap.
// Initializes the capacity(i.e. number of buckets)
// The algorithm is:
//  - allocate memory for our hashmap
//  - set the number of buckets
//  - initialize our array of lists for each bucket
//  - setup our hash function to point to our stringHash function
//  - return new map that we have created
hashmap_t* hashmap_create(unsigned int _buckets) {
    hashmap_t* newHashMap = (hashmap_t*)malloc(sizeof(hashmap_t));
    newHashMap->buckets = _buckets;
    newHashMap->arrayOfLists = (node_t**)malloc(sizeof(node_t*) * _buckets);

    for (int i = 0; i < _buckets; i++)
    {
        newHashMap->arrayOfLists[i] = NULL;
    }
    
    newHashMap->hashFunction = stringHash;
    return newHashMap;
}

// helper function to free node
void freeNode(node_t* node) {
    free(node->kv->value);
    free(node->kv->key);
    free(node->kv);
    free(node);
}

// Frees a hashmap
// Responsibility to free a hashmap that has been previously allocated.
// Must also free all of the chains in the hashmap
// This function should run in O(n) time
void hashmap_delete(hashmap_t* _hashmap) {
    if (_hashmap == NULL)
    {
        return;
    }

    for (int i = 0; i < _hashmap->buckets; i++)
    {
        node_t* currentNode = _hashmap->arrayOfLists[i];
        while (currentNode != NULL)
        {
            node_t* temp = currentNode;
	    currentNode = currentNode->next;
            freeNode(temp);
        }
    }
    free(_hashmap->arrayOfLists);
    free(_hashmap);
}

// Returns a boolean value if a key has been put into
// the hashmap
//  - Returns a '1' if a key exists already
//  - Returns a '0' if the key does not exist
//  - Returns a '-9999' if the hashmap is NULL
// The algorithm is:
//  - Call the _hashmap's hash function on the key
//  - Search that bucket to see if the key exists.
// This function should run in average-case constant time
int hashmap_hasKey(hashmap_t* _hashmap, char* key) {
	// TODO: Implement me!!
    if (_hashmap == NULL)
    {
        return -9999;
    }
    unsigned int bucket = _hashmap->hashFunction(key, _hashmap->buckets);

    node_t* iter = _hashmap->arrayOfLists[bucket];
    while (iter != NULL)
    {
        if(strcmp(iter->kv->key, key) == 0) {
            return 1;
        }
        iter = iter->next;
    } 
    return 0;
}

// Insert a new key/value pair into a hashmap
// The algorithm is:
//  - If a key already exists, do not add it--return
//  - Call the _hashmap's hash function on the key
//  - Store the key/value pair at the end of the buckets chain
//      - You should malloc the key/value in this function
// This function should run in average-case constant time
void hashmap_insert(hashmap_t* _hashmap,char* key,char* value) {
    if (_hashmap == NULL) {
        return;
    }
    pair_t* newPair = (pair_t*)malloc(sizeof(pair_t));
    newPair->key = (char*)malloc(strlen(key) * sizeof(char) + 1);
    newPair->value = (char*)malloc(strlen(value) * sizeof(char) + 1);

    strcpy(newPair->key, key);
    strcpy(newPair->value, value);

    node_t* newNode = (node_t*)malloc(sizeof(node_t));
    newNode->kv = newPair;
    newNode->next = NULL;

    unsigned int bucket = _hashmap->hashFunction(key, _hashmap->buckets);

    if (_hashmap->arrayOfLists[bucket] == NULL)
    {
        _hashmap->arrayOfLists[bucket] = newNode;
    } else {
        node_t* temp = _hashmap->arrayOfLists[bucket];
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Return a value from a key 
// Returns NULL if the _hashmap is NULL
// Returns NULL if the key is not found
// The algorithm is:
//  - If the key does not exist, then--return NULL if not found.
//  - Call the _hashmap's hash function on the key
//  - Search the _hashmap's bucket for the key and return the value
// This function should run in average-case constant time
char* hashmap_getValue(hashmap_t* _hashmap, char* key) {
    if (_hashmap == NULL)
    {
        return NULL;
    }
    if (hashmap_hasKey(_hashmap, key) == 0)
    {
        return NULL;
    }

    unsigned int bucket = _hashmap->hashFunction(key, _hashmap->buckets);
    node_t* iter = _hashmap->arrayOfLists[bucket];
    while (iter != NULL)
    {
        if (strcmp(iter->kv->key, key) == 0) {
            return iter->kv->value;
        }
        iter = iter->next;
    }
    return NULL;
}

// Remove a key from a hashmap
// The algorithm is:
//  - Determine if the key exists--return if it does not.
//  - Call the _hashmap's hash function on the key
//  - Search the _hashmap's bucket for the key and then remove it
// This function should run in average-case constant time
void hashmap_removeKey(hashmap_t* _hashmap, char* key) {
	if (hashmap_hasKey(_hashmap, key) == 0 || _hashmap == NULL)
    {
        return;
    }
    
    unsigned int bucket = _hashmap->hashFunction(key, _hashmap->buckets);
    node_t* iter = _hashmap->arrayOfLists[bucket];
    node_t* prevNode = NULL;
    while (iter != NULL)
    {
        if (strcmp(iter->kv->key, key) == 0)
        {
            // when the key to be removed is the first one in this bucket
            if (prevNode == NULL)
            {
                // and it's also the only one in the bucket
                if (iter->next == NULL)
                {
                    _hashmap->arrayOfLists[bucket] = NULL;
                    freeNode(iter);
                    return;
                } else { // but the key is not the only one in the bucket
                    _hashmap->arrayOfLists[bucket] = iter->next;
                    freeNode(iter);
                    return;
                } 
            } else { // when the key to be removed is in the middle of this bucket
                if (iter->next != NULL)
                {
                    prevNode->next = iter->next;
                    freeNode(iter);
                    return;
                } else { // when the key to be removed is the last on in the list of this bucket
                    prevNode->next = NULL;
                    freeNode(iter);
                    return;
                }
            }
        }
        prevNode = iter;
        iter = iter->next;
    }
    return;
}

// Update a key with a new Value
// The algorithm is:
//  - Returns immediately if the key does not exist
//  - Call the _hashmap's hash function on the key
//  - Updates the value of the key to the new value
// This function should run in average-case constant time
void hashmap_update(hashmap_t* _hashmap, char* key, char* newValue) {
	// TODO: Implement me!!
    if (hashmap_hasKey(_hashmap, key) == 0 || _hashmap == NULL)
    {
        return;
    }

    unsigned int bucket = _hashmap->hashFunction(key, _hashmap->buckets);
    node_t* iter = _hashmap->arrayOfLists[bucket];
    while (iter != NULL)
    {
        if (strcmp(iter->kv->key, key) == 0) {
            char* oldValue = iter->kv->value;
            free(oldValue);
            iter->kv->value = (char*)malloc(strlen(newValue) * sizeof(char) + 1);
            strcpy(iter->kv->value, newValue);
        }
        iter = iter->next;
    }
    return;
}

// Prints all of the keys in a hashmap
// The algorithm is:
//  - Iterate through every bucket and print out the keys
// This function should run in O(n) time
void hashmap_printKeys(hashmap_t* _hashmap){
    for (int i = 0; i < _hashmap->buckets; i++)
    {
        printf("Bucket# %d\n", i);
        node_t* iter = _hashmap->arrayOfLists[i];
        while (iter != NULL)
        {
            printf("\tKey=%s\tValue=%s", iter->kv->key, iter->kv->value);
            iter = iter->next;
        } 
    }
}

#endif
