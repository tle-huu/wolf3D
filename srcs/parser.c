/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-huu- <tle-huu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 22:14:01 by tle-huu-          #+#    #+#             */
/*   Updated: 2018/02/11 10:19:15 by tle-huu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

static void	numberit(char **map)
{
	int i;
	int j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[j])
			map[i][j++] -= 48;
		i++;
	}
}

static void	fill_map(int fd, char **line, char **map, size_t len)
{
	size_t i;

	i = 1;
	while (i < len)
	{
		get_next_line(fd, line);
		if ((size_t)ft_strlen(*line) > len)
		{
			ft_printf("Wrong map size\n");
			exit(1);
		}
		map[i] = *line;
		i++;
	}
	if (get_next_line(fd, line))
	{
		ft_printf("Wrong map size\n");
		exit(1);
	}
}

char		**reader(const int fd)
{
	char	*line;
	char	**map;
	size_t	len;

	line = NULL;
	get_next_line(fd, &line);
	len = ft_strlen(line);
	if (!(map = (char **)malloc(sizeof(*map) * len + 1)))
		exit(1);
	map[len] = 0;
	map[0] = line;
	fill_map(fd, &line, map, len);
	numberit(map);
	return (map);
}
