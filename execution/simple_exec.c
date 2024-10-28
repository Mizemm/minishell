/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:10:51 by abdennac          #+#    #+#             */
/*   Updated: 2024/10/28 05:36:38 by abdennac         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../minishell.h"

void simple_input(t_cmd *cmd)
{
	int fd_in;
	int i;

	if (cmd->heredoc_delimiter)
	{
		fd_in = open("/tmp/heredoc", O_RDONLY);
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}

	if (cmd->input_file)
	{
		i = -1;
		while (cmd->input_file[++i])
			fd_in = open(cmd->input_file[i], O_RDONLY);
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
}

void simple_output(t_cmd *cmd)
{
	int fd_out;
	int i;

	if (cmd->output_file)
	{
		i = -1;
		while (cmd->output_file[++i])
			fd_out = open((cmd->output_file[i]), O_WRONLY | O_CREAT, 0644);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	else if (cmd->append_file)
	{
		i = -1;
		while (cmd->append_file[++i])
			fd_out = open((cmd->append_file[i]), O_WRONLY | O_CREAT | O_APPEND, 0644);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
}

void simple_cleanup(t_cmd *cmd)
{
	if (cmd->heredoc_delimiter)
		unlink("/tmp/heredoc");
	if (cmd->stdin_backup != -1)
	{
		dup2(cmd->stdin_backup, STDIN_FILENO);
		close(cmd->stdin_backup);
	}
	if (cmd->stdout_backup != -1)
	{
		dup2(cmd->stdout_backup, STDOUT_FILENO);
		close(cmd->stdout_backup);
	}
}
char *path_split(char *str, char c)
{
	int i;
	char *tmp;

	i = 0;
	while (str[i])
		i++;
	while (i >= 0 && str[i] != c)
		i--;
	tmp = ft_strdup(str + i + 1);
	free(str);
	return (tmp);
}

void fix_path(t_cmd *cmd)
{
	if (ft_strchr(cmd->command, '/'))
	{
		cmd->path = ft_strdup(cmd->command);
		cmd->command = path_split(cmd->command, '/');
	}
	else
	{
		cmd->path = getcwd(cmd->path, 0);
		cmd->path = ft_strjoin(cmd->path, "/");
		cmd->path = ft_strjoin(cmd->path, cmd->command);
	}
}

void find_path(t_main *main, t_cmd *cmd)
{
	t_env *tmp;
	int i = 0;
	tmp = main->env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "PATH") == 0)
			i = 1;
		tmp = tmp->next;
	}
	if (i == 1)
	{
		fix_path(cmd);
		if (access(cmd->path, X_OK) != 0)
			error2(main, "Command not found", 127);
	}
	else
	{
		fix_path(cmd);
		if (access(cmd->path, F_OK) != 0)
			error2(main, "no such file or directory", 127);
		if (access(cmd->path, X_OK) != 0)
			error2(main, "permission denied", 126);
	}
}

void simple_exec(t_main *main)
{
	pid_t pid;
	int status;

	if (check_if_builtin(main->cmd->command))
	{
		simple_input(main->cmd);
		simple_output(main->cmd);
		execute_builtins(main, main->cmd);
		simple_cleanup(main->cmd);
	}
	else
	{
		pid = fork();
		if (pid < 0)
			error2(main, "fork error", 1);
		else if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			simple_input(main->cmd);
			simple_output(main->cmd);
			if (!main->cmd->path)
				find_path(main, main->cmd);
		// dprintf(2, "path: %s\n", main->cmd->path);
				
			execve(main->cmd->path, main->cmd->args, main->full_env);
		}
		else
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				status = 128 + WTERMSIG(status);
			main->exit_status = status;
		}
	}
	if (main->cmd->heredoc_delimiter)
		unlink("/tmp/heredoc");
}
