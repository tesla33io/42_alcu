#include "alcu.h"

void print_board(t_board *board)
{
	t_board *cur = board;
	int max = get_max(board);
	int size = ft_lstsize(board);
	int i = 0;
	while (i < size)
	{
		int offset = ((max - cur->objs));
		for (int m = 0; m <= offset; m++)
			write(1, " ", 1);
		for (int j = 0; j < cur->objs; j++)
			write(1, "| ", 2);
		write (1, "\n", 1);
		cur = cur->next;
		i++;
	}
}

int	get_max(t_board *board)
{
	int		max = 0;
	int		size = ft_lstsize(board);

	while (size)
	{
		if (board->objs > max)
			max = board->objs;
		board = board->next;
		size--;
	}
	return (max);
}

size_t	ft_arrsize(char	**arr)
{
	size_t	size;

	size = 0;
	while (arr[size])
		size++;
	return (size);
}

void	print_arr(char **arr) //rem
{
	int	i;

	if (!arr || !*arr)
		write(1, "no array\n", 9);
	i = 0;
	while (arr[i])
	{
		printf("%s", arr[i]);
		i++;
	}
}

int	print_digit(int n)
{
	int			count;
	const char	*symbols;

	count = 0;
	symbols = "0123456789";
	if (n < 0)
	{
		return (0);
	}
	if (n >= 10)
		count += print_digit(n / 10);
	n = symbols[n % 10];
	count += write(1, &n, 1);
	return (count);
}

int	ft_isdigit(int c)
{
	if (c > 47 && c < 58)
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int		sign;
	size_t	total;

	sign = 1;
	total = 0;
	while (*str != '\0' && (*str == 32 || (*str >= 9 && *str <= 13)))
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (ft_isdigit(*str))
	{
		total *= 10;
		total += (*str - '0');
		str++;
	}
	return (total * sign);
}

int	isdigit_str(char *s)
{
	int	j;

	j = 0;
	if (s[j] == 43 || s[j] == 45)
	{
		j++;
		while (s[j] != '\n')
		{
			if (ft_isdigit(s[j]) == 0)
				return (0);
			j++;
		}
	}
	else
	{
		while (s[j] != '\n')
		{
			if (ft_isdigit(s[j]) == 0)
				return (0);
			j++;
		}
	}
	return (1);
}

int	out_range(int nbr, int min, int max)
{
	if (nbr < min || nbr > max)
		return (-1);
	return (0);
}

void	ft_putnbr_fd(int n, int fd)
{
	int	num;

	num = 0;
	if (n < 0)
	{
		num = -(n % 10);
		n = -(n / 10);
		write(fd, "-", 1);
	}
	else
	{
		num = n % 10;
		n = n / 10;
	}
	if (n > 0)
	{
		ft_putnbr_fd(n, fd);
	}
	num += 48;
	write(fd, &num, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	while (*s && *s != '\n')
		write(fd, s++, 1);
}
