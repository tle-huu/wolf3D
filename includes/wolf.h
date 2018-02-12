/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-huu- <tle-huu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 12:56:33 by tle-huu-          #+#    #+#             */
/*   Updated: 2018/02/11 10:52:45 by tle-huu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include "mlx.h"
# include "libft.h"
# include "fcntl.h"

# define PI 3.14159265358979323846
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_F 3
# define KEY_H 4
# define KEY_G 5
# define KEY_Z 6
# define KEY_X 7
# define KEY_C 8
# define KEY_V 9
# define KEY_B 11
# define KEY_Q 12
# define KEY_W 13
# define KEY_E 14
# define KEY_R 15
# define KEY_Y 16
# define KEY_T 17
# define KEY_ONE 18
# define KEY_TWO 19
# define KEY_THREE 20
# define KEY_FOUR 21
# define KEY_SIX 22
# define KEY_FIVE 23
# define KEY_NINE 25
# define KEY_SEVEN 26
# define KEY_EIGHT 28
# define KEY_ZERO 29
# define KEY_BRACE_R 30
# define KEY_O 31
# define KEY_U 32
# define KEY_BRACE_L 33
# define KEY_I 34
# define KEY_P 35
# define KEY_L 37
# define KEY_J 38
# define KEY_K 40
# define KEY_SEMI 41
# define KEY_N 45
# define KEY_M 46
# define KEY_TAB 48
# define KEY_ESC 53
# define KEY_PLUS 69
# define KEY_MINUS 78
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_DOWN 125
# define KEY_UP 126
# define SCREENWIDTH 320
# define SCREENHEIGHT 200
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

	char		**map;
	void		*mlx_ptr;
	void		*win_ptr;

	t_point		*position;
	t_point		*direction;
	t_point		*plane;
	t_point		*screen;

	double		fov;
	double		time;
	double		h;
	double		movespeed;
	double		rotspeed;
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

char					**reader(int fd);
t_point					*new_point(double x, double y);
t_game					*new_wolf(char **map, int width, int height);
void					check_vertical_inter(t_game *game, double cam,
	t_dda *dda);
void					check_horizontal_inter(t_game *game, double cam,
	t_dda *dda);
t_dda					*new_dda();
void					caster(t_dda *dda, char **map);
int						color(t_dda *dda, char **map, t_game *game);
void					drawer(t_game *game, t_dda *dda, int column);
int						motion(int keycode, t_game *game);
void					painter(t_game *game, t_dda *dda);

#endif
