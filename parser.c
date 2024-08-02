/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 02:49:24 by abdennac          #+#    #+#             */
/*   Updated: 2024/08/02 15:03:12 by abdennac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_ac(char **str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int path_check(char *s)
{
	int i;
	char str[5] = "PATH";

	i = 0;
	while (s[i] && s[i] == str[i])
		i++;
	if (i == 4)
		return (1);
	return (0);
}
char **environment(char **env)
{
	int i;
	int j;
	char **tmp;

	tmp = NULL;
	i = 0;
	while (env[i])
	{
		if (path_check(env[i]))
		{
			j = 0;
			while (env[i][j])
			{
				if (env[i][j] == '/')
				{
					tmp = pipe_split(&env[i][j], ':');
					break;
				}
				j++;
			}
		}
		i++;
	}
	return (tmp);
}
char *return_path(char **ev, char *str)
{
	int i;
	char *tmp;

	i = 0;
	while (ev[i])
	{
		tmp = ft_strjoin(ev[i], str);
		if (access(tmp, X_OK) == 0)
			return (tmp);
		free(tmp);
		i++;
	}
	return (0);
}

t_cmd *create_list(t_cmd *list, char *tokens, char **ev)
{
	int		i;
	t_cmd	*cmd;
	char	**str;
	int		ac;

	i = 0;
	str = pipe_split(tokens, ' ');
	ac = count_ac(str);
	cmd = malloc(sizeof(t_cmd));
	cmd->command = ft_strdup(str[0]);
	cmd->path = return_path(ev, cmd->command);
	cmd->arg_count = ac;
	cmd->args = malloc(sizeof(char *) * (ac + 1));
	while (i < ac)
	{
		cmd->args[i] = ft_strdup(str[i]);
		i++;
	}
	cmd->args[i] = NULL;
	ft_lstadd_back(&list, cmd);
	return (cmd);
}
