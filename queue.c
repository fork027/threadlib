#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

struct node {
    void *data;
    struct node *next;
};

struct queue {
    struct node *head;
    struct node *tail;
    int length;
};

// allocate memory for a new queue
queue_t queue_create(void)
{
    // allocate memory for new que
    queue_t que = malloc(sizeof(*que));
    // error management for allocating memory
    if (!que)
        return NULL;
    // initialize head and tail of que
    que->head = NULL;
    que->tail = NULL;
    // initialize que length
    que->length = 0;
    return que; // return pointer to new que
} // end queue_create()

// deallocate memory for a que
int queue_destroy(queue_t que)
{
    // error management when que is not found
    if (!que || que->length)
        return -1;
    // deallocate memory
    free(que);
    return 0; 
} // end queue_destroy()

// insert a node to tail of que
int queue_enqueue(queue_t que, void *data)
{
    // error management when que is not found
    if (!que || !data)
        return -1;
    // allocate memory for a new node
    struct node *new_node = malloc(sizeof(*new_node));
    // error management for new node allocated memory
    if (!new_node)
        return -1;
    // store passed in data into new node
    new_node->data = data;
    // initialize next pointer of new node
    new_node->next = NULL;
    // when there is no node in que
    if ((!que->head) && (!que->tail)) {
        // point head and tail to the new node
        // new node is the first node in que
        que->head = que->tail = new_node;
    } else { // when there are more then one node in que
        // creating connection b/t tail and new node
        que->tail->next = new_node;
        // assign que tail to new node
        que->tail = new_node;
    } // end if, adding new node in que
    que->length++; // update que length
    return 0;
} // end queue_enqueue()

// storing head.data into pass in pointer
int queue_dequeue(queue_t que, void **data)
{
    // error management
    if (!que || !data || que->length == 0) 
        return -1;
    // store head node data into pass in pointer
    *data = que->head->data;
    // store address of curr head
    struct node *temp = que->head;
    // reassign head
    que->head = que->head->next;
    // free the previous head
    free(temp);
    // update queue length
    que->length--;
    return 0;
} // end queue_dequeue()

// delete the first node in que with the value, data
int queue_delete(queue_t que, void *data)
{
    // error management
    if (!que || !data)
        return -1;
    // create node pointers to iterate que
    struct node *curr = que->head;
    struct node *prev = NULL;
    // while not the end of que and curr node data is not target data
    while (curr && curr->data != data) {
        // move forward one node
        prev = curr;
        curr = curr->next;
    } 
    // return -1 when target data is not found in que
    if (!curr)
        return -1;

    // when prev is NULL, head data is target data
    if (!prev){
        // reassign que head to second node
        que->head = curr->next;
    }
    else { // when target data is found in the middle of que
        // connect the prev node with next node
        prev->next = curr->next;
    }

    // when curr node is last node
    if (!curr->next){
        // reassign que tail to prev node
        que->tail = prev;
    }
    // deallocate memory for curr node
    free(curr);
    // update que length
    que->length--;
    return 0;
} // end queue_delete()

// iterate que and call func on each node
int queue_iterate(queue_t que, queue_func_t func)
{
    // error management
    if (!que || !func)
        return -1;
    // create node pointer to iterate que
    struct node *curr = que->head;
    // while not the end of que
    while (curr) {
        // call func on curr node
        func(que, curr->data);
        // move to next node
        curr = curr->next;
    }
    return 0; 
} // end queue_iterate()

// return que length
int queue_length(queue_t que)
{
    if (!que)
        return -1;
    return que->length;
}
