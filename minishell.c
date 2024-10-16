/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 21:23:49 by mizem             #+#    #+#             */
/*   Updated: 2024/10/16 23:54:16 by mizem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	// signal(SIGINT, handle_sigint);
	// atexit(leaks);
	t_main *main;
	t_lexer *lex_list;
	char *line;
	int flag;
	(void)av;
	using_history();
	main = malloc(sizeof(t_main));
	main->exit_status = 0;
	flag = 1;
	if (ac < 1)
		return 0;
	while (1)
	{
		// handle_signals();
		line = readline("lminishin $ ");
		if (!line)
			break ;
		if (*line)
		{
			if (flag != 1)
				main = malloc(sizeof(t_main));
			flag = 0;
			main->env = enviroment_variable(env);
			main->full_env = env;
			lex_list = NULL;
			main->cmd = NULL;
			lex_list = tokenize(line, main);
			if (lex_list != NULL && lex_list->syntax_error == false)
			{
				main->cmd = create_list(main->cmd, lex_list, environment(main));
				// while(main->cmd)
				// {
				// 	printf("COMMAND : %s\n", main->cmd->command);
				// 	printf("PATH : %s\n", main->cmd->path);
				// 	printf("ARG COUNT : %d\n", main->cmd->arg_count);
				// 	printf("PIPE OUT : %d\n", main->cmd->pipe_out);
				// 	int i = -1;
				// 	if (main->cmd->args)
				// 	{
				// 	while(main->cmd->args[++i])
				// 		printf("ARGS : %s\n", main->cmd->args[i]);
				// 	}
				// 	if (main->cmd->input_file)
				// 	{
				// 	i = -1;
				// 	while(main->cmd->input_file[++i])
				// 		printf("INPUT FILES : %s\n", main->cmd->input_file[i]);
				// 	}
				// 	if (main->cmd->output_file)
				// 	{
				// 	i = -1;
				// 	while(main->cmd->output_file[++i])
				// 		printf("OUTPUT FILES : %s\n", main->cmd->output_file[i]);
				// 	}
				// 	if (main->cmd->append_file)
				// 	{
				// 	i = -1;
				// 	while(main->cmd->append_file[++i])
				// 		printf("APPEND FILES : %s\n", main->cmd->append_file[i]);
				// 	}
				// 	if (main->cmd->heredoc_delimiter)
				// 	{
				// 	i = -1;
				// 	while(main->cmd->heredoc_delimiter[++i])
				// 		printf("HERDOC FILES : %s\n", main->cmd->heredoc_delimiter[i]);
				// 	}
				// 	printf("###############\n");
				// 	main->cmd = main->cmd->next;
				// }
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
