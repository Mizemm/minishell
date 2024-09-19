#include "../minishell.h"

int db_quotes_counter(char *str)
{
	int i;
	int qc;

	i = 0;
	qc = 0;
	while (str[i])
	{
		if (str[i] == '"')
			qc++;
		i++;
	}
	return (qc);
}

int sg_quotes_counter(char *str)
{
	int i;
	int qc;

	i = 0;
	qc = 0;
	while (str[i])
	{
		if (str[i] == 39)
			qc++;
		i++;
	}
	return (qc);
}