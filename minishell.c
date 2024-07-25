/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 21:23:49 by mizem             #+#    #+#             */
/*   Updated: 2024/07/24 19:05:21 by abdennac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_strchr2(char *s)
{
	int i = 0;
	char str[5] = "PATH";
	while (s[i] && s[i] == str[i])
		i++;
	if (i == 4)
		return 1;
	return 0;
}

char **enviromnt(char **env)
{
	int i;
	int j;
	char **tmp = NULL;

	i = 0;
	j = 0;
	while (env[i])
	{
		if (ft_strchr2(env[i]))
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

int main(int ac, char **av, char **env)
{
	char *line;

	char **tmp;
	(void)av;
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