/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 21:23:49 by mizem             #+#    #+#             */
/*   Updated: 2024/10/17 02:56:08 by abdennac         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

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
	t_main *main;
	t_lexer *lex_list;
	char *line;
	int flag;
	(void)av;
	using_history();
	main = malloc(sizeof(t_main));
	main->cmd = NULL;
	main->exit_status = 0;
	flag = 1;
	if (ac < 1)
		return 0;
	main->env = enviroment_variable(env);
	main->full_env = env;
	while (1)
	{
		handle_signals();
		line = readline("lminishin $ ");
		if (!line)
			break ;
		if (*line)
		{
			if (flag != 1)
			{
				main = malloc(sizeof(t_main));
				main->env = enviroment_variable(env);
				main->full_env = env;
			flag = 0;
			}
			lex_list = NULL;
			main->cmd = NULL;
			lex_list = tokenize(line, main);
			if (lex_list != NULL && lex_list->syntax_error == false)
			{
				main->cmd = create_list(main->cmd, lex_list, environment(main));
				handle_heredoc(main);
				execute_command(main);
			}
			else
			{
				main->exit_status = 258;
				printf("Syntax error\n");
			}
			add_history(line);
			// clear(main, lex_list, line);
		}
	}
}
