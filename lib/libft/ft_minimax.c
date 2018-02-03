/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minimax.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-huu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 16:56:59 by tle-huu-          #+#    #+#             */
/*   Updated: 2018/01/19 16:57:04 by tle-huu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_max(int a, int b)
{
	if (a < b)
		return (b);
	else
		return (a);
}

int		ft_min(int a, int b)
{
	if (a < b)
		return (a);
	else
		return (b);
}
