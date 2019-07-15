#include <stdio.h>
#include <stdlib.h>

#define FLAWLESS_DELETE_METHOD

struct node
{
	static unsigned int list_size; //valid only in c++
	int val;
	struct node *next;
};

typedef struct node node_t;

/*
 * Function that creates a node internally 
 * The input parameter is:
 *  - the value to be stored int the created node
 * The output is:
 *  - the pointer to the internally allocated node
 *  The address of the next element in list is set to NULL by default.
 */ 
node_t* create_node(int val);

/*
 * Iterate over the list and print the integer values and the current pointer value
 * The input is:
 *  - the first element in the list
 */ 
void print_list(node_t** head);

/*
 * Iterate over the list and find the last node, then append the new node to the last node in list
 * Inputs:
 *  - the node to be appended
 *  - the head node of the list
 */ 
void append_node(node_t** head, node_t** new_node);

/*
 * Iterate over the list and find the second last node, then remove the next node
 * Input:
 *  - the head node of the list
 */ 
void remove_last_node(node_t** head);

/*
 * Replace head with the new node which becomes the new head. The new head points to old head
 * Inputs:
 *  - the node to be prepended (new head)
 *  - the head node of the list (old head)
 */ 
void prepend_node(node_t** head, node_t** new_node);

/*
 * The new head is the old second element
 * Input:
 *  - the head node of the list
 */ 
void remove_first_node(node_t** head);

/*
 * Iterate over the list and delete the current element. Lastly set the head to point to NULL
 * Input:
 *  - the head node of the list
 */ 
void delete_list(node_t** head);

/*
 * If index equals lists size, then call append_node.
 * If index equals 0, then call prepend_node.
 * Else, iterate over the list to find the previous node to the one pointed by index.
 * Once found, then append the new node to it and prepend to its former next.
 * Input:
 *  - the head node of the list
 *  - the node to be inserted
 *  - the index where the new node should be inserted 
 */ 
void insert_node_at_index(node_t** head, node_t** node, unsigned short int index);

/*
 * If index equals lists size, then call remove_last_node.
 * If index equals 0, then call remove_first_node.
 * Else, iterate over the list to find the previous node to the one pointed by index.
 * Once found, then remove the node it points to and bind it to the deleted nodes next.
 * Input:
 *  - the head node of the list
 *  - the node to be inserted
 *  - the index where the new node should be inserted 
 */
void remove_node_at_index(node_t** head, unsigned short int index);