/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-huu- <tle-huu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 17:13:08 by tle-huu-          #+#    #+#             */
/*   Updated: 2018/02/03 10:25:22 by tle-huu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx_macos/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "wolf.h"
#include "libft.h"
#include "fcntl.h"

#define PI 3.14159265358979323846

#define mapWidth 24
#define mapHeight 24
#define SCREENWIDTH 512
#define SCREENHEIGHT 384


int worldMap[mapWidth][mapHeight]=
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,4,4,4,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int		game(char **map)
{
	t_game *game;
	t_dda *dda;

	game = new_wolf(map, SCREENWIDTH, SCREENHEIGHT);  // game = parser
	dda = new_dda();
	game->h = 64;
	game->playerHeight = game->h / 2;
	game->position->x = 22;
	game->position->y = 12;
	double distPlanePlayer = (SCREENWIDTH / 2) / (tan(PI / 6));
	int color = 0;
	int column = 0;
	double finalDist;

	double 	cam;

	game->mlx_ptr = mlx_init();
	game->win_ptr = mlx_new_window(game->mlx_ptr, SCREENWIDTH, SCREENHEIGHT, "Raycatster");

	while (column < SCREENWIDTH)
	{

		cam = 2 * column / (double)SCREENWIDTH - 1; //x-coordinate in camera space

		dda->map->x = game->position->x;
		dda->map->y = game->position->y;

		check_horizontal_inter(game, cam, dda);
		check_vertical_inter(game, cam, dda);
		caster(dda, game->map);
		drawer(game, dda, game->map, column);
		column++;
	}

	mlx_loop(game->mlx_ptr);
	return 0;
}

int main(int argc, char **argv)
{
	int fd;
	char **map;

	if (argc != 2)
	{
		ft_printf("usage: ./wolf map_file\n");
		return (1);
	}
	if ((fd = open(argv[1], O_RDONLY)) < 0)
	{
		ft_printf("Wrong entry.\n");
		return (1);
	}
	game(reader(fd));
	if (close(fd) == -1)
		return (2);
	return (0);
}
