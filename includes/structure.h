#ifndef STRUCTURE_H
# define STRUCTURE_H

typedef struct s_token
{
    char	*value;
	int		type;
}	t_token;

typedef struct tree_node {
	char				*data;
	struct tree_node	*left;
    struct tree_node	*right;
} tree_node;

typedef struct binarytree {
	tree_node	*root;
} binarytree;

#endif