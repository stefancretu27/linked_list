#include "list.hpp"

int main()
{
	node_t *head = create_node(0);
	//if the list contains only the head, increment the list size to 1
	if(head->next == NULL)
	{
		//head node was created, increase the list size
		node_t::list_size++;
		printf("Head node was created. The list size is: %d\n", node_t::list_size);
	}


	node_t *node1 = create_node(1);
	append_node(&head, &node1);

	node_t *node2 = create_node(2);
	append_node(&head, &node2);
	print_list(&head);

	node_t *node_neg = create_node(-1);
	prepend_node(&head, &node_neg);
	print_list(&head);
	
	node_t *node3 = create_node(3);
	insert_node_at_index(&head, &node3, 2);
	print_list(&head);

	remove_first_node(&head);
	print_list(&head);

	remove_node_at_index(&head, 2);
	print_list(&head);

	remove_last_node(&head);
	print_list(&head);

	delete_list(&head);

	return 0;
}