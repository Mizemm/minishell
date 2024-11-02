/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 01:35:05 by mizem             #+#    #+#             */
/*   Updated: 2024/11/02 22:22:54 by abdennac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	path_check(char *s)
{
	int		i;
	char	str[5];

	i = 0;
	ft_strncpy(str, "PATH", 5);
	while (s[i] && s[i] == str[i])
		i++;
	if (i == 4)
		return (1);
	return (0);
}

char	**environment(t_main *main)
{
	char	**tmp;
	t_env	*env;

	env = main->env;
	tmp = NULL;
	while (env)
	{
		if (ft_strcmp(env->name, "PATH") == 0)
		{
			tmp = ft_split(env->value, ':');
			return (tmp);
		}
		env = env->next;
	}
	return (tmp);
}

char	*return_path(char **ev, char *str)
{
	int		i;
	char	*tmp;
	char	*tmp2;
	char	*slash;

	i = 0;
	if (!ev)
		return (0);
	slash = ft_strdup("/");
	while (ev[i])
	{
		tmp2 = ft_strjoin(ev[i], slash);
		tmp = ft_strjoin(tmp2, str);
		free(tmp2);
		tmp2 = NULL;
		if (access(tmp, X_OK) == 0)
			return (free(slash), tmp);
		free(tmp);
		i++;
	}
	free(slash);
	return (0);
}

void	replace_command(t_cmd *tmp_list)
{
	tmp_list->path = ft_strdup(tmp_list->command);
	tmp_list->command = path_split(tmp_list->command, '/');
	if (access(tmp_list->path, X_OK) != 0 || stat(tmp_list->path, NULL) != 0)
	{
		free(tmp_list->path);
		tmp_list->path = NULL;
	}
}
