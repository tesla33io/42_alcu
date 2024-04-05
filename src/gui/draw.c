/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:53:04 by astavrop          #+#    #+#             */
/*   Updated: 2024/04/05 22:42:03 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/gui.h"
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stdlib.h>

void prepareScene(App app)
{
	for (int i = 0; i < 30 * 10; i += 30)
	{
		SDL_Rect dstrect = { 5 + i, 5, 20 * TEXTURE_SIZE, 60 * TEXTURE_SIZE };
		SDL_RenderCopy(app.renderer, app.matchTexture, NULL, &dstrect);
	}
}

void presentScene(App app)
{
	SDL_RenderPresent(app.renderer);
}

void	loadBMP(App app, char *filename)
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

	// app.matchSface = malloc(sizeof(SDL_Surface));
	app.matchSface = SDL_LoadBMP(filename);
	if (app.matchSface == NULL)
	{
		printf("Error loadBMP: %s\n", SDL_GetError());
		exit(1);
	}
}
