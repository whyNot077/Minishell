#include "../../includes/minishell.h"

stack	*create_stack(void)
{
	stack	*list;

	list = calloc(1, sizeof(stack));
	if (!list)
		return (NULL);
	return (list);
}

static stack_node	*create_new_node(tree_node *data)
{
	stack_node	*new_node;

	new_node = calloc(1, sizeof(stack_node));
	if (!new_node)
		return (NULL);
	new_node->data = data;
	return (new_node);
}

int	push(stack *list, tree_node *data)
{
	stack_node	*new_node;

	if (list == NULL)
		return (-1);
	new_node = create_new_node(data);
	if (list->headnode == NULL)
		list->headnode = new_node;
	else
	{
		list->top->next = new_node;
		new_node->prev = list->top;
	}
	list->top = new_node;
	return (0);
}

int	pop(stack *list)
{
	tree_node	*data;
	stack_node	*del_node;

	if (list == NULL || list->top == NULL)
		return (-1);
	data = list->top->data;
	del_node = list->top;
	if (list->top->prev == NULL)
	{
		list->top = NULL;
		list->headnode = NULL;
	}
	else
	{
		list->top = list->top->prev;
		list->top->next = NULL;
		del_node->prev = NULL;
	}
	free(del_node);
	del_node = NULL;
	return (0);
}

void	display_stack(stack *list)
{
	stack_node	*dummy;

	if (list == NULL || list->top == NULL)
	{
		printf("empty list\n");
		return ;
	}
	dummy = list->headnode;
	printf("\n----------------\n");
	printf("\ndisplay_list\n");
	while (dummy != NULL)
	{
		printf("%s ", dummy->data->data);
		dummy = dummy->next;
	}
	printf("\n----------------\n");
}

void	destroy_stack(stack **list)
{
	stack_node	*dummy;
	stack_node	*remove;

	if (!*list)
		return ;
	dummy = (*list)->headnode;
	while (dummy != NULL)
	{
		remove = dummy;
		dummy = dummy->next;
		free(remove);
		remove = NULL;
	}
	free(*list);
	*list = NULL;
}
