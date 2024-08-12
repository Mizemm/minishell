#include "../minishell.h"

int	check_if_builtin(char *str)
{
	if (ft_strcmp("echo", str) == 0)
		return (0);
	if (ft_strcmp("cd", str) == 0)
		return (0);
	if (ft_strcmp("pwd", str) == 0)
		return (0);
	if (ft_strcmp("export", str) == 0)
		return (0);
	if (ft_strcmp("unset", str) == 0)
		return (0);
	if (ft_strcmp("env", str) == 0)
		return (0);
	if (ft_strcmp("exit", str) == 0)
		return (0);
	return (1);
}

int check_flag(char *str)
{
    int i;

    if (!str)
        return (0);
    if (str[0] != '-' || str[1] != 'n')
        return (0);
    i = 1;
    while (str[i] != '\0')
    {
        if (str[i] != 'n')
            return (0);
        i++;
    }
    return (1);
}

void exec_echo(t_cmd *cmd, int if_exit) //ba9i fiha chi l3ibat
{
    int i = 0;
    int flag_n = 0;

    while (++i < cmd->arg_count && check_flag(cmd->args[i]))
        flag_n = 1;
    // Print argument, separated by space.
    while (i < cmd->arg_count)
    {
        printf("%s", cmd->args[i]);
        if (i < cmd->arg_count - 1)
            printf("%c", ' ');
        i++;
    }
    // Print a newline if the -n flag was not used.
    if (!flag_n)
            printf("%c", '\n');

    if (if_exit)
    {
        
    }
}
