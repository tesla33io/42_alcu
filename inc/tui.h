/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:30:21 by astavrop          #+#    #+#             */
/*   Updated: 2024/04/06 20:55:54 by astavrop         ###   ########.fr       */
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
}	TUI;

#endif /* TUI_H */
