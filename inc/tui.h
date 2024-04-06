/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:30:21 by astavrop          #+#    #+#             */
/*   Updated: 2024/04/06 17:26:26 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TUI_H
# define TUI_H

# include <ncurses.h>

# define SCREEN_WIDTH 80
# define SCREEN_HEIGHT 24

# define MAX_HEAPS 10000
# define MAX_ITEMS 10000

typedef struct
{
	WINDOW	*wbody;
	int		board_height;
	int		board_y;
	int		board_x;
	int		board_max;
	int		cur_heap;
}	TUI;

#endif /* TUI_H */
