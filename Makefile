# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mizem <mizem@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/20 22:27:04 by abdennac          #+#    #+#              #
#    Updated: 2024/07/26 17:39:03 by mizem            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MINISHELL = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror

MINISHELL_C = minishell.c
UTILS_C = \
			utils/ft_isalnum.c utils/ft_lstclear_bonus.c utils/ft_strdup.c \
			utils/ft_lstsize_bonus.c utils/ft_strchr.c utils/ft_strcmp.c \
			utils/ft_strjoin.c utils/ft_split.c utils/ft_strlen.c \
			utils/ft_printf/ft_printf.c utils/ft_printf/ft_putchar.c utils/ft_printf/ft_putnbr.c \
			utils/ft_printf/ft_hex.c utils/ft_printf/ft_upperhex.c utils/ft_printf/ft_putstr.c \
			utils/ft_printf/ft_unsignednbr.c

MINISHELL_O = $(MINISHELL_C:.c=.o)
UTILS_O = $(UTILS_C:.c=.o)

all: $(MINISHELL)

$(MINISHELL): $(MINISHELL_O) $(UTILS_O) minishell.h
	$(CC) $(CFLAGS) $(MINISHELL_O) $(UTILS_O) -o minishell -lreadline

clean:
	rm -rf $(MINISHELL_O) $(UTILS_O)

fclean: clean
	rm -rf $(MINISHELL)

re: fclean all