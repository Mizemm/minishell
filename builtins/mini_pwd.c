#include "../minishell.h"

void excec_pwd(void)
{
    char *cwd;

    cwd = NULL;
    cwd = getcwd(cwd, 0);
    if (!cwd)
        error("pwd error");
    printf("%s\n", cwd);
}
