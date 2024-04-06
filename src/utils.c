#include "alcu.h"

void print_board(t_board *board)
{
	t_board *cur = board;
	int max = 30; // tried to print in the midle of line | TODO find_max
	int size = ft_lstsize(board);
	int i = 0;
	while (i < size)
	{
		int offset = (max - cur->objs) / 2;
		for (int m = 0; m < offset; m++)
			write(1, "   ", 2);
		for (int j = 0; j < cur->objs; j++) {
				write(1, " | ", 2);
	 	}
		for (int n = 0; n < ((max - cur->objs) / 2); n++)
			write(1, "  ", 2);
		write (1, "\n", 1);
		cur = cur->next;
		i++;
	}
}

size_t	ft_arrsize(char	**arr)
{
	size_t	size;

	size = 0;
	while (arr[size])
		size++;
	return (size);
}

void	print_arr(char **arr)
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
	if (n >= 10)
		count += print_digit(n / 10);
	n = symbols[n % 10];
	count += write(1, &n, 1);
	return (count);
}

char	*ft_strdup(const char *src)
{
	char			*s;
	unsigned int	i;

	s = (char *)malloc(sizeof(char) * ft_strlen(src) + 1);
	if (!s)
		return (NULL);
	i = 0;
	while (src[i])
	{
		s[i] = src[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

int	ft_isdigit(int c)
{
	if (c > 47 && c < 58)
		return (1);
	return (0);
}

// int	ft_atoi(const char *str)
// {
// 	int		sign;
// 	size_t	total;

// 	sign = 1;
// 	total = 0;
// 	while ((*str != '\n' || *str != '\0') && (*str == 32 || (*str >= 9 && *str <= 13)))
// 		str++;
// 	if (*str == '-')
// 	{
// 		sign = -1;
// 		str++;
// 	}
// 	else if (*str == '+')
// 		str++;
// 	while (*str != '\n' || *str != '\0')
// 	{
// 		if (!(ft_isdigit(*str)))
// 			return (-1);
// 		total *= 10;
// 		total += (*str - '0');
// 		str++;
// 	}
// 	if ((total * sign) < 1 || (total * sign) > 10000)
// 		return (-1);
// 	return (total * sign);
// }

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
	while (*str != '\n')
	{
		if (!ft_isdigit(*str))
			return (-1);
		total *= 10;
		total += (*str - '0');
		str++;
	}
	if ((total * sign) < 1 || (total * sign) > 10000)
		return (-1);
	return (total * sign);
}
