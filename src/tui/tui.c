/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:33:17 by astavrop          #+#    #+#             */
/*   Updated: 2024/04/07 14:58:57 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/tui.h"

#include <ncurses.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <locale.h>

size_t	ft_tui_strlen(const char *str)
{
	const char *s;
	for (s = str; *s; ++s);
	return(s - str);
}

int	ft_dputs(int fd, const char *str)
{
	for (int i = 0; str[i]; i++)
		write(fd, &str[i], 1);
	return (ft_tui_strlen(str));
}

TUI	*tui_init(void)
{
	TUI	*tui = malloc(sizeof(TUI));
	
	if (!tui)
	{
		ft_dputs(1, "TUI mem allocation failed\n");
		return (NULL);
	}
	setlocale(LC_ALL, "");
	initscr();
	start_color();
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

	tui->board_height = height - 20;
	tui->board_y = 5;
	tui->board_x = 0;
	tui->cur_heap = 0;
	tui->move = 1;

	init_pair(1, COLOR_YELLOW, COLOR_BLACK); // Highlight color
	init_pair(2, -1, COLOR_BLACK); // Normal color
	return (tui);
}

size_t	get_board_len(int *board)
{
	size_t	len = 0;
	while (board[len] >= 0)
		len++;
	return (len);
}

void	print_header(TUI *tui, const char *text, int y_pos)
{
	int x, y;
	getmaxyx(tui->wbody, y, x);
	mvwprintw(tui->wbody, y_pos, (x - ft_tui_strlen(text))/2, "%s", text);
	wrefresh(tui->wbody);
}

void	print_move(TUI *tui, int move, int y_pos)
{
	int x, y;
	getmaxyx(tui->wbody, y, x);
	mvwprintw(tui->wbody, y_pos, (x - ft_tui_strlen("Move:   "))/2, "Move: %d", move);
	wrefresh(tui->wbody);
}

void	print_ai_move(TUI *tui, int y_pos)
{
	int x, y;
	getmaxyx(tui->wbody, y, x);
	mvwprintw(tui->wbody, y_pos,
		(x - ft_tui_strlen("AI took   "))/2, "AI took %d", tui->last_ai_move); 
	wrefresh(tui->wbody);
}

void	print_result(TUI *tui)
{
	int	height, width;
	getmaxyx(tui->wbody, height, width);
	if (height >= 30 && width >= 90)
	{
		if (tui->move % 2 == 0)
		{
			int	y_start = ((tui->board_y + tui->board_height) / 2) - 1;
			int	x_start = (width / 2) - (int) (83 / 2);
			mvwprintw(tui->wbody, y_start++, x_start, "__   __          _            _   _                     _                       _ ");
			mvwprintw(tui->wbody, y_start++, x_start, "\\ \\ / /         ( )          | | | |                   (_)                     | |");
			mvwprintw(tui->wbody, y_start++, x_start, " \\ V /___  _   _|/ _ __ ___  | |_| |__   ___  __      ___ _ __  _ __   ___ _ __| |");
			mvwprintw(tui->wbody, y_start++, x_start, "  \\ // _ \\| | | | | '__/ _ \\ | __| '_ \\ / _ \\ \\ \\ /\\ / / | '_ \\| '_ \\ / _ \\ '__| |");
			mvwprintw(tui->wbody, y_start++, x_start, "  | | (_) | |_| | | | |  __/ | |_| | | |  __/  \\ V  V /| | | | | | | |  __/ |  |_|");
			mvwprintw(tui->wbody, y_start, x_start, "  \\_/\\___/ \\__,_| |_|  \\___|  \\__|_| |_|\\___|   \\_/\\_/ |_|_| |_|_| |_|\\___|_|  (_)");
		}
		else
		{
			int	y_start = ((tui->board_y + tui->board_height) / 2) - 1;
			int	x_start = (width / 2) - (int) (76 / 2);
			mvwprintw(tui->wbody, y_start++, x_start, "  ___  _____   _       _   _                     _                       _ ");
			mvwprintw(tui->wbody, y_start++, x_start, " / _ \\|_   _| (_)     | | | |                   (_)                     | |");
			mvwprintw(tui->wbody, y_start++, x_start, "/ /_\\ \\ | |    _ ___  | |_| |__   ___  __      ___ _ __  _ __   ___ _ __| |");
			mvwprintw(tui->wbody, y_start++, x_start, "|  _  | | |   | / __| | __| '_ \\ / _ \\ \\ \\ /\\ / / | '_ \\| '_ \\ / _ \\ '__| |");
			mvwprintw(tui->wbody, y_start++, x_start, "| | | |_| |_  | \\__ \\ | |_| | | |  __/  \\ V  V /| | | | | | | |  __/ |  |_|");
			mvwprintw(tui->wbody, y_start, x_start, "\\_| |_/\\___/  |_|___/  \\__|_| |_|\\___|   \\_/\\_/ |_|_| |_|_| |_|\\___|_|  (_)");
		}
	}
	else
	{
		wmove(tui->wbody, tui->board_y + 1, (width / 2) - 10);
		wprintw(tui->wbody, "%s the winner!",
			tui->move % 2 != 0 ? " AI is" : "You're are");
	}
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
	print_header(tui, "<<<  THE GREAT NIM  >>>", 1);

	int	blen = get_board_len(board);
	
	if (blen > 0)
	{
		print_move(tui, tui->move, 2);
		print_ai_move(tui, 3);
	}
	else
	{
		print_header(tui, (tui->move % 2 != 0 ? "AI wins" : "Player wins") , 2);
		print_result(tui);
	}

	int	height, width;
	getmaxyx(tui->wbody, height, width);
	char	sep_line[width];
	for (int i = 0; i < width; i++)
		sep_line[i] = '=';
	sep_line[width] = '\0';
	mvwprintw(tui->wbody, (tui->board_y - 1), 0, "%s", sep_line);
	for (int h = tui->cur_heap;
			h - tui->cur_heap < tui->board_height
			&& h < blen
			; h++)
	{
		print_heap(tui, h, board[h]);
	}
	mvwprintw(tui->wbody, (tui->board_y + tui->board_height), 0, "%s", sep_line);
	wrefresh(tui->wbody);
}

void	print_ascii_digit(TUI *tui, int d, int color, int x, int y)
{
	// ASCII art for digits
	char *digit1[] = {
		"┓  ",
		"┃  ",
		"┻  ",
		"   "
	};

	char *digit2[] = {
		" ┏┓",
		" ┏┛",
		" ┗━",
		"  "
	};

	char *digit3[] = {
		" ┏┓",
		"  ┫",
		" ┗┛",
		"   "
	};
	char	**to_print = NULL;
	switch (d)
	{
		case 1:
			to_print = digit1;
			break;
		case 2:
			to_print = digit2;
			break;
		case 3:
			to_print = digit3;
			break;
		default:
			return ;
	}
	wattron(tui->wbody, COLOR_PAIR(color));
	for (int i = 0; i < 4; i++) {
		mvwprintw(tui->wbody, y + i, x, "%s\n", to_print[i]);
	}
	wattroff(tui->wbody, COLOR_PAIR(color));
}

void	print_options(TUI *tui, int a)
{
	print_header(tui, "Available moves",(tui->board_y + tui->board_height + 2));
	int	height, width;
	getmaxyx(tui->wbody, height, width);
	int	x_pos = (width / 2) - 6;
	int	y_pos = tui->board_y + tui->board_height + 4;
	for (int i = 0; i < 3; i++)
	{
		x_pos += 3 * i;
		print_ascii_digit(tui, i + 1, a >= (i + 1) ? 1 : 2, x_pos, y_pos);
	}
	wrefresh(tui->wbody);
}

int	update_board(TUI *tui, int num, int *board)
{
	int	blen = (int) get_board_len(board);
	if (num < 1 || num > board[blen])
		return (board[blen]);
	board[blen] -= num;
	if (board[blen] == 0)
		board[blen] = -42;
	tui->move++;
	return (board[blen]);
}

/*
int	main2(void)
{
	int		board[] = {
		1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 13, 14, 15, 16, 17, 18, 19, 20, -42};
		21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
		1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 13, 14, 15, 16, 17, 18, 19, 20,
		21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 4,
		-42
	};
	
	TUI		*tui = tui_init();
	int		key;
	bool	run = true;
	int		blen;
	while (run)
	{
		blen = (int) get_board_len(board);
		werase(tui->wbody);
		draw_board(tui, board);
		print_options(tui, board[blen - 1]);
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
				// board[blen] = update_board(tui, 3, board);
				num = key - '0';
				if (num < 1 || num > board[blen - 1])
					break;
				board[blen - 1] -= num;
				if (board[blen - 1] == 0)
					board[blen - 1] = -42;
				tui->move++;
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
	return (0);
}
*/
