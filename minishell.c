/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 21:23:49 by mizem             #+#    #+#             */
/*   Updated: 2024/07/22 17:39:07 by abdennac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_strchr(char *s)
{
	int i = 0;
	char str[4] = "PATH";
	while (s[i] && s[i] == str[i])
		i++;
	if (i == 4)
		return 1;
	return 0;
}
char **enviroment(char **env)
{
	int i;
	int j;

	i = 0;
	j = 0;
	char **tmp;
	while (env[i])
	{
		if (ft_strchr(env[i]))
		{
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
int main(int ac, char **av, char **env)
{
	// char *line;

	char **tmp;
	(void)av;
	if (ac < 1)
		exit(1);
	tmp = enviroment(env);
	while (*tmp)
	{
		printf("%s\n", *tmp);
		tmp++;
	}
	// while (1)
	// {
	// 	line = readline("minishell $ ");
	// 	if (!line)
	// 		break;
	// 	if (*line)
	// 	{
	// 		printf("%s\n", line);
	// 		free(line);
	// 	}
	// }
}