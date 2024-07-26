/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 02:49:24 by abdennac          #+#    #+#             */
/*   Updated: 2024/07/26 14:27:31 by mizem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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

t_cmd *create_list(char **tokens, int start, int end)
{
	t_cmd *cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->command = ft_strdup(tokens[start]);
	// cmd->path = ;
	cmd->args = malloc(sizeof(char *) * en)
	
}