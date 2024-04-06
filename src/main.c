/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 20:33:17 by ohladkov          #+#    #+#             */
/*   Updated: 2024/04/07 00:02:00 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alcu.h"
#include "tui.h"

# ifndef WITH_BONUS
#  define WITH_BONUS 0
# endif

int g_winner = 0;

void	copy_board(int arr[], t_board *board)
{
	t_board *tmp = board;
	int size = ft_lstsize(board);
	int k = 0;
	while (k < size)
	{
		arr[k] = tmp->objs;
		tmp = tmp->next;
		k++;
	}
	arr[k] = -1;
}

void	announce_the_winner(void)
{
	if (g_winner == 1)
		write(1, "You are the winner! Congratulations!\n", 37);
	else
		write(1, "The AI is the winner! Better luck next time!\n", 45);
}

int	run_game(t_board *board)
{
	while (board)
	{
		print_board(board);
		set_states(board);
		bot_turn(&board, NULL);
		print_board(board);
		int i = get_user_input(board);
		if (i == -2)
			return (1);
		else 
		if (i == -1)
			return (0);
		board->prev->objs -= i;
		if (board->prev->objs == 0)
		{
			g_winner = 0;
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
		if (read_stdin(&board) != 0)
		{
			if (board)
				free_list(board, board->prev);
			return (1);
		}
	}
	else if (ac == 2)
	{
		if (open_read_file(&board, av[1]) != 0)
		{
			if (board)
				free_list(board, board->prev);
			return (1);
		}
	}
	else
		return (write(2, "Error\n", 6));
	if (!board)
		return (write(2, "ERROR\n", 6));
	if (WITH_BONUS == 0)
	{
		if (run_game(board) != 0)
		{
			if (board)
				free_list(board, board->prev);
			return (1);
		}
		announce_the_winner();
	}
	else if (WITH_BONUS == 1)
	{
		int		tui_board[ft_lstsize(board)];
		TUI		*tui = tui_init();
		int		key;
		bool	run = true;
		int		blen;
		while (run)
		{
			if (tui->move % 2 != 0)
			{
				copy_board(tui_board, board);
				blen = (int) get_board_len(tui_board);
				if (blen > 0)
					tui->move++;
				set_states(board);
				bot_turn(&board, tui);
			}
			copy_board(tui_board, board);
			blen = (int) get_board_len(tui_board);
			werase(tui->wbody);
			draw_board(tui, tui_board);
			print_options(tui, tui_board[blen - 1]);
			key = wgetch(tui->wbody);
			int num;
			switch (key)
			{
				case KEY_DOWN:
					if (tui->cur_heap + tui->board_height < blen)
						tui->cur_heap++;
					break;
				case KEY_UP:
					if (tui->cur_heap > 0)
						tui->cur_heap--;
					break;
				case '1':
				case '2':
				case '3':
					if (tui->move % 2 == 0)
					{
						num = key - '0';
						if (num < 1 || num > tui_board[blen - 1])
							break;
						board->prev->objs -= num;
						if (board->prev->objs == 0)
						{
							g_winner = 0;
							delete_last_node(&board);
						}
						tui->move++;
					}
					break;
				case 'q':
				case 27:
					run = false;
					break;
				default:
					break;
			}
		}
		delwin(tui->wbody);
		endwin();
	}
	return (0);
}
