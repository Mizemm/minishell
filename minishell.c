/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 21:23:49 by mizem             #+#    #+#             */
/*   Updated: 2024/07/26 17:36:40 by mizem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int main(int ac, char **av, char **env)
{
	char *line;

	char **tmp;
	(void)av;
	(void)env;
	if (ac < 1)
		exit(1);
	tmp = enviromnt(env);
	// while (*tmp)
	// {
	// 	printf("%s\n", *tmp);
	// 	tmp++;
	// }
	while (1)
	{
		line = readline("minishell $ ");
		if (!line)
			break;
		if (*line)
		{
			parse(line);
			// printf("***%s***\n", line);
			// free(line);
		}
	}
}