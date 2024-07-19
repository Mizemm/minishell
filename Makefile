MINISHELL = minishell
CC = cc
CFLAGS = -Wall -Wextra  -Werror

MINISHELL_C = 
UTILS_C =

MINISHELL_O = $(MINISHELL_C:.c=.o)
UTILS_O = $(UTILS_C:.c=.o)

all: $(MINISHELL)

$(MINISHELL): $(MINISHELL_O) minitalk.h
	$(CC) $(CFLAGS) $(MINISHELL_O) $(UTILS_O) -o minishell

clean:
	rm -rf $(MINISHELL_O) $(UTILS_O)
fclean: clean
	rn -rf $(MINISHELL)
re: fclean all