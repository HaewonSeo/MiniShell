/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cntword.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 16:57:09 by haseo             #+#    #+#             */
/*   Updated: 2021/05/22 16:57:42 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_cntword(char const *s, char c)
{
	size_t		count;
	int			word_start;

	count = 0;
	word_start = 1;
	while (*s)
	{
		if (*s == c)
			word_start = 1;
		else if (word_start == 1)
		{
			count++;
			word_start = 0;
		}
		s++;
	}
	return (count);
}
