/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_ch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 18:29:40 by haseo             #+#    #+#             */
/*   Updated: 2021/10/14 17:27:45 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	printf_ch(t_spec *spec, const char ch)
{
	char	pad;

	if (spec->type == '%' && spec->zero_pad)
		pad = '0';
	else
		pad = ' ';
	if (spec->width > 0)
		spec->cnt_ch += spec->width;
	else
		spec->cnt_ch = 1;
	if (spec->hyphen)
	{
		ft_putchar_fd(ch, 1);
		while (--(spec->width) > 0)
			ft_putchar_fd(pad, 1);
	}
	else
	{
		while (--(spec->width) > 0)
			ft_putchar_fd(pad, 1);
		ft_putchar_fd(ch, 1);
	}
}
