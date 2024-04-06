/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:30:21 by astavrop          #+#    #+#             */
/*   Updated: 2024/04/06 22:13:18 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TUI_H
# define TUI_H

# include <ncurses.h>

typedef struct
{
	WINDOW	*wbody;
	int		board_height;
	int		board_y;
	int		board_x;
	int		board_max;
	int		cur_heap;
	int		move;
	int		last_ai_move;
}	TUI;

size_t	ft_tui_strlen(const char *str);
int		ft_dputs(int fd, const char *str);
TUI		*tui_init(void);
size_t	get_board_len(int *board);
void	print_header(TUI *tui, const char *text, int y_pos);
void	print_move(TUI *tui, int move, int y_pos);
void	print_heap(TUI *tui, int heap, int heap_len);
void	draw_board(TUI *tui, int *board);
void	print_ascii_digit(TUI *tui, int d, int color, int x, int y);
void	print_options(TUI *tui, int a);
int		update_board(TUI *tui, int num, int *board);
int		main2(void);

#endif /* TUI_H */
