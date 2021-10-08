/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schetty <schetty@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 03:05:13 by schetty           #+#    #+#             */
/*   Updated: 2021/10/08 18:04:16 by schetty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	is_numeric(char *num)
{
	int	i;

	if (!num)
		return (0);
	i = -1;
	while (num[++i])
	{
		if (!ft_isdigit(num[i]))
			return (0);
	}
	return (1);
}

int	error_message(int n, int is_exit)
{
	if (n == 1)
		ft_printf("USAGE: ./client [PID] [MESSAGE]\n");
	else if (n == 2)
		ft_printf("ERROR: PID Must Be Numbers\n");
	else if (n == 3)
		ft_printf("ERROR: MESSAGE Is Empty\n");
	else if (n == 4)
		ft_printf("ERROR: Initialization Error\n");
	else
		ft_printf("ERROR: Message Transmission Failed\n");
	if (is_exit)
		exit(0);
	else
		return (1);
}
