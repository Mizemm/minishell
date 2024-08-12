/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 21:23:49 by mizem             #+#    #+#             */
/*   Updated: 2024/08/09 17:33:39 by mizem            ###   ########.fr       */
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
			if (db_quotes_counter(line) % 2 != 0 || sg_quotes_counter(line) % 2 != 0)
				break ;
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
