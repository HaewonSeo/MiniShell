/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 16:14:21 by haseo             #+#    #+#             */
/*   Updated: 2021/12/18 18:01:13 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	pwd 기능

	현재 작업 디렉토리를 출력
		- getcwd를 이용할 수도 있고 - 이 방식으로 구현함
		- 환경변수 $PATH를 출력해도 됨
*/

void ft_pwd()
{
	printf("%s\n", getcwd(NULL, 0));
	g_info.exit_status = 0;
}
