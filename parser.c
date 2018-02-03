/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-huu- <tle-huu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 22:14:01 by tle-huu-          #+#    #+#             */
/*   Updated: 2018/02/03 15:53:13 by tle-huu-         ###   ########.fr       */
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

char		**reader(const int fd)
{
	char	*line;
	char	**map;
	size_t	len;
	size_t	i;

	line = NULL;
	get_next_line(fd, &line);
	len = ft_strlen(line);
	if (!(map = (char **)malloc(sizeof(*map) * len + 1)))
		exit(1);
	map[len] = 0;
	map[0] = line;
	i = 1;
	while (i < len)
	{
		get_next_line(fd, &line);
		map[i] = line;
		i++;
	}
	numberit(map);
	return (map);
}
