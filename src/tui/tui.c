/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:33:17 by astavrop          #+#    #+#             */
/*   Updated: 2024/04/06 18:32:32 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/tui.h"

#include <ncurses.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h> /* WARN: DEL*/
#include <stdlib.h>

size_t	ft_strlen(const char *str)
{
	const char *s;
	for (s = str; *s; ++s);
	return(s - str);
}

int	ft_dputs(int fd, const char *str)
{
	for (int i = 0; str[i]; i++)
		write(fd, &str[i], 1);
	return (ft_strlen(str));
}

TUI	*tui_init(void)
{
	TUI	*tui = malloc(sizeof(TUI));
	
	if (!tui)
	{
		ft_dputs(1, "TUI mem allocation failed\n");
		exit(1);
	}
	initscr();
	cbreak();
	noecho();
	curs_set(0);
	keypad(stdscr, TRUE);

	int height, width;
	getmaxyx(stdscr, height, width);

	tui->wbody = newwin(height, width, 0, 0);
	box(stdscr, 0, 0);
	keypad(tui->wbody, TRUE);
	refresh();

	tui->board_height = height - 10;
	tui->board_y = 5;
	tui->board_x = 0;
	tui->cur_heap = 0;
	return (tui);
}

size_t	get_board_len(int *board)
{
	size_t	len = 0;
	while (board[len] >= 0)
		len++;
	return (len);
}

void	print_header(TUI *tui, const char *text)
{
	int x, y;
	getmaxyx(tui->wbody, y, x); // Get the dimensions of the window
    mvwprintw(tui->wbody, 1, (x - ft_strlen(text))/2, "%s", text); // Print the text in the upper middle of the window
	wrefresh(tui->wbody); // Refresh the window
}

void	print_heap(TUI *tui, int heap, int heap_len)
{
	int	y = tui->board_y + heap - tui->cur_heap;
	wmove(tui->wbody, y, tui->board_x);
	wprintw(tui->wbody, "> %d :", heap);

	int	height, width;
	getmaxyx(tui->wbody, height, width);
	int		x_limit = width - tui->board_x - 15;
	char	string_heap[heap_len];
	for (int i = 0; i < heap_len && i <= x_limit; i++)
	{
		string_heap[i] = '|';
	}
	string_heap[heap_len] = '\0';
	char	end = ' ';
	if (heap_len > x_limit)
	{
		end = '+';
		string_heap[x_limit] = '\0';
	}
	wmove(tui->wbody, y, tui->board_x + 7);
	wprintw(tui->wbody, "%s%c", string_heap, end);
}

void	draw_board(TUI *tui, int *board)
{
	print_header(tui, "<<<  THE GREAT NIM  >>>");

	int	blen = get_board_len(board);
	for (int h = tui->cur_heap;
			h - tui->cur_heap < tui->board_height
			&& h < blen
			; h++)
	{
		print_heap(tui, h, board[h]);
		wrefresh(tui->wbody);
	}
}

/*
int	process_input(TUI *tui)
{
	int	ret = 0;
	int	key;
	key = getch();
}
*/

int	main(void)
{
	int		board[] = {
		1000, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 13, 14, 15, 16, 17, 18, 19, 20,
		21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
		1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 13, 14, 15, 16, 17, 18, 19, 20,
		21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
		-42
	};
	TUI		*tui = tui_init();
	int		key;
	bool	run = true;
	while (run)
	{
		werase(tui->wbody);
		draw_board(tui, board);
		key = wgetch(tui->wbody);
		switch (key)
		{
			case KEY_DOWN:
				if (tui->cur_heap + tui->board_height < (int) get_board_len(board))
					tui->cur_heap++;
				break;
			case KEY_UP:
				if (tui->cur_heap > 0)
					tui->cur_heap--;
				break;
			case 'q':
			case KEY_EXIT:
				run = false;
				break;
			default:
				break;
		}
	}
	delwin(tui->wbody);
	endwin();
	return (0);
}
