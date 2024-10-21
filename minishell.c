/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 21:23:49 by mizem             #+#    #+#             */
/*   Updated: 2024/10/21 23:50:50 by mizem            ###   ########.fr       */
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
		ft_free(tmp);
		if (!head)
			head = new_node;
		else
			current->next = new_node;
		current = new_node;
	}
	return (head);
}

void	loop(t_main *main, char *line, t_lexer *lex_list)
{

	lex_list = NULL;
	main->cmd = NULL;
	lex_list = tokenize(line, main);
	if (lex_list != NULL && lex_list->syntax_error == false)
	{
		main->cmd = create_list(main->cmd, lex_list, environment(main));
		system("leaks -q minishell");
		handle_heredoc(main);
		execute_command(main);
	}
	else
	{
		main->exit_status = 258;
		printf("Syntax error\n");
	}

}

void	initialize_1(t_main *main, t_lexer *lex_list, char **env)
{
	main->cmd = NULL;
	main->exit_status = 0;
	main->env = enviroment_variable(env);
	// system("leaks -q minishell");
	main->full_env = env;
	lex_list = NULL;
}

int main(int ac, char **av, char **env)
{
	atexit(leaks);
	t_main *main;
	t_lexer *lex_list;
	char *line;

	(void)av;
	using_history();
	main = malloc(sizeof(t_main));
	lex_list = NULL;
	initialize_1(main, lex_list, env);
	if (ac < 1)
		return 0;
	while (1)
	{
		// handle_signs();
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
	clear_all(&main);
}


// void	minish(t_main *main, char *line, t_lexer *lex_list)
// {
// 	main->flag = 0;
// 	lex_list = NULL;
// 	main->cmd = NULL;
// 	lex_list = tokenize(line, main);
// 	if (lex_list != NULL && lex_list->syntax_error == false)
// 	{
// 		main->cmd = create_list(main->cmd, lex_list, environment(main));
// 		handle_heredoc(main);
// 		execute_command(main);
// 	}
// 	else
// 	{
// 		main->exit_status = 258;
// 		printf("Syntax error\n");
// 	}
// }
// void	initialize_1(t_main *main, t_lexer *lex_list, char **env)
// {
// 	main->cmd = NULL;
// 	main->exit_status = 0;
// 	main->flag = 1;
// 	main->env = enviroment_variable(env);
// 	main->full_env = env;
// 	lex_list = NULL;
// }

// void initialize_2(t_main *main, t_lexer *lex_list, char **env)
// {
// 	main->env = enviroment_variable(env);
// 	main->full_env = env;
// }
// int	main(int ac, char **av, char **env)
// {
// 	char	*line;
// 	t_main	*main;
// 	t_lexer	*lex_list;
// 	// atexit(leaks);
// 	if (ac != 1 || !env)
// 		return (0);
// 	(void)av;
// 	using_history();
// 	main = malloc(sizeof(t_main));
// 	if (!main)
// 		return(0);
// 	initialize_1(main, lex_list, env);
// 	while (1)
// 	{
// 		// handle_signals();
// 		line = readline("lminishin $ ");
// 		if (!line)
// 			break ;
// 		if (*line)
// 		{
// 			if (main->flag != 1)
// 			{
// 				main = malloc(sizeof(t_main));
// 				if (!main)
// 					return(0);
// 				initialize_2(main, lex_list, env);
// 			}
// 			minish(main, line, lex_list);
// 			add_history(line);
// 			clear(main, lex_list, line);
// 		}
// 	}
// }
