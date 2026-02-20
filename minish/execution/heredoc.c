/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 13:47:36 by abdennac          #+#    #+#             */
/*   Updated: 2024/10/31 01:30:12 by abdennac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	heredoc_loop_1(t_main *main, t_cmd *cmd, int fd, int j)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, (cmd->heredoc_delimiter[j])) == 0)
			break ;
		if (dollar_count(line) > 0 && cmd->herdoc_flag == 0)
			line = her_expand(line, main);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	free(line);
}

void	handle_piped_heredoc(t_main *main, t_cmd *cmd)
{
	t_cmd	*tmp;
	int		fd;
	int		i;
	int		j;

	tmp = cmd;
	i = 0;
	while (tmp)
	{
		if (tmp->heredoc_delimiter)
		{
			j = -1;
			while (tmp->heredoc_delimiter[++j])
			{
				if (!main->heredoc_files[i])
					break ;
				fd = open(main->heredoc_files[i], O_WRONLY | O_CREAT | O_TRUNC,
						0644);
				heredoc_loop_1(main, tmp, fd, j);
			}
			i++;
		}
		tmp = tmp->next;
	}
}

void	handle_simple_heredoc(t_cmd *cmd, t_main *main)
{
	int		fd;
	int		j;

	j = -1;
	if (cmd->heredoc_delimiter)
	{
		while (cmd->heredoc_delimiter[++j])
		{
			fd = open("/tmp/heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
			heredoc_loop_1(main, cmd, fd, j);
		}
	}
}

void	heredoc_helper(t_main *main)
{
	main->exit_status = 1;
	g_signal = 1;
	if (main->heredoc_files)
	{
		while (main->heredoc_files[++main->cmd->her_index])
			unlink(main->heredoc_files[main->cmd->her_index]);
	}
}

void	handle_heredoc(t_main *main)
{
	int	pid;
	int	status;

	signal(SIGINT, SIG_IGN);
	main->heredoc_files = make_file_name(main->cmd);
	pid = fork();
	if (pid == 0)
	{
		handle_herdoc_signal();
		if (!main->cmd->next)
			handle_simple_heredoc(main->cmd, main);
		else
			handle_piped_heredoc(main, main->cmd);
		exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
		handle_signals();
		if (WIFSIGNALED(status))
			heredoc_helper(main);
	}
}
