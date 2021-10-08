/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schetty <schetty@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 16:51:21 by schetty           #+#    #+#             */
/*   Updated: 2021/10/08 18:03:51 by schetty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	sighandler(int signum)
{
	static int	count = 0;

	if (signum == SIGUSR1)
		count++;
	else
	{
		ft_printf("  \033[0;34m%d Received\033[0m\n", ++count);
		exit(0);
	}
}

void	send_bit(int pid, char chr)
{
	int	bit;

	bit = 8;
	while (bit--)
	{
		if (chr >> bit & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(1500);
	}
}

void	send_message(int pid, char *str)
{
	while (*str)
		send_bit(pid, *str++);
	send_bit(pid, 0);
}

static int	is_valid(int argc, char **argv)
{
	if (argc != 3)
		return (error_message(1, 0));
	else if (!is_numeric(argv[1]))
		return (error_message(2, 0));
	else if (!ft_strlen(argv[2]))
		return (error_message(3, 0));
	else
		return (0);
}

int	main(int argc, char **argv)
{
	int	ret;

	ret = is_valid(argc, argv);
	if (!ret)
	{
		ft_printf("\nSignal: \033[0;32m%d Sent", (ft_strlen(argv[2]) + 1) * 8);
		signal(SIGUSR1, sighandler);
		signal(SIGUSR2, sighandler);
		send_message(ft_atoi(argv[1]), argv[2]);
	}
	return (ret);
}
