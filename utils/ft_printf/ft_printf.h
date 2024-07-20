/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 16:15:20 by mizem             #+#    #+#             */
/*   Updated: 2024/02/13 11:08:07 by mizem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int	ft_putchar(int c);
int	ft_putnbr(int n);
int	ft_putnbr(int n);
int	ft_putstr(char *s);
int	ft_unsignednbr(unsigned int n);
int	ft_hex(unsigned long int x);
int	ft_upperhex(unsigned long int x);
int	ft_printf(const char *str, ...);

#endif