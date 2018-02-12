/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-huu- <tle-huu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 17:13:08 by tle-huu-          #+#    #+#             */
/*   Updated: 2018/02/12 08:54:02 by tle-huu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static int		exit_hook(void)
{
	exit(0);
	return (1);
}

void			painter(t_game *game, t_dda *dda)
{
	int		column;
	double	cam;

	column = 0;
	while (column < SCREENWIDTH)
	{
		cam = 2 * column / (double)SCREENWIDTH - 1;
		dda->map->x = (int)game->position->x;
		dda->map->y = (int)game->position->y;
		check_horizontal_inter(game, cam, dda);
		check_vertical_inter(game, cam, dda);
		caster(dda, game->map);
		drawer(game, dda, column);
		column++;
	}
}

int				game(char **map)
{
	t_game	*game;
	t_dda	*dda;

	game = new_wolf(map, SCREENWIDTH, SCREENHEIGHT);
	dda = new_dda();
	game->position->x = 15;
	game->position->y = 15;
	if (map[(int)game->position->x][(int)game->position->y] > 0)
	{
		ft_printf("Wrong starting position\n");
		exit(1);
	}
	game->mlx_ptr = mlx_init();
	game->win_ptr = mlx_new_window(game->mlx_ptr, game->screen->x,
		game->screen->y, "wolf3d 42");
	painter(game, dda);
	mlx_do_key_autorepeaton(game->mlx_ptr);
	mlx_hook(game->win_ptr, 17, 0, exit_hook, 0);
	mlx_hook(game->win_ptr, 2, 0, motion, (void *)game);
	mlx_loop(game->mlx_ptr);
	free(map);
	free(game);
	free(dda);
	return (0);
}

int				main(int argc, char **argv)
{
	int		fd;

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
