#include "alcu.h"

int read_stdin(t_board **board)
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
		if (isdigit_str(line))
			nbr = ft_atoi(line);
		else
			nbr = -1;
		tmp = line;
		free(tmp);
		tmp = NULL;
		if (nbr == -1 || out_range(nbr, 1, 10000))
		{
			int fd = open("/dev/null", O_RDONLY);
			get_next_line(fd);
			close(fd);
			return (write(2, "ERROR\n", 6));
		}
		ft_add_back(board, ft_lstnew(nbr));
	}
	return (0);
}

int open_read_file(t_board **board, char *file)
{
	char *line = NULL;
	char *tmp = NULL;
	int nbr = 0;
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
		if (isdigit_str(line))
			nbr = ft_atoi(line);
		else
			nbr = -1;
		tmp = line;
		free(tmp);
		tmp = NULL;
		if (nbr == -1 || nbr == -1 || out_range(nbr, 1, 10000))
		{
			close (fd);
			fd = open("/dev/null", O_RDONLY);
			get_next_line(fd);
			close(fd);
			free(line);
			return (write(2, "ERROR\n", 6));
		}
		ft_add_back(board, ft_lstnew(nbr));
	}
	return (0);
}

