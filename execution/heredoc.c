/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 13:47:36 by abdennac          #+#    #+#             */
/*   Updated: 2024/10/13 23:10:24 by abdennac         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../minishell.h"

char **make_file_name(t_cmd *cmd)
{
	char *file_name;
	char **files;
	int i;
	t_cmd *tmp;
	int nb_files;

	nb_files = 0;
	tmp = cmd;
	while (tmp)
	{
		if (tmp->heredoc_delimiter)
			nb_files++;
		tmp = tmp->next;
	}
	if (nb_files == 0)
		return NULL;
	files = malloc(sizeof(char *) * (nb_files + 1));
	file_name = "/tmp/heredoc";

	i = -1;
	while (++i < nb_files)
		files[i] = ft_strjoin(file_name, ft_itoa(i));
	files[i] = NULL;
	return files;
}

void handle_piped_heredoc(t_main *main, t_cmd *cmd)
{
	t_cmd *tmp;
	char *line;
	int fd;
	int i;
	int j;

	main->heredoc_files = make_file_name(cmd);
	i = -1;
	while (main->heredoc_files[++i])
		printf("%s\n", main->heredoc_files[i]);
	
	tmp = cmd;
	i = -1;
	while (tmp)
	{
		if (tmp->heredoc_delimiter)
		{
			j = -1;
			while (tmp->heredoc_delimiter[++j])
			{
				fd = open(main->heredoc_files[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
				while (1)
				{
					line = readline("> ");
					if (!line)
						break;
					// if (line[0] == '$')
					// line = expand;
					if (ft_strcmp(line, (tmp->heredoc_delimiter[j])) == 0)
						break;
					write(fd, line, ft_strlen(line));
					write(fd, "\n", 1);
					free(line);
				}
				close(fd);
				free(line);
				i++;
			}
		}
		tmp = tmp->next;
	}
}

void handle_simple_heredoc(t_cmd *cmd)
{
	char *line;
	int fd;
	int i;
	int j;

	j = -1;
	if (cmd->heredoc_delimiter)
	{
		while (cmd->heredoc_delimiter[++j])
		{
			fd = open("/tmp/heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
			while (1)
			{
				line = readline("> ");
				if (!line)
					break;
				// if (line[0] == '$')
				// line = expand;
				if (ft_strcmp(line, (cmd->heredoc_delimiter[j])) == 0)
					break;
				write(fd, line, ft_strlen(line));
				write(fd, "\n", 1);
				free(line);
			}
			close(fd);
			free(line);
		}
	}
}

void handle_heredoc(t_main *main)
{
	if (!main->cmd->next)
		handle_simple_heredoc(main->cmd);
	else
		handle_piped_heredoc(main, main->cmd);
}
