#include "alcu.h"

// TODO
void	announce_the_winner(void)
{
	write(1, "You are the winner! Congratulations!\n", 37);
	write(1, "The AI is the winner! Better luck next time!\n", 45);
}

int	run_game(t_board *board)
{
	while (board)
	{
		print_board(board);
		set_states(board, board->prev);
		bot_turn(board);
		print_board(board);
		int i = get_user_input(board);
		if (i == -2)
			return (1);
		board->prev->objs -= i;
		if (board->prev->objs == 0)
		{
			delete_last_node(&board);
		}
	}
	return (0);
}

int main(int ac, char **av)
{
	t_board *board = NULL;

	if (ac == 1)
	{
		if (read_f(&board) != 0)
		{
			// free_list(board, board->prev);
			return (1);
		}
	}
	else if (ac == 2)
	{
		if (open_read_file(&board, av[1]) != 0)
		{
			// free_list(board, board->prev);
			return (1);
		}
	}
	else
		return (write(2, "Error\n", 6));
	if (run_game(board) != 0)
	{
		// free_list(board, board->prev);
		return (1);
	}
	announce_the_winner();
	return (0);
}
