/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:28:37 by astavrop          #+#    #+#             */
/*   Updated: 2024/04/05 22:45:05 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_H
# define GUI_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>

#include <stdbool.h>

# define SCREEN_WIDTH	1280
# define SCREEN_HEIGHT	720

# define TEXTURE_SIZE	1

typedef struct
{
	/* General */
	SDL_Renderer	*renderer;
	SDL_Window		*win;
	/* Assests */
	SDL_Surface		*matchSface;
	SDL_Texture		*matchTexture;
}	App;

/* init.c */

App		initSDL(void);

/* input.c */

bool	doInput(void);

/* draw.c */

void	prepareScene(App app);
void	presentScene(App app);
void	loadBMP(App app, char *filename);

#endif /* GUI_H */
