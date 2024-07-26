/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 02:49:24 by abdennac          #+#    #+#             */
/*   Updated: 2024/07/26 20:33:19 by mizem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_ac(char **str)
{
	int i = 0;
	
	if (!str)
		return 0;
	while (str[i])
		i++;
	return (i);
}

int path_check(char *s)
{
	int i = 0;
	char str[5] = "PATH";
	while (s[i] && s[i] == str[i])
		i++;
	if (i == 4)
		return 1;
	return 0;
}
char **environment(char **env)
{
	int i;
	int j;
	char **tmp = NULL;

	i = 0;
	j = 0;
	while (env[i])
	{
		if (path_check(env[i]))
		{
			j= 5;
			while (env[i][j])
			{
				if (env[i][j] == '/')
				{
					tmp = ft_split(&env[i][j], ':');
					break;
				}
				j++;
			}
			break;
		}
		i++;
	}
	return tmp;
}

t_cmd *create_list(char **tokens)
{
	t_cmd *cmd;
	int ac = count_ac(tokens);
	int i = 0;

	cmd = malloc(sizeof(t_cmd));
	cmd->command = ft_strdup(tokens[0]);
	// cmd->path = ;
	cmd->arg_count = ac;
	cmd->args = malloc(sizeof(char *) * (ac + 1));
	printf("<<<<<<<<<%d>>>>>>>>>\n", ac);
	while (i < ac)
	{
		cmd->args[i] = ft_strdup(tokens[i]);
		i++;
	}
	cmd->args[i] = NULL;
	return cmd;
}
