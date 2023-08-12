# Create a shell. It's small but still powerful 

### reference  

[GNU Bash Manual][bash]  
[Posix shell][posix]  
[Shell Grammar Rules][shell]  
[Base Definitions][base]  
[LL parser][ll]  
[Chomsky hierarchy][chom]

[bash]: https://www.gnu.org/software/bash/manual/bash.html
[posix]: https://pubs.opengroup.org/onlinepubs/9699919799/utilities/contents.html
[shell]: https://pubs.opengroup.org/onlinepubs/009604499/utilities/xcu_chap02.html#tag_02_10_02
[base]: https://pubs.opengroup.org/onlinepubs/9699919799.2018edition/
[ll]: https://en.wikipedia.org/wiki/LL_parser
[chom]: https://en.wikipedia.org/wiki/Chomsky_hierarchy


### Parse command
```c
static void	connect_command_node_to_tree(t_binarytree *tree, \
	t_tree_node *rightmost, t_tree_node *previous, t_tree_node *command_node)
{
	if (find_pipe(rightmost) == TRUE \
		|| rightmost->type == AND || rightmost->type == OR)
	{
		put_it_on_the_right_of_the_rightmost_node(tree, rightmost, previous, \
				command_node);
	}
	else if ((rightmost->type == WORD || rightmost->type == BUILTIN))
	{
		free(command_node);
	}
	else if (is_redirection(rightmost->type))
	{
		put_it_on_the_top_of_the_rightmost_node(tree, rightmost, previous, \
				command_node);
	}
}

void	add_command_to_the_tree(t_binarytree *tree, t_tree_node *command_node)
{
	t_tree_node	*current;
	t_tree_node	*previous;

	if (tree->root == NULL)
	{
		tree->root = command_node;
		return ;
	}
	else
	{
		get_rightmost_and_previous(tree, &current, &previous);
		connect_command_node_to_tree(tree, current, previous, command_node);
	}
}

void	parse_command_and_option(t_binarytree *tree, t_token *tokens,
		int *index)
{
	t_tree_node	*command_node;

	command_node = create_new_node(tokens[*index].value, tokens[*index].type);
	add_command_to_the_tree(tree, command_node);
	while (tokens[*index].type == WORD || tokens[*index].type == BUILTIN)
	{
		fill_command_structure(tree, tokens[*index].value);
		(*index)++;
	}
}
```

```c
static size_t	get_command_size(t_tree_node *command_node)
{
	size_t	i;

	i = 0;
	while (command_node->command[i] != NULL)
	{
		i++;
	}
	return (i);
}

static char	**get_new_command(t_tree_node *command_node, \
	char *value, size_t size)
{
	char	**new_command;

	new_command = ft_calloc(size + 2, sizeof(char *));
	ft_memmove(new_command, command_node->command, size * sizeof(char *));
	new_command[size] = value;
	new_command[size + 1] = NULL;
	return (new_command);
}

void	fill_command_structure(t_binarytree *tree, char *value)
{
	char		**new_command;
	t_tree_node	*command_node;
	size_t		size;

	command_node = find_rightmost_node(tree->root);
	if (command_node->command == NULL)
	{
		command_node->command = (char **)ft_calloc(2, sizeof(char *));
		command_node->command[0] = value;
		command_node->command[1] = NULL;
	}
	else
	{
		size = get_command_size(command_node);
		new_command = get_new_command(command_node, value, size);
		free(command_node->command);
		command_node->command = new_command;
	}
}
```

### parse pipe
```c

static void	connect_pipe_node_to_tree(t_binarytree *tree, \
	t_tree_node *rightmost, t_tree_node *previous, t_tree_node *pipe_node)
{
	if (find_pipe(rightmost) == TRUE || rightmost->type == AND || \
		rightmost->type == OR)
	{
		free(pipe_node);
		printf("Syntax error: unexpected pipe '|'\n");
		tree->syntex_error = TRUE;
	}
	else if (rightmost->type == WORD || rightmost->type == BUILTIN)
	{
		put_it_on_the_left_of_the_rightmost_node(tree, rightmost, previous, \
				pipe_node);
	}
	else if (is_redirection(rightmost->type))
	{
		put_it_on_the_top_of_the_rightmost_node(tree, rightmost, previous, \
				pipe_node);
	}
}

static void	pipe_to_the_tree(t_binarytree *tree, t_tree_node *pipe_node, \
		int *index)
{
	t_tree_node	*current;
	t_tree_node	*previous;

	if (tree->root == NULL)
	{
		free(pipe_node);
		printf("Syntax error: unexpected pipe '|'\n");
		tree->syntex_error = TRUE;
		(*index)++;
	}
	else
	{
		get_rightmost_and_previous(tree, &current, &previous);
		if (current->type == PIPE || current->type == AND || \
				current->type == OR)
		{
			free(pipe_node);
			printf("Syntax error: unexpected pipe '|'\n");
			tree->syntex_error = TRUE;
			(*index)++;
			return ;
		}
		connect_pipe_node_to_tree(tree, current, previous, pipe_node);
	}
	(*index)++;
}

void	parse_pipe(t_binarytree *tree, t_token *tokens, int *index)
{
	int			type;
	char		*pipe;
	t_tree_node	*pipe_node;

	type = tokens[*index].type;
	pipe = tokens[*index].value;
	if (type != PIPE)
		return ;
	pipe_node = create_new_node(pipe, type);
	pipe_to_the_tree(tree, pipe_node, index);
}
```

### parse redirection
```c
void	parse_filename(t_tree_node *new_node, char *value, int *index)
{
	new_node->filename = ft_strdup(value);
	(*index)++;
}

static void	connect_redirection_node(t_binarytree *tree, \
t_tree_node *rightmost, t_tree_node *previous, t_tree_node *redirection_node)
{
	if (find_pipe(rightmost) == TRUE)
	{
		rightmost->right = redirection_node;
	}
	else if ((rightmost->type == WORD || rightmost->type == BUILTIN))
	{
		put_it_on_the_left_of_the_rightmost_node(tree, rightmost, previous, \
				redirection_node);
	}
	else if (is_redirection(rightmost->type))
	{
		put_it_on_the_top_of_the_rightmost_node(tree, rightmost, previous, \
				redirection_node);
	}
	else if (rightmost->type == AND || rightmost->type == OR)
	{
		put_it_on_the_right_of_the_rightmost_node(tree, rightmost, previous, \
				redirection_node);
	}
}

static void	redirection_to_tree(t_binarytree *tree, t_tree_node *redirection)
{
	t_tree_node	*current;
	t_tree_node	*previous;

	if (tree->root == NULL)
	{
		tree->root = redirection;
	}
	else
	{
		get_rightmost_and_previous(tree, &current, &previous);
		connect_redirection_node(tree, current, previous, redirection);
	}
}

void	parse_redirection(t_binarytree *tree, t_token *tokens, int *index)
{
	int			type;
	char		*redirection;
	t_tree_node	*new_node;

	type = tokens[*index].type;
	redirection = tokens[*index].value;
	if (is_redirection(type) == 0)
		return ;
	new_node = create_new_node(redirection, type);
	redirection_to_tree(tree, new_node);
	(*index)++;
	if (tokens[*index].type == WORD)
		parse_filename(new_node, tokens[*index].value, index);
	else
	{
		printf("Error: Missing filename after '%s'\n", redirection);
		tree->syntex_error = TRUE;
	}
}
```
