/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 21:23:49 by mizem             #+#    #+#             */
/*   Updated: 2024/09/02 00:42:08 by abdennac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env *enviroment_variable(char **ev)
{
    int i = -1;
    t_env *head = NULL;
    t_env *current = NULL;
	t_env *new_node;
	char **tmp;

    while (ev[++i])
    {
        new_node = malloc(sizeof(t_env));
        tmp = ft_split(ev[i], '=');
        new_node->name = ft_strdup(tmp[0]);
        new_node->value = ft_strdup(tmp[1]);
        new_node->next = NULL;
        if (!head)
            head = new_node;
        else
            current->next = new_node;
        current = new_node;
    }
    return head;
}

int main(int ac, char **av, char **env)
{
	t_cmd *list;
	char *line;
	char **tokens;
	int i;
	int flag;

	(void)av;
	list = NULL;
	if (ac < 1)
		exit(1);
	using_history();
	while (1)
	{
		line = readline("minishin $ ");
		if (!line)
			break;
		if (*line)
		{
			if (db_quotes_counter(line) % 2 != 0 || sg_quotes_counter(line) % 2 != 0)
				break;
			tokens = pipe_split(line, '|');
			flag = count_ac(tokens);
			while (*tokens)
			{
				list = create_list(list, *tokens, environment(getenv("PATH")), flag);
				list->full_env = env;
				list->env = enviroment_variable(env);
				printf("Command :	[%s]\n", list->command);
				printf("Path :		[%s]\n", list->path);
				printf("Output file :	[%s]\n", list->output_file);
				printf("Input file :	[%s]\n", list->input_file);
				printf("Pipe_out :	[%d]\n", list->pipe_out);
				i = -1;
				while (list->args[++i])
					printf("-------> Args : {%s}\n", list->args[i]);
				tokens++;
				flag--;
			}
			add_history(line);
		}
		execute_command(list);
	}
}
