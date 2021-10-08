/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schetty <schetty@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 16:51:24 by schetty           #+#    #+#             */
/*   Updated: 2021/10/08 18:04:03 by schetty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	finished(int pid)
{
	ft_printf("\n");
	kill(pid, SIGUSR2);
}

static void	handler(int signum, siginfo_t *info, void *context)
{
	static int				pid = 0;
	static unsigned char	chr = 0;
	static int				bit = 0;

	(void)context;
	pid = info->si_pid;
	chr |= (signum == SIGUSR2);
	if (++bit < 8)
		chr = chr << 1;
	else
	{
		if (chr)
			write(1, &chr, 1);
		else
			finished(pid);
		bit = 0;
		chr = 0;
	}
	kill(pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	s_action;

	s_action.sa_sigaction = handler;
	s_action.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_action, NULL);
	sigaction(SIGUSR2, &s_action, NULL);
	ft_printf("Running On PID \033[1;33m%d\033[0m\n", getpid());
	ft_printf("Press \033[0;31mCtrl-C\033[0m to quit\n");
	while (1)
		pause();
}
