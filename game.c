/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-huu- <tle-huu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 17:13:08 by tle-huu-          #+#    #+#             */
/*   Updated: 2018/02/04 14:57:34 by tle-huu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		painter(t_game *game, t_dda *dda)
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

int			game(char **map)
{
	t_game	*game;
	t_dda	*dda;

	game = new_wolf(map, SCREENWIDTH, SCREENHEIGHT);
	dda = new_dda();
	game->mlx_ptr = mlx_init();
	game->win_ptr = mlx_new_window(game->mlx_ptr, game->screen->x,
		game->screen->y, "Raycatster");
	game->position->x = 14.5;
	game->position->y = 14.5;
	painter(game, dda);
	game->moveSpeed = 0.2;
	game->rotSpeed = 0.1;
	mlx_do_key_autorepeaton(game->mlx_ptr);
	mlx_hook(game->win_ptr, 2, 0, motion, (void *)game);
	mlx_loop(game->mlx_ptr);
	return (0);
}

int			main(int argc, char **argv)
{
	int		fd;
	char	**map;

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
