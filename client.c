/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schetty <schetty@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 16:51:21 by schetty           #+#    #+#             */
/*   Updated: 2021/10/09 11:08:32 by schetty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	sighandler(int signum)
{
	static int	count = 0;

	if (signum == SIGUSR1)
		count++;
	else
	{
		ft_printf("  \033[0;34m%d Received\033[0m\n\n", count);
		exit(0);
	}
}

static void	send_bit(int pid, char chr)
{
	int	bit;

	bit = 8;
	while (bit--)
	{
		if (chr >> bit & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(100);
	}
}

static void	send_message(int pid, char *str)
{
	while (*str)
		send_bit(pid, *str++);
	send_bit(pid, 0);
}

int	main(int argc, char **argv)
{
	int	ret;

	ret = 0;
	if (argc != 3)
		ret = (error_message(1, 0));
	else if (!is_numeric(argv[1]))
		ret = (error_message(2, 0));
	else if (!ft_strlen(argv[2]))
		ret = (error_message(3, 0));
	if (!ret)
	{
		ft_printf("\n\033[0;32m%d Sent", ft_strlen(argv[2]));
		signal(SIGUSR1, sighandler);
		signal(SIGUSR2, sighandler);
		send_message(ft_atoi(argv[1]), argv[2]);
	}
	return (ret);
}
