#include "list.hpp"

unsigned int node_t::list_size = 0;

node_t* create_node(int val)
{
	node_t* current_node = (node_t*) malloc(sizeof(node_t));
		
	//now check if the allocation was successful
	if(current_node == NULL)
	{
		exit(0);
	}
	//set the nodes fields to corresponding values
	else
	{
		(*current_node).val = val;
		(*current_node).next = NULL;
	}
	
	return current_node;
}

void print_list(node_t** head)
{
	/*
	* Start with the node given as input, then make sure it is not NULL, then dereference it in order to access the next element in the list.
	* If the check iterator=>next != NULL is used, the last element is not accessed as itś next points to NULL
	*/
	if(*head)
	{
		printf("\nThe elements currently in the list are listed beneath:\n");
		for(node_t* iterator = *head; iterator != NULL; iterator = iterator->next)
		{
			printf("Pointer: %p | Value: %d | Next pointer: %p \n", iterator, iterator->val, iterator->next);
		}
		printf("\n");
	}
}

void append_node(node_t** head, node_t** new_node)
{
	//append the new node only if the head exists
	if(*head)
	{
		node_t* iterator;

		//start with the node given as input. If it points to another node, then dereference it in order to access the next element in the list
		for(iterator = *head; iterator->next != NULL; iterator = iterator->next);
		
		//last element found: double check
		if(iterator->next == NULL)
		{
			iterator->next = *new_node;
			(**new_node).next = NULL;
			
			//node added to list, increase the list size
			node_t::list_size++;
			printf("A new node was appended. The list size is: %d\n", node_t::list_size);
		}
	}
}

void remove_last_node(node_t** head)
{
	if(*head)
	{
		//if the list contains only the head
		if((**head).next == NULL)
		{
			free(*head);
			*head = NULL;
			node_t::list_size--;
			printf("The lists head was removed. The list size is: %d\n",  node_t::list_size);
		}
		else
		{
			node_t* iterator;
			//find the second last element in list
			for(iterator = *head; iterator->next->next != NULL; iterator = iterator->next);

			//double check
			if(iterator->next->next == NULL)
			{
				//second last element was found, delete the node it points to
				free(iterator->next);
				iterator->next = NULL;

				printf("The last node was removed. The new tail address is %p, its value is %d \n",  iterator, iterator->val);
				node_t::list_size--;
				printf("The list size is: %d\n", node_t::list_size);
			}
		}
	}
}

void prepend_node(node_t** head, node_t** new_node)
{
	if(*head)
	{
		//by default, any new node does not point to a next element, but to null. New node should point to old head
		(**new_node).next = *head;
		//replace head with the new node
		*head = *new_node;

		//node added to list, increase the list size
		node_t::list_size++;
		printf("A new node was prepended. The list size is: %d\n", node_t::list_size);
	}
}

void remove_first_node(node_t** head)
{
	if(*head)
	{
		//if there is only one element in list
		if((**head).next == NULL)
		{
			//delete the head
			free(*head);
			*head = NULL;
			//update list size
			node_t::list_size--;
			printf("The listś head was removed. The list size is: %d\n",  node_t::list_size);
		}
		else
		{
			//get second element
			node_t* new_head = (**head).next;
			//delete first element
			free(*head);
			//new head
			*head = new_head;
			printf("The first node was removed. The new head address is %p, its value is %d \n",  *head, (*head)->val);
			
			//update list size
			node_t::list_size--;
			printf("The list size is: %d\n", node_t::list_size);
		}
	}
}

void insert_node_at_index(node_t** head, node_t** new_node, unsigned short int index)
{
	if(*head && index <= node_t::list_size)
	{
		//if the node is inserted on the first position, then it is prepended
		if(index == 0)
		{
			prepend_node(head, new_node);
		}
		//if the node is appended, it is added on index ehich is the current list_size + 1
		else if(index == node_t::list_size)
		{
			append_node(head, new_node);
		}
		else
		{
			node_t *iterator = NULL, *swap = NULL;
			unsigned short int idx = 0;

			//Within the loop is seeked for the node pointing to the node whose next should be the new node
			//After the loop ends its iterations both the iterator and index will indicate the node to whom the new node shall be appended
			for(iterator = *head, idx = 0; iterator-> next != NULL && idx < index - 1; iterator = iterator->next, idx++);

			swap = iterator->next;
			iterator->next = *new_node;
			(**new_node).next = swap;

			node_t::list_size++;
			printf("A new node was added on position %d. The list size is: %d\n", index, node_t::list_size);
		}
		
	}
}

void remove_node_at_index(node_t** head, unsigned short int index)
{
		if(*head && index <= node_t::list_size)
	{
		//if the node is inserted on the first position, then it is prepended
		if(index == 0)
		{
			remove_first_node(head);
		}
		//if the node is appended, it is added on index ehich is the current list_size + 1
		else if(index == node_t::list_size-1)
		{
			remove_last_node(head);
		}
		else
		{
			node_t *iterator = NULL, *swap = NULL;
			unsigned short int idx = 0;

			//Within the loop is seeked for the node pointing to the node whose next should be the node to be deleted
			//After the loop ends its iterations both the iterator and index will indicate the node to whom the new node shall be appended
			for(iterator = *head, idx = 0; iterator-> next != NULL && idx < index - 1; iterator = iterator->next, idx++);

			//get the next node that the node to be deleted points to
			swap = iterator->next->next;
			free(iterator->next);
			iterator->next = swap;

			node_t::list_size--;
			printf("The node on position %d was deleted. The list size is: %d\n", index, node_t::list_size);
		}
		
	}
}

void delete_list(node_t** head)
{
	if(*head)
	{
		node_t* iterator;

#ifndef FLAWLESS_DELETE_METHOD
		//invalid read of size 8 for the last element in list
		//increment done after the for body (after free is executed)
		for(iterator = *head; iterator != NULL; iterator = iterator->next)
		{
			free(iterator);
		}
#else	
		node_t* next = NULL;
		unsigned short int index;
		const unsigned short int size = (**head).list_size;

		printf("All nodes in list are deleted sequentially\n");
		for(iterator = *head, index = 0; iterator != NULL && index < size; iterator = next, index++)
		{
			//hold the address of the next element in a swap, so the increment can be properly done
			next = iterator->next;

			node_t::list_size--;
			printf("The node %d was removed. The list size is: %d\n", index,  node_t::list_size);
			//free the current element
			free(iterator);
		}
#endif
		
		//set the first element to null
		*head = NULL;

		printf("The list was deleted\n");
	}
}