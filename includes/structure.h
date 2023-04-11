#ifndef STRUCTURE_H
# define STRUCTURE_H
# define MAX_INPUT_SIZE 1024

typedef struct s_token
{
	char				*value;
	int					type;
}						t_token;

typedef struct s_process_input_data
{
	const char			*input;
	t_token				*tokens;
	int					*token_index;
	char				buffer[MAX_INPUT_SIZE];
	int					buffer_index;
}						t_process_input_data;

typedef struct s_find
{
	char				quote_char;
	int					*find;
}						t_find;

typedef struct stack_node
{
	int					data;
	struct stack_node	*next;
	struct stack_node	*prev;
}						stack_node;

typedef struct list
{
	stack_node			*top;
	stack_node			*headnode;
}						stack;

typedef struct tree_node
{
	char				*data;
	struct tree_node	*left;
	struct tree_node	*right;
}						tree_node;

typedef struct binarytree
{
	tree_node			*root;
}						binarytree;

#endif