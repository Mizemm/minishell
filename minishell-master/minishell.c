/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 21:23:49 by mizem             #+#    #+#             */
/*   Updated: 2024/08/01 09:53:34 by abdennac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_cmd	**head;
	t_cmd	*list;
	char	**ev;
	char	*line;
	char	**tokens;
	int		i;

	(void)av;
	head = NULL;
	if (ac < 1)
		exit(1);
	using_history();
	while (1)
	{
		line = readline("minishell $ ");
		ev = environment(env);
		if (!line)
			break ;
		if (*line)
		{
			tokens = pipe_split(line, '|');
			while (*tokens)
			{
				list = create_list(*tokens, ev);
				printf("Command : [%s]\n", list->command);
				printf("Path : [%s]\n", list->path);
				i = 0;
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
