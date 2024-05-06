#include <stdio.h>
#include <string.h>

size_t  ft_strlen(const char *s)
{
  size_t	i;

  i = 0;
  while (s[i])
    i++;
  return (i);
}

void	remove_paranthesis(char **line)
{
	char	*tmp;

	tmp = *line;
	while (*tmp)
	{
		if (*tmp == '(')
		{
			*tmp = ' ';
			break ;
		}
		tmp++;
	}
	tmp = *line + ft_strlen(*line) - 1;
	while (tmp != *line)
	{
		if (*tmp == ')')
		{
			*tmp = ' ';
			break ;
		}
		tmp--;
	}
}

int main() {
  char  *line = strdup("(ls && cat)");

  remove_paranthesis(&line);
  printf("%s\n", line);
}
