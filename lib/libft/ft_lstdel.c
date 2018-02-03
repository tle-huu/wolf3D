/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-huu- <tlehuu@hotmail.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 17:29:24 by tle-huu-          #+#    #+#             */
/*   Updated: 2017/10/24 17:37:05 by tle-huu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*follower;

	if (*alst && del)
	{
		follower = (*alst)->next;
		ft_lstdelone(alst, del);
		ft_lstdel(&follower, del);
	}
}
