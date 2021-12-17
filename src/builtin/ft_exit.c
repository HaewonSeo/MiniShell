/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 18:36:01 by haseo             #+#    #+#             */
/*   Updated: 2021/12/17 12:04:59 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*

	exit 기능

	1. exit 출력
	2. canonical mode 설정
	3. 프로그램 종료

*/

void ft_exit()
{
	printf("exit\n");
	ft_exit_with_set_mode(0);
}
