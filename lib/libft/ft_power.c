/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-huu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 16:30:35 by tle-huu-          #+#    #+#             */
/*   Updated: 2017/11/14 16:32:41 by tle-huu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_power(int n, int pow)
{
	if (pow < 0 || n == 0)
		return (0);
	if (pow == 0)
		return (n);
	if (n % 2 == 0)
		return (ft_power(n * n, pow / 2));
	else
		return (n * ft_power(n * n, pow / 2));
}