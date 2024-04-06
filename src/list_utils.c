/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 20:34:14 by ohladkov          #+#    #+#             */
/*   Updated: 2024/04/07 00:01:29 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alcu.h"

t_board	*ft_lstnew(int val)
{
	t_board	*new;

	new = (t_board *)ft_calloc(1, sizeof(t_board));
	if (!new)
		return (NULL);
	new->objs = val;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	ft_add_back(t_board **head, t_board *new_node)
{
	t_board	*last;

	if (head == NULL)
		return ;
	if (*head == NULL)
	{
		(*head) = new_node;
		(*head)->next = new_node;
		(*head)->prev = new_node;
		return ;
	}
	last = (*head);
	while (last->next != *head)
		last = last->next;
	if (new_node)
	{
		last->next = new_node;
		new_node->prev = last;
		(*head)->prev = new_node;
		new_node->next = (*head);
	}
}

void	delete_last_node(t_board **head)
{
	t_board *last = (*head)->prev;

	if (head == NULL || *head == NULL)
		return ;
	if ((*head)->next == *head && (*head)->prev == *head)
	{
		free(*head);
		(*head) = NULL;
	}
	else
	{
		(*head)->prev->prev->next = (*head);
		(*head)->prev = (*head)->prev->prev;
		free(last);
		last = NULL;
	}
}

size_t	ft_lstsize(t_board *board)
{
	t_board	*cur;
	size_t	i;

	if (!board)
		return (0);
	cur = board;
	i = 1;
	while (cur->next != board)
	{
		cur = cur->next;
		i++;
	}
	return (i);
}

void	free_list(t_board *head, t_board *last)
{
	if (head == NULL)
		return ;
	if (head != last)
		free_list(head->next, last);
	free(head);
}

