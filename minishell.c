/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 21:23:49 by mizem             #+#    #+#             */
/*   Updated: 2024/10/05 17:24:54 by mizem            ###   ########.fr       */
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
	// atexit(leaks);
	// signal(SIGINT, handle_sigint);
	t_main *main;
	t_lexer *lex_list;
	char *line;

	main = malloc(sizeof(t_main));
	(void)av;
	main->cmd = NULL;
	lex_list = NULL;
	using_history();
	if (ac < 1)
		return 0;
	while (1)
	{
		line = readline("lminishin $ ");
		if (!line)
			break;
		if (*line)
		{
				main->env = enviroment_variable(env);
				main->full_env = env;
				lex_list = tokenize(line, main);
				printf("%d\n", count_redir_out(lex_list));
				printf("%d\n", count_redir_in(lex_list));
				printf("%d\n", count_her(lex_list));
				printf("%d\n", count_append(lex_list));
				if (lex_list != NULL && lex_list->syntax_error == false)
				{
					while(lex_list)
					{
						printf("%s --> ", lex_list->content);
						if (lex_list->state == IN_DQUOTE)
						printf("In double quotes : ");
						if (lex_list->state == IN_QUOTE)
							printf("In single quotes : ");
						if (lex_list->state == GENERAL)
							printf("General : ");
						if (lex_list->type == WORD)
							printf("Word");
						else if (lex_list->type == ENV)
							printf("Env");
						else if (lex_list->type == WHITE_SPACE)
							printf("White Space");
						else if (lex_list->type == PIPE_LINE)
							printf("Pipe");
						else if (lex_list->type == REDIR_IN)
							printf("Redirection in");
						else if (lex_list->type == REDIR_OUT)
							printf("Redirection out");
						else if (lex_list->type == HERE_DOC)
							printf("Heredoc");
						else if (lex_list->type == APPEND)
							printf("Append");
						printf("\n");
						lex_list = lex_list->next;
					// execute_command(main);
					}
				}
				else
					printf("Syntax error\n"); 
			}
			add_history(line);
			clear_cmd_list(main->cmd);
		}
}
