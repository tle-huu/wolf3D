/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-huu- <tle-huu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 12:59:43 by tle-huu-          #+#    #+#             */
/*   Updated: 2018/02/03 13:46:16 by tle-huu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <math.h>

t_point		*new_point(double x, double y)
{
	t_point *nouveau;

	if (!(nouveau = (t_point *)malloc(sizeof(*nouveau))))
		exit(1);
	nouveau->x = x;
	nouveau->y = y;
	return (nouveau);

}

t_game		*new_wolf(char **map, int width, int height)
{
	t_game *nouveau;

	if (!(nouveau = (t_game *)malloc(sizeof(*nouveau))))
		exit(1);
	nouveau->map = map;
	nouveau->mlx_ptr = NULL;
	nouveau->win_ptr = NULL;
	nouveau->fov = PI / 3;
	nouveau->direction = new_point(-1, 0);
	nouveau->screen = new_point(width, height);
	nouveau->position = new_point(0, 0);
	nouveau->plane = new_point(0, tan(nouveau->fov / 2));


	nouveau->time = 0;
	nouveau->oldTime = 0;
	nouveau->h = 64;
	nouveau->moveSpeed = 0;
	nouveau->rotSpeed = 0;
	nouveau->frameTime = 0;
	return (nouveau);
}

t_dda		*new_dda()
{
	t_dda	*nouveau;

	if (!(nouveau = (t_dda *)malloc(sizeof(*nouveau))))
		exit(1);
	nouveau->map = new_point(0, 0);
	nouveau->step = new_point(0, 0);
	nouveau->dist = new_point(0, 0);
	nouveau->delta = new_point(0, 0);
	nouveau->ray = new_point(0, 0);
	nouveau->side = 0;
	return (nouveau);
}

int 	color(t_dda *dda, char **map)
{
	int color;
	int square;

	square = map[(int)dda->map->x][(int)dda->map->y];
	if (square == 1)
		color = RED;
	else if (square == 2)
		color = GREEN;
	else if (square == 3)
		color = BLUE;
	else if (square == 4)
		color = YELLOW;
	else
		color = WHITE;
	if (dda->side)
		color /= 3;
	return (color);
}
