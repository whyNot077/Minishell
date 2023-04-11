#ifndef LINKED_STACK_H
# define LINKED_STACK_H

stack		*create_stack(void);
int			push(stack *list, int data);
int			pop(stack *list);
void		display_stack(stack *list);
void		destroy_stack(stack **list);

#endif