/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-huu- <tle-huu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 21:44:09 by tle-huu-          #+#    #+#             */
/*   Updated: 2018/02/04 15:41:02 by tle-huu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void			check_vertical_inter(t_game *game, double cam, t_dda *dda)
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

void			check_horizontal_inter(t_game *game, double cam, t_dda *dda)
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
		dda->dist->y = (dda->map->y + 1.0 - game->position->y) * dda->delta->y;
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

static void		norm(int drawstart, int drawend, int column,
	t_game *game)
{
	int i;

	i = 0;
	while (i <= drawstart)
		mlx_pixel_put(game->mlx_ptr, game->win_ptr, column, i++,
			0x202033);
	while (drawend <= game->screen->y)
		mlx_pixel_put(game->mlx_ptr, game->win_ptr, column, drawend++,
			0x996600);
}

void			drawer(t_game *game, t_dda *dda, int column)
{
	double	finaldist;
	int		projectedheight;
	int		drawstart;
	int		drawend;

	if (!dda->side)
		finaldist = fabs((dda->map->x - game->position->x +
			(1 - dda->step->x) / 2) / dda->ray->x);
	else
		finaldist = fabs((dda->map->y - game->position->y +
			(1 - dda->step->y) / 2) / dda->ray->y);
	projectedheight = (int)(game->screen->y / finaldist);
	drawstart = game->screen->y / 2 - projectedheight / 2;
	drawend = game->screen->y / 2 + projectedheight / 2;
	if (drawstart < 0)
		drawstart = 0;
	if (drawend >= game->screen->y)
		drawend = game->screen->y - 1;
	norm(drawstart, drawend, column, game);
	while (drawstart <= drawend)
		mlx_pixel_put(game->mlx_ptr, game->win_ptr, column, drawstart++,
			color(dda, game->map));
}
