/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 23:50:41 by abdennac          #+#    #+#             */
/*   Updated: 2024/10/31 22:29:18 by abdennac         ###   ########.fr       */
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

char	**get_file_names(char **files, int nb_files)
{
	int		i;
	char	*nb;
	
	i = -1;
	files = malloc(sizeof(char *) * (nb_files + 1));
	while (++i < nb_files)
	{
		nb = ft_itoa(i);
		files[i] = ft_strjoin("/tmp/heredoc", nb);
		free(nb);
	}
	files[i] = NULL;
	return (files);
}

char	**make_file_name(t_cmd *cmd)
{
	char	**files;
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
	files = NULL;
	files = get_file_names(files, nb_files);
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

void	close_fds(t_main *main, int *prev_pipe_fd)
{
	if (prev_pipe_fd[0] != -1)
	{
		close(prev_pipe_fd[0]);
		close(prev_pipe_fd[1]);
	}
	if (main->cmd->stdin_backup != -1)
	{
		dup2(main->cmd->stdin_backup, STDIN_FILENO);
		close(main->cmd->stdin_backup);
	}
	if (main->cmd->stdout_backup != -1)
	{
		dup2(main->cmd->stdout_backup, STDOUT_FILENO);
		close(main->cmd->stdout_backup);
	}
}
