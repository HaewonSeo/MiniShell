/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 23:02:56 by haseo             #+#    #+#             */
/*   Updated: 2021/10/14 17:26:49 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	printf_spec(t_spec *spec, va_list ap)
{
	if (spec->type == 'c')
		printf_ch(spec, va_arg(ap, int));
	else if (spec->type == 's')
		printf_str(spec, va_arg(ap, char *));
	else if (spec->type == 'p')
		printf_nbr(spec, va_arg(ap, long long));
	else if (spec->type == 'd' || spec->type == 'i')
		printf_nbr(spec, va_arg(ap, int));
	else if (spec->type == 'u' || spec->type == 'x' || spec->type == 'X')
		printf_nbr(spec, va_arg(ap, unsigned int));
	else if (spec->type == '%')
		printf_ch(spec, '%');
}

static int	print_format(const char *format, va_list ap)
{
	int		i;
	int		cnt_ch;
	t_spec	spec;

	i = 0;
	cnt_ch = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			init_spec(&spec);
			while (!ft_strchr(TYPE, format[++i]))
				get_opt_spec(&spec, format[i], ap);
			spec.type = format[i++];
			handle_unusual_case(&spec);
			printf_spec(&spec, ap);
			cnt_ch += spec.cnt_ch;
		}
		else
		{
			ft_putchar_fd(format[i++], 1);
			cnt_ch++;
		}
	}
	return (cnt_ch);
}

int	ft_printf(const char *format, ...)
{
	va_list		ap;
	int			cnt_ch;

	va_start(ap, format);
	cnt_ch = print_format(format, ap);
	va_end(ap);
	return (cnt_ch);
}
