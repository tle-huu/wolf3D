/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-huu- <tle-huu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 17:13:08 by tle-huu-          #+#    #+#             */
/*   Updated: 2018/02/03 15:13:55 by tle-huu-         ###   ########.fr       */
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
#define SCREENWIDTH 1000
#define SCREENHEIGHT 500

#include <time.h>
#include <sys/time.h>

#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#endif


void current_utc_time(struct timespec *ts) {

	#ifdef __MACH__ // OS X does not have clock_gettime, use clock_get_time
	clock_serv_t cclock;
	mach_timespec_t mts;
	host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
	clock_get_time(cclock, &mts);
	mach_port_deallocate(mach_task_self(), cclock);
	ts->tv_sec = mts.tv_sec;
	ts->tv_nsec = mts.tv_nsec;
	#else
	clock_gettime(CLOCK_REALTIME, ts);
	#endif


}

int		motion(int keyCode, t_game *game)
{
	if (keyCode == KEY_UP)
	{
		if(!game->map[(int)(game->position->x + game->direction->x * game->moveSpeed)][(int)(game->position->y)])
			game->position->x += game->direction->x * game->moveSpeed;
		if(!game->map[(int)(game->position->x)][(int)(game->position->y + game->direction->y * game->moveSpeed)])
			game->position->y += game->direction->y * game->moveSpeed;
	}
	else if (keyCode == KEY_DOWN)
	{
		if(!game->map[(int)(game->position->x - game->direction->x * game->moveSpeed)][(int)(game->position->y)])
			game->position->x -= game->direction->x * game->moveSpeed;
		if(!game->map[(int)(game->position->x)][(int)(game->position->y - game->direction->y * game->moveSpeed)])
			game->position->y -= game->direction->y * game->moveSpeed;
	}
	else if (keyCode == KEY_RIGHT)
	{
		double oldDir = game->direction->x;
		double oldPlane = game->plane->x;

		game->direction->x = game->direction->x * cos(-game->rotSpeed) - game->direction->y * sin(-game->rotSpeed);
		game->direction->y = oldDir * sin(-game->rotSpeed) + game->direction->y * cos(-game->rotSpeed);
		game->plane->x = game->plane->x * cos(game->rotSpeed) - game->plane->y * sin(-game->rotSpeed);
		game->plane->y = oldPlane * sin(-game->rotSpeed) + game->plane->y * cos(game->rotSpeed);
	}
	else if (keyCode == KEY_LEFT)
	{
		double oldDir = game->direction->x;
		double oldPlane = game->plane->x;

		game->direction->x = game->direction->x * cos(game->rotSpeed) - game->direction->y * sin(game->rotSpeed);
		game->direction->y = oldDir * sin(game->rotSpeed) + game->direction->y * cos(game->rotSpeed);
		game->plane->x = game->plane->x * cos(game->rotSpeed) - game->plane->y * sin(game->rotSpeed);
		game->plane->y = oldPlane * sin(game->rotSpeed) + game->plane->y * cos(game->rotSpeed);
	}
	mlx_clear_window(game->mlx_ptr, game->win_ptr);
	int column;
	double cam;
	t_dda *dda;
	dda = new_dda();
	column = 0;
	while (column < SCREENWIDTH)
	{

		cam = 2 * column / (double)SCREENWIDTH - 1; //x-coordinate in camera space

		dda->map->x = (int)game->position->x;
		dda->map->y = (int)game->position->y;

		check_horizontal_inter(game, cam, dda);
		check_vertical_inter(game, cam, dda);
		caster(dda, game->map);
		drawer(game, dda, game->map, column);
		column++;
	}

	return 0;
}

void		painter(t_game *game, t_dda *dda)
{
	int column;
	double cam;

	column = 0;
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
}


int		game(char **map)
{
	t_game *game;
	t_dda *dda;

	struct timespec timee;
	current_utc_time(&timee);
	struct timespec oldTime;

	game = new_wolf(map, SCREENWIDTH, SCREENHEIGHT);  // game = parser
	dda = new_dda();
	//double distPlanePlayer = (SCREENWIDTH / 2) / (tan(PI / 6));
	int color = 0;

	game->mlx_ptr = mlx_init();
	game->win_ptr = mlx_new_window(game->mlx_ptr, SCREENWIDTH, SCREENHEIGHT, "Raycatster");
	game->position->x = 14.5;
	game->position->y = 14.5;

	ft_printf("je passe icic \n");

	painter(game, dda);
	current_utc_time(&timee);
	oldTime = timee;
	current_utc_time(&timee);

	game->frameTime = (timee.tv_nsec - oldTime.tv_nsec) / 100000.0;
	printf("%f\n", 1.0 / game->frameTime);
	printf("frame : %f\n", game->frameTime);

	game->moveSpeed = 0.1;
	game->rotSpeed = 0.1;
	mlx_do_key_autorepeatoff((void *)game);

	mlx_key_hook(game->win_ptr, motion, (void *)game);
	//mlx_hook(v->window, 2, 0, motion, (void *)game);
	mlx_loop(game->mlx_ptr);

	return (0);
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
