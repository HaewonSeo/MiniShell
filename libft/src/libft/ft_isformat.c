/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isformat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 20:59:06 by haseo             #+#    #+#             */
/*   Updated: 2021/05/19 19:41:06 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isformat(char *str, char *fmt)
{
	int		len_str;
	int		len_fmt;
	char	*start_fmt;

	len_str = ft_strlen(str);
	len_fmt = ft_strlen(fmt);
	if (len_str <= len_fmt)
		return (0);
	start_fmt = str + len_str - len_fmt;
	if (ft_strncmp(start_fmt, fmt, len_fmt) == 0)
		return (1);
	return (0);
}
