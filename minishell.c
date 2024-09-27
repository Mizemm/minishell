/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 21:23:49 by mizem             #+#    #+#             */
/*   Updated: 2024/09/27 12:24:14 by abdennac         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

void handle_sigint(int sig)
{
	(void)sig;
	exit(0);
}

void leaks(void)
{
	system("leaks minishell");
}
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
	// atexit(leaks);
	signal(SIGINT, handle_sigint);
	t_main *main;
	t_cmd *tmp;
	char *line;
	char **tokens;
	int flag;

	(void)av;
	main = malloc(sizeof(t_main));
	main->cmd = NULL;
	if (ac < 1)
		exit(1);
	using_history();
	main->env = enviroment_variable(env);
	main->full_env = env;
	while (1)
	{
		line = readline("lminishin🤸$ ");
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
				tmp = main->cmd;
				tokens++;
				flag--;
			}
			add_history(line);
			execute_command(main);
			clear_cmd_list(main->cmd);
		}
	}
}
