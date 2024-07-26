/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 21:23:49 by mizem             #+#    #+#             */
/*   Updated: 2024/07/26 20:34:03 by mizem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int main(int ac, char **av, char **env)
{
	char *line;
	t_cmd *list;
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
			tokens = ft_split(line, ' ');
			list = create_list(tokens);
			printf("command : %s\ncount : %d\n", list->command, list->arg_count);
			add_history(line);
			int i = 0;
			while (i < count_ac(tokens))
			{
				printf("argument :<%s>\n", (list->args[i]));
				i++;;
			}
		}
	}
}