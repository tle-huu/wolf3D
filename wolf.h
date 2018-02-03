/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-huu- <tle-huu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 12:56:33 by tle-huu-          #+#    #+#             */
/*   Updated: 2018/02/03 10:04:11 by tle-huu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include "minilibx_macos/mlx.h"
# include "libft.h"


# define RED 0xFF0033
# define YELLOW 0xFFFF00
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define WHITE 0xFFFFFF

# define PI 3.14159265358979323846

typedef struct			s_point
{
	double x;
	double y;
}						t_point;

typedef struct			s_game
{

	char **map;
	void *mlx_ptr;
	void *win_ptr;

	t_point *position;
	t_point *direction;
	t_point *plane;
	t_point *screen;

	double fov;
	double time;
	double oldTime;
	double playerHeight;
	double h;
	double moveSpedd;
	double rotSpeed;
	double frameTime;
}						t_game;

typedef struct			s_dda
{
	t_point		*map;
	t_point		*dist;
	t_point		*delta;
	t_point		*ray;
	t_point		*step;
	int			side;
}						t_dda;

char		**reader(int fd);
t_point		*new_point(double x, double y);
t_game		*new_wolf(char **map, int width, int height);
void		check_vertical_inter(t_game *game, double cam, t_dda *dda);
void		check_horizontal_inter(t_game *game, double cam, t_dda *dda);
t_dda		*new_dda();
void		caster(t_dda *dda, char **map);
int 		color(t_dda *dda, char **map);
void		drawer(t_game *game, t_dda *dda, char **map, int column);

#endif
