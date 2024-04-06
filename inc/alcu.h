/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alcu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:02:01 by astavrop          #+#    #+#             */
/*   Updated: 2024/04/06 15:31:52 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"

# define W 1
# define L 0

extern int g_winner;
// typedef struct s_board {
// 	char	**board;
// 	/**********************
// 	 * ["||||||||||||||",
// 	 *  "|||||||||",
// 	 *  "|||",
// 	 *  "|||||||||||||||||",
// 	 *  "|||||",
// 	 *  NULL]
// 	 **********************/
// 	char	**states;
// 	/***********************
// 	 * ["W",
// 	 *  "L",
// 	 *  "W",
// 	 *  "W",
// 	 *  "L",
// 	 *  "W",
// 	 *  NULL]
// 	 **********************/
// }	t_board;

typedef struct s_board
{
	int objs;
	int	nmb_heap;
	int	state;
	struct s_board *next;
	struct s_board *prev;
} t_board;

size_t	ft_arrsize(char	**arr);
void	print_arr(char **arr);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *src);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
int		print_digit(int n);
void	ft_putstr_fd(char *s, int fd);
t_board	*ft_lstnew(int val);
void	ft_add_back(t_board **head, t_board *new_node);
void	delete_last_node(t_board **head);
int		get_max(t_board *stack);
size_t	ft_lstsize(t_board *board);
void	free_list(t_board *head, t_board *last);
void	print_lst(t_board *board);
int 	read_stdin(t_board **board);
int		open_read_file(t_board **board, char *file);
int		get_user_input(t_board *board);
int		isdigit_str(char *s);
int		out_range(int nbr, int min, int max);
void	ft_putnbr_fd(int n, int fd);
void	set_states(t_board *boar);
void	print_board(t_board *board);
void	bot_turn(t_board **board);
int		take_last(int items);
int		leave_last(int items);
