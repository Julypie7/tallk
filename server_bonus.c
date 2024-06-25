/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 10:39:33 by ineimatu          #+#    #+#             */
/*   Updated: 2024/06/21 10:49:46 by ineimatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	handler(int signum, siginfo_t *siginfo, void *context)
{
	static int	bit = 0;
	static char	c = 0;
	int			signal;

	signal = SIGUSR1;
	(void)context;
	if (signum == SIGUSR1)
		c |= (1 << bit);
	bit++;
	if (bit == 8)
	{
		if (!c)
			signal = SIGUSR2;
		write(1, &c, 1);
		bit = 0;
		c = 0;
	}
	kill(info->si_pid, signal);
}

int	main(void)
{
	struct sigaction	sigac;
	int pid;
	
	pid = getpid();
	if(!pid)
		write(1, "Pid doesn't exist", 17);
	else
	{	
		write(1, "Server PID is: ", 15);
		ft_putnbr(pid);
		write(1, "\n", 1);
	}
	sigac.sa_sigaction = handler;
	sigac.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sigac, NULL) == -1)
		write(2, "Error", 6);
	if (sigaction(SIGUSR2, &sigac, NULL) == -1)
		write(2, "Error", 6);
	while (1)
		pause ();
	return (0);
}
