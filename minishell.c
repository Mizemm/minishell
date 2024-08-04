/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 21:23:49 by mizem             #+#    #+#             */
/*   Updated: 2024/08/04 01:06:34 by abdennac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av)
{
	t_cmd	*list;
	char	*line;
	char	**ev;
	char	**tokens;
	int		i;
	int		flag;

	(void)av;
	list = NULL;
	if (ac < 1)
		exit(1);
	using_history();
	while (1)
	{
		line = readline("minishin $ ");
		ev = environment(getenv("PATH"));
		if (!line)
			break ;
		if (*line)
		{
			tokens = pipe_split(line, '|');
			flag = count_ac(tokens);
			while (*tokens)
			{
				list = create_list(list, *tokens, ev, flag);
				printf("Command :	[%s]\n", list->command);
				printf("Path :		[%s]\n", list->path);
				printf("Output file :	[%s]\n", list->output_file);
				printf("Input file :	[%s]\n", list->input_file);
				printf("Pipe_out :	[%d]\n", list->pipe_out);
				i = -1;
				while (list->args[++i])
					printf("-------> Args : {%s}\n", list->args[i]);
				tokens++;
				flag--;
			}
			add_history(line);
		}
			execute_command(list);
	}
}
