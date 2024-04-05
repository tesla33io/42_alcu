/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:40:19 by astavrop          #+#    #+#             */
/*   Updated: 2024/04/05 22:48:31 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/gui.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stdlib.h>

int	main(void)
{
	App	app = initSDL();

	// loadBMP(app, "data/match_1.bmp");

	char	*filename = "data/match_1.bmp";
	app.matchSface = SDL_LoadBMP(filename);
	if (app.matchSface == NULL)
	{
		printf("Error loadBMP: %s\n", SDL_GetError());
		exit(1);
	}

	app.matchTexture = SDL_CreateTextureFromSurface(app.renderer, app.matchSface);
	while (1)
	{
		prepareScene(app);
		if (doInput())
			break;
		presentScene(app);
		SDL_Delay(16);
	}

	/* Cleanup */
	SDL_FreeSurface(app.matchSface);
	SDL_DestroyTexture(app.matchTexture);
	SDL_DestroyWindow(app.win);
	SDL_DestroyRenderer(app.renderer);
	// free(app.matchSface);

	return (0);
}
