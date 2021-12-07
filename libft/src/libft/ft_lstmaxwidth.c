/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmaxwidth.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 02:02:43 by haseo             #+#    #+#             */
/*   Updated: 2021/10/02 17:32:46 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_lstmaxwidth(t_list *lst)
{
	size_t	max;
	size_t	len;

	max = 0;
	while (lst)
	{
		len = ft_strlen((const char *)lst->content);
		if (len > max)
			max = len;
		lst = lst->next;
	}
	return (max);
}
