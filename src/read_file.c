#include "alcu.h"

int read_f(t_board **board)
{
	char *line = NULL;
	char *tmp = NULL;
	int nbr;
	int n = 0;

	while (1)
	{
		line = get_next_line(0);
		if (!line)
		{
			if (n == 0)
				return (write(2, "ERROR\n", 6));
			break ;
		}
		if (*line == '\n')
		{
			n = 1;
			tmp = line;
			free(tmp);
			tmp = NULL;
			continue ;
		}
		n = 0;
		nbr = ft_atoi(line);
		if (nbr == -1)
			return (write(2, "ERROR\n", 6));
		ft_add_back(board, ft_lstnew(nbr));
		tmp = line;
		free(tmp);
		tmp = NULL;
	}
	return (0);
}

int open_read_file(t_board **board, char *file)
{
	char *line = NULL;
	char *tmp = NULL;
	int nbr;
	int	n = 0;
	int fd = open(file, O_RDONLY);

	if (fd == -1)
		return (write(2, "Error opening file\n", 19));
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
		{
			if (n == 0)
				return (write(2, "ERROR\n", 6));
			break ;
		}
		if (*line == '\n')
		{
			n = 1;
			tmp = line;
			free(tmp);
			tmp = NULL;
			continue ;
		}
		n = 0;
		nbr = ft_atoi(line);
		if (nbr == -1)
		{
			close (fd);
			return (write(2, "ERROR\n", 6));
		}
		ft_add_back(board, ft_lstnew(nbr));
		tmp = line;
		free(tmp);
		tmp = NULL;
	}
	return (0);
}

