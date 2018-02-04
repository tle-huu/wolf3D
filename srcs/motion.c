/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-huu- <tle-huu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 13:37:49 by tle-huu-          #+#    #+#             */
/*   Updated: 2018/02/04 15:45:18 by tle-huu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	keyup(t_game *game)
{
	if (!game->map[(int)(game->position->x + game->direction->x *
		game->movespeed)][(int)(game->position->y)])
		game->position->x += game->direction->x * game->movespeed;
	if (!game->map[(int)(game->position->x)][(int)(game->position->y
		+ game->direction->y * game->movespeed)])
		game->position->y += game->direction->y * game->movespeed;
}

static void	keydown(t_game *game)
{
	if (!game->map[(int)(game->position->x - game->direction->x *
		game->movespeed)][(int)(game->position->y)])
		game->position->x -= game->direction->x * game->movespeed;
	if (!game->map[(int)(game->position->x)][(int)(game->position->y
		- game->direction->y * game->movespeed)])
		game->position->y -= game->direction->y * game->movespeed;
}

static void	keyright(t_game *game)
{
	double olddir;
	double oldplane;

	olddir = game->direction->x;
	oldplane = game->plane->x;
	game->direction->x = game->direction->x * cos(-game->rotspeed) -
	game->direction->y * sin(-game->rotspeed);
	game->direction->y = olddir * sin(-game->rotspeed) + game->direction->y
	* cos(-game->rotspeed);
	game->plane->x = game->plane->x * cos(game->rotspeed) - game->plane->y
	* sin(-game->rotspeed);
	game->plane->y = oldplane * sin(-game->rotspeed) + game->plane->y
	* cos(game->rotspeed);
}

static void	keyleft(t_game *game)
{
	double olddir;
	double oldplane;

	olddir = game->direction->x;
	oldplane = game->plane->x;
	game->direction->x = game->direction->x * cos(game->rotspeed) -
	game->direction->y * sin(game->rotspeed);
	game->direction->y = olddir * sin(game->rotspeed) + game->direction->y
	* cos(game->rotspeed);
	game->plane->x = game->plane->x * cos(game->rotspeed) - game->plane->y
	* sin(game->rotspeed);
	game->plane->y = oldplane * sin(game->rotspeed) + game->plane->y *
	cos(game->rotspeed);
}

int			motion(int keycode, t_game *game)
{
	t_dda *dda;

	dda = new_dda();
	if (keycode == KEY_UP)
		keyup(game);
	else if (keycode == KEY_DOWN)
		keydown(game);
	else if (keycode == KEY_RIGHT)
		keyright(game);
	else if (keycode == KEY_LEFT)
		keyleft(game);
	mlx_clear_window(game->mlx_ptr, game->win_ptr);
	painter(game, dda);
	free(dda);
	return (0);
}
