/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 21:23:49 by mizem             #+#    #+#             */
/*   Updated: 2024/10/18 14:51:06 by mizem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	leaks(void)
{
	system("leaks minishell");
}

t_env	*enviroment_variable(char **ev)
{
	int		i;
	char	**tmp;
	t_env	*head;
	t_env	*current;
	t_env	*new_node;

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
		if (!head)
			head = new_node;
		else
			current->next = new_node;
		current = new_node;
	}
	return (head);
}
void	minish(t_main *main, char *line, t_lexer *lex_list)
{
	main->flag = 0;
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
}
int	main(int ac, char **av, char **env)
{
	char	*line;
	t_main	*main;
	t_lexer	*lex_list;
	// atexit(leaks);
	if (ac != 1 || !env)
		return (0);
	using_history();
	(void)av;
	main = malloc(sizeof(t_main));
	main->cmd = NULL;
	main->exit_status = 0;
	main->flag = 1;
	main->env = enviroment_variable(env);
	main->full_env = env;
	lex_list = NULL;
	while (1)
	{
		// handle_signals();
		line = readline("lminishin $ ");
		if (!line)
			break ;
		if (*line)
		{
			if (main->flag != 1)
			{
				main = malloc(sizeof(t_main));
				main->env = enviroment_variable(env);
				main->full_env = env;
			}
			minish(main, line, lex_list);
			add_history(line);
			clear(main, lex_list, line);
		}
	}
}
