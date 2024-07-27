/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 21:23:49 by mizem             #+#    #+#             */
/*   Updated: 2024/07/27 21:54:15 by mizem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int main(int ac, char **av, char **env)
{
	t_cmd **head = NULL;
	t_cmd *list;
	char *line;
	char **tokens;
	(void)av;
	(void)env;
	
	if (ac < 1)
		exit(1);
	using_history();
	while (1)
	{
		line = readline("minishell $ ");
		if (!line)
			break;
		if (*line)
		{
			tokens = ft_split(line, '|');
			while (*tokens)
			{
				printf("<%s>\n", *tokens);
				tokens++;
			}
			while (*tokens)
			{
				list = create_list(*tokens);
				// printf("command : %s\ncount : %d\n", list->command, list->arg_count);
				// int i = 0;
				// while (list->args[i])
				// {
				// 	printf("<%s>\n", list->args[i]);
				// 	i++;
				// }
				ft_lstadd_back(head, list);
				tokens++;
			}
			add_history(line);
		}
	}
}