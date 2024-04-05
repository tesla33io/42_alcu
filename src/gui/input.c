/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:49:28 by astavrop          #+#    #+#             */
/*   Updated: 2024/04/05 22:48:18 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/gui.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>

bool doInput(void)
{
	SDL_Event	event;
	bool		q = false;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				exit(0);
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						q = true;
						break;
					case SDLK_q:
						q = true;
						break;
				}
				break;
			default:
				break;
		}
	}
	return (q);
}
