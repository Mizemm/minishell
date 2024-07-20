MINISHELL = minishell
CC = cc
CFLAGS = -Wall -Wextra  -Werror

MINISHELL_C = minishell.c
UTILS_C = utils/ft_split.c utils/ft_strncpy.c utils/ft_printf/ft_printf.c utils/ft_printf/ft_putchar.c utils/ft_printf/ft_putnbr.c utils/ft_printf/ft_hex.c utils/ft_printf/ft_upperhex.c utils/ft_printf/ft_putstr.c utils/ft_printf/ft_unsignednbr.c

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