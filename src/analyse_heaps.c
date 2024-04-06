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
void	set_states(t_board *board, t_board *last)
{
	int size = ft_lstsize(board);
	int i = -1;
	while (++i < size)
	{
		if ((board->objs % 4) != 1)
			board->state = W;
		else if ((board->objs % 4) != 0)
			board->state = L;
		else
			board->state = 3;
		if (board->prev != last)
		{
			if (board->prev->state == 0)
			{
				if ((board->objs % 4) != 0)
					board->state = W;
				else if ((board->objs % 4) != 1)
					board->state = L;
				else
					board->state = 3;
			}
		}
		board = board->next;
	}
}

void	bot_turn(t_board *board)
{
	int i = 0;
	// if (board->state == W)
	// {
		
	// }
	// else if (board->state == L)
	// {

	// }
	// else

	board->prev->objs -= i;
	if (board->prev->objs == 0)
	{
		delete_last_node(&board);
	}
	write(1, "AI took ", 9);
	print_digit(i);
	write(1, "\n", 1);
}

int	get_user_input(t_board *board)
{
	int i;
	while (1)
	{
		write(1, "Please choose between 1 and 3 items(don;t use characters)\n", 59);
		char *str = get_next_line(0);
		if (!str)
			return (-2);
		if (*str == '\n')
		{
			free(str);
			str = NULL;
			continue ;
		}
		i = ft_atoi(str);
		free(str);
		str = NULL;
		if (i == -1 || i < 0 || i > 3 || i > board->prev->objs)
		{
			print_digit(i); // not good for chars
			write(2, " - Invalid choice\n", 19);
		}
		else
			break ;
	}
	return (i);
}


