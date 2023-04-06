/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:37:30 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/06 14:37:31 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main() {
    char *line;
	init();
    while ((line = readline("Enter a command: ")) != NULL) {
        if (strcmp(line, "clear_history") == 0) {
            rl_clear_history();
            printf("History cleared.\n");
        } else if (strcmp(line, "modify") == 0) {
            rl_on_new_line(); // Move to a new line
            rl_replace_line("Modified command", 0); // Replace the current line with a new string
            rl_redisplay(); // Redisplay the modified line

            // Read the modified line
            char *modified_line = readline(NULL);
            if (modified_line) {
                add_history(modified_line); // Add the modified line to the history
                printf("Modified command: %s\n", modified_line);
                free(modified_line);
            }
        } else {
            printf("Command: %s\n", line);
            add_history(line); // Add the line to the history
        }
        free(line);
    }
    return 0;
}
