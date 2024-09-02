/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 21:23:49 by mizem             #+#    #+#             */
/*   Updated: 2024/09/02 01:01:49 by abdennac         ###   ########.fr       */
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
	t_main *main;
	char *line;
	char **tokens;
	int i;
	int flag;

	main = malloc(sizeof(t_main));
	(void)av;
	main->cmd = NULL;
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
				main->cmd = create_list(main->cmd, *tokens, environment(getenv("PATH")), flag);
				main->full_env = env;
				main->env = enviroment_variable(env);
				printf("Command :	[%s]\n", main->cmd->command);
				printf("Path :		[%s]\n", main->cmd->path);
				printf("Output file :	[%s]\n", main->cmd->output_file);
				printf("Input file :	[%s]\n", main->cmd->input_file);
				printf("Pipe_out :	[%d]\n", main->cmd->pipe_out);
				i = -1;
				while (main->cmd->args[++i])
					printf("-------> Args : {%s}\n", main->cmd->args[i]);
				tokens++;
				flag--;
			}
			add_history(line);
		}
		execute_command(main);
	}
}
