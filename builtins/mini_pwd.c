/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 22:55:16 by abdennac          #+#    #+#             */
/*   Updated: 2024/10/17 00:52:41 by abdennac         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../minishell.h"

int excec_pwd(void)
{
    char *cwd;

    cwd = NULL;
    cwd = getcwd(cwd, 0);
    if (!cwd)
        return(error("pwd error"), 1);
    printf("%s\n", cwd);
    free(cwd);
    return (0);
}
