/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 19:53:16 by haseo             #+#    #+#             */
/*   Updated: 2020/11/23 02:46:59 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *b1, const void *b2, size_t len)
{
	size_t			i;
	unsigned char	*uc_b1;
	unsigned char	*uc_b2;

	i = 0;
	uc_b1 = (unsigned char *)b1;
	uc_b2 = (unsigned char *)b2;
	while (i < len)
	{
		if (uc_b1[i] != uc_b2[i])
			return (uc_b1[i] - uc_b2[i]);
		i++;
	}
	return (0);
}
