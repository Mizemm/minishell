/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 23:50:41 by abdennac          #+#    #+#             */
/*   Updated: 2024/10/30 23:52:25 by abdennac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error2(t_main *main, char *str, int status)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	main->exit_status = status;
	exit(status);
}

char	**make_file_name(t_cmd *cmd)
{
	char	*file_name;
	char	**files;
	int		i;
	t_cmd	*tmp;
	int		nb_files;

	nb_files = 0;
	tmp = cmd;
	while (tmp)
	{
		if (tmp->heredoc_delimiter)
			nb_files++;
		tmp = tmp->next;
	}
	if (nb_files == 0)
		return (NULL);
	files = malloc(sizeof(char *) * (nb_files + 1));
	file_name = "/tmp/heredoc";
	i = -1;
	while (++i < nb_files)
		files[i] = ft_strjoin(file_name, ft_itoa(i));
	files[i] = NULL;
	return (files);
}

int	dollar_count(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '$')
			count++;
		i++;
	}
	return (count);
}
