/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 22:55:16 by abdennac          #+#    #+#             */
/*   Updated: 2024/08/26 22:55:16 by abdennac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
