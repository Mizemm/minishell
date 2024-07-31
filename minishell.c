/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 21:23:49 by mizem             #+#    #+#             */
/*   Updated: 2024/07/31 11:33:17 by mizem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int main(int ac, char **av, char **env)
{
	t_cmd **head;
	t_cmd *list;
	char *line;
	char **tokens;
	char **paths;
	(void)av;
	
	head = NULL;
	if (ac < 1)
		exit(1);
	using_history();
	while (1)
	{
		line = readline("minishell $ ");
		paths = environment(env);
		if (!line)
			break;
		if (*line)
		{
			tokens = pipe_split(line, '|');
			while (*tokens)
			{
				list = create_list(*tokens);
				printf("Command : [%s]\n", list->command);
				int i = 0;
				while (list->args[i])
				{
					printf(" Args : <%s>\n", list->args[i]);
					i++;
				}
				ft_lstadd_back(head, list);
				tokens++;
			}
			add_history(line);
		}
	}
}