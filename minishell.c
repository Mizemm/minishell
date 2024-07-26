/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 21:23:49 by mizem             #+#    #+#             */
/*   Updated: 2024/07/26 17:42:47 by mizem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int main(int ac, char **av, char **env)
{
	char *line;

	char **tokens;
	(void)av;
	(void)env;
	if (ac < 1)
		exit(1);
	while (1)
	{
		line = readline("minishell $ ");
		if (!line)
			break;
		if (*line)
		{
			tokens = ft_split(line, ' ');
			while(*tokens)
			{
				printf("<%s>\n", *tokens);
				tokens++;
			}
		}
	}
}