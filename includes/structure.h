#ifndef STRUCTURE_H
# define STRUCTURE_H

typedef struct tree_node {
	char				*data;
	struct tree_node	*left;
    struct tree_node	*right;
} tree_node;

typedef struct binarytree {
	tree_node	*root;
} binarytree;

typedef struct stack_node {
	tree_node			*data;
	struct stack_node	*next;
	struct stack_node	*prev;
} stack_node;

typedef struct list {
	stack_node	*top;
	stack_node	*headnode;
} stack;

typedef struct queue_node {
	tree_node			*data;
	struct queue_node	*next;
} queue_node;

typedef struct queue {
	queue_node	*headnode;
	queue_node	*rearnode;
} queue;


#endif