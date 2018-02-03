/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-huu- <tle-huu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 21:44:09 by tle-huu-          #+#    #+#             */
/*   Updated: 2018/02/03 10:04:08 by tle-huu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		check_horizontal_inter(t_game *game, double cam, t_dda *dda)
{
	dda->ray->x = game->direction->x + (game->plane->x) * cam;

	dda->delta->x = fabs(1 / dda->ray->x);
	if (dda->ray->x < 0)
	{
		dda->step->x = -1;
		dda->dist->x = (game->position->x - dda->map->x) * dda->delta->x;
	}
	else
	{
		dda->step->x = 1;
		dda->dist->x = (dda->map->x + 1.0 - game->position->x) * dda->delta->x;
	}
}

void			check_vertical_inter(t_game *game, double cam, t_dda *dda)
{
	dda->ray->y = game->direction->y + game->plane->y * cam;

	dda->delta->y = fabs(1 / dda->ray->y);
	if (dda->ray->y < 0)
	{
		dda->step->y = -1;
		dda->dist->y = (game->position->y - dda->map->y) * dda->delta->y;
	}
	else
	{
		dda->step->y = 1;
		dda->dist->y= (dda->map->y + 1.0 - game->position->y) * dda->delta->y;
	}

}

void			caster(t_dda *dda, char **map)
{
	int hit;

	hit = 0;

	while (hit == 0)
	{
		if (dda->dist->x < dda->dist->y)
		{
			dda->dist->x += dda->delta->x;
			dda->map->x += dda->step->x;
			dda->side = 0;
		}
		else
		{
			dda->dist->y += dda->delta->y;
			dda->map->y += dda->step->y;
			dda->side = 1;
		}
		if (map[(int)dda->map->x][(int)dda->map->y] > 0)
			hit = 1;
	}
}

void			drawer(t_game *game, t_dda *dda, char **map, int column)
{
	int finalDist;
	int projectedHeight;
	int drawStart;
	int drawEnd;

	if (!dda->side)
		finalDist = (dda->map->x - game->position->x + (1 - dda->step->x) / 2) / dda->ray->x;
	else
		finalDist = (dda->map->y - game->position->y + (1 - dda->step->y) / 2) / dda->ray->y;
	projectedHeight = (int)(game->screen->y / finalDist);
	drawStart = game->screen->y / 2 - projectedHeight / 2;
	drawEnd = game->screen->y / 2 + projectedHeight / 2;
	if (drawStart < 0)
		drawStart = 0;
	if (drawEnd >= game->screen->y)
		drawEnd = game->screen->y - 1;
	while (drawStart <= drawEnd)
		mlx_pixel_put(game->mlx_ptr, game->win_ptr, column, drawStart++ , color(dda, map));
}
