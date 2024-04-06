/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse_heaps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 20:33:23 by ohladkov          #+#    #+#             */
/*   Updated: 2024/04/06 21:03:11 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alcu.h"

/*
- For heaps in a winning state (W), 'AI' should start first.
- For heaps in a losing state (L), 'AI' should start second.
- Heap analysis starts from the top.
- The winning state of the first heap is determined by len(heap) % 4 != 1.
- Subsequent heap states depend on the state of the previous heap:
  - If the current heap is winning (W), all heaps below it are winning if len(heap_n) % 4 != 1.
  - If the current heap is losing (L), all heaps below it are winning if len(heap_n) % 4 != 0.
*/

// assume previous is in W state, then check if previous in L
void	set_states(t_board *board)
{
	int size = ft_lstsize(board);
	int i = 0;
	while (i < size)
	{
		if ((board->objs % 4) != 1) //(board->objs % 4) != 0 && 
			board->state = W;
		if ((board->objs % 4) == 1 && (board->objs % 4) != 0)
			board->state = L;
		if (board->prev != board->next)
		{
			if (board->prev->state == 0)
			{
				if ((board->objs % 4) != 0) // && (board->objs % 4) == 1
					board->state = W;
				else if ((board->objs % 4) != 1)
					board->state = L;
			}
		}
		// print_digit(board->state);//rem
		// write(1, " ", 1); //rem
		board = board->next;
		i++;
	}
	// write(1, "\n", 1); //rem
}

void	bot_turn(t_board **board)
{
	t_board *tmp = *board;
	int i = 0;
	if (!board)
		return ;
	if (tmp->prev->prev->state == L && ((*board) != (*board)->prev))
		i = take_last(tmp->prev->objs);
	else if (tmp->prev->prev->state == W && ((*board) != (*board)->prev))
		i = leave_last(tmp->prev->objs);
	else
		i = leave_last(tmp->prev->objs);
	tmp->prev->objs -= i;
	if (tmp->prev->objs == 0)
	{
		g_winner = 1;
		delete_last_node(board);
	}
	write(1, "AI took ", 9);
	print_digit(i);
	write(1, "\n", 1);
}

int	take_last(int items)
{
	int nbr;
	int rem = items % 4;

	if (rem == 0)
		nbr = 1; //?
	else if (rem == items)
		nbr = rem;
	else
		nbr = rem;
	return (nbr);
}

int	leave_last(int items)
{
	int nbr = 0;
	int rem = items % 4;

	if (rem == 0)
		nbr = 3; //?
	else if (rem == 1)
		nbr = 1;
	else if (rem != 1)
		nbr = rem - 1;
	return (nbr);
}

int	get_user_input(t_board *board)
{
	int i = -1;
	char *str = NULL;
	int terminal_fd = open("/dev/tty", O_RDWR);
	if (terminal_fd == -1) {
        perror("open");
        return (-2);
    }
	if (!board)
		return (-1);
	while (1)
	{
		write(terminal_fd, "Please choose between 1 and 3 items\n", 36);
		str = get_next_line(terminal_fd);
		if (!str)
		{
			close(terminal_fd);
			return (-2);
		}
		if (*str == '\n')
		{
			free(str);
			str = NULL;
			continue ;
		}
		if (isdigit_str(str))
			i = ft_atoi(str);
		else
		{
			i = -1;
			ft_putstr_fd(str, 2);
			write(2, " - Invalid choice\n", 19);
		}
		free(str);
		str = NULL;
		if (i == -1 || out_range(i, 1, 3) || i > board->prev->objs)
		{
			if (print_digit(i) != 0)
				write(2, " - Invalid choice\n", 19);
		}
		else
		{
			int fd = open("/dev/null", O_RDONLY);
			get_next_line(fd);
			close(fd);
			close(terminal_fd);
			break ;
		}
	}
	close(terminal_fd);
	return (i);
}
