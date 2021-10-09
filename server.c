/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schetty <schetty@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 16:51:24 by schetty           #+#    #+#             */
/*   Updated: 2021/10/09 11:53:24 by schetty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	server_message(int is_newline)
{
	if (is_newline)
		ft_printf("\n\n");
	ft_printf("====================================================\n");
	ft_printf("  Listening On PID \033[1;33m%d\033[0m..    ", getpid());
	ft_printf("Press \033[0;31mCTRL+C\033[0m to quit\n");
	ft_printf("----------------------------------------------------\n");
}

static void	sighandler(int signum, siginfo_t *info, void *context)
{
	static unsigned char	chr = 0;
	static int				bit = 0;

	(void)context;
	chr |= (signum == SIGUSR2);
	if (++bit < 8)
		chr = chr << 1;
	else
	{
		if (chr)
		{
			kill(info->si_pid, SIGUSR1);
			write(1, &chr, 1);
		}
		else
		{
			kill(info->si_pid, SIGUSR2);
			server_message(1);
		}
		bit = 0;
		chr = 0;
	}
}

int	main(void)
{
	struct sigaction	s_action;

	s_action.sa_sigaction = sighandler;
	s_action.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_action, NULL);
	sigaction(SIGUSR2, &s_action, NULL);
	server_message(0);
	while (1)
		pause();
}
