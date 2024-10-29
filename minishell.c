/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:29:43 by abdennac          #+#    #+#             */
/*   Updated: 2024/10/29 10:46:20 by abdennac         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

void leaks(void)
{
	system("leaks minishell");
}

t_env *enviroment_variable(char **ev)
{
	int i;
	char **tmp;
	t_env *head;
	t_env *current;
	t_env *new_node;

	i = -1;
	head = NULL;
	current = NULL;
	while (ev[++i])
	{
		new_node = malloc(sizeof(t_env));
		tmp = ft_split(ev[i], '=');
		new_node->name = ft_strdup(tmp[0]);
		new_node->value = ft_strdup(tmp[1]);
		new_node->next = NULL;
		ft_free(tmp);
		if (!head)
			head = new_node;
		else
			current->next = new_node;
		current = new_node;
	}
	return (head);
}

void loop(t_main *main, char *line, t_lexer *lex_list)
{

	lex_list = NULL;
	main->cmd = NULL;
	lex_list = tokenize(line, main);
	if (lex_list != NULL && lex_list->syntax_error == false)
	{
		main->cmd = create_list(main->cmd, lex_list, environment(main));
		handle_heredoc(main);
		if (!g_signal)
			execute_command(main);
		g_signal = 0;
	}
	else
	{
		main->exit_status = 258;
		printf("Syntax error\n");
	}
}

void initialize_1(t_main *main, t_lexer *lex_list, char **env)
{
	main->cmd = NULL;
	main->exit_status = 0;
	main->env = enviroment_variable(env);
	main->full_env = env;
	lex_list = NULL;
}

int main(int ac, char **av, char **env)
{
	t_main *main;
	t_lexer *lex_list;
	char *line;

	// atexit(leaks);
	(void)av;
	using_history();
	main = malloc(sizeof(t_main));
	lex_list = NULL;
	initialize_1(main, lex_list, env);
	if (ac < 1)
		return 0;
	while (1)
	{
		handle_signals();
		line = readline("lminishin $ ");
		if (!line)
			break;
		if (*line)
		{
			loop(main, line, lex_list);
			add_history(line);
			clear(main->cmd, line);
		}
	}
	// free(line);
	clear_all(&main);
}
