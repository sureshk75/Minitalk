/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schetty <schetty@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 16:51:24 by schetty           #+#    #+#             */
/*   Updated: 2021/10/09 11:02:56 by schetty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	sighandler(int signum, siginfo_t *info, void *context)
{
	static unsigned char	chr = 0;
	static int				bit = 0;

	(void)context;
	chr |= (signum == SIGUSR2);
	chr = chr << 1;
	if (++bit == 8)
	{
		write(1, &chr, 1);
		if (chr)
			kill(info->si_pid, SIGUSR1);
		else
			kill(info->si_pid, SIGUSR2);
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
	ft_printf("Running On PID \033[1;33m%d\033[0m\n", getpid());
	ft_printf("Press \033[0;31mCtrl-C\033[0m to quit\n");
	while (1)
		pause();
}
