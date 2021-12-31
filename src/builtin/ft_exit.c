/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 18:36:01 by haseo             #+#    #+#             */
/*   Updated: 2021/12/30 17:28:10 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_exit_with_set_mode(int errnum)
{
	// 프로그래밍이 종료되기 때문에, 동적 할당한 메모리 해제하는 기능을 추가해야 함
		// envp
		// cmd list
		// ...

	set_canonical_mode();
	exit(errnum);
}

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
