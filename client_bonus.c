/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:40:59 by ineimatu          #+#    #+#             */
/*   Updated: 2024/06/21 10:59:33 by ineimatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handl(int pid, char c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
		{
			g_wait = 1;
			if (c & (1 << bit))
			{
				if (kill(pid, SIGUSR1) == -1)
					write (2, "Error!", 6);
			}
			else
			{
				if (kill(pid, SIGUSR2) == -1)
					write (2, "Error!", 6);
			}
			while (g_wait)
				usleep(10);
			bit++;
	}
}

static void	recieve(int signum, siginfo_t *info, void *context)
{
	(void)context;
	if (signum == SIGUSR2)
		write(1, "Message recieved\n", 17);
	g_wait = 0; 
}

int	main(int argc, char **argv)
{
	struct sigacion sigac;
	int i;
	
	i = -1;
	if (argc != 3 || check_digit(argv[1]) == 0 || ft_strlen(argv[2]) == 0)
		return (write(2, "incorrect arguments\n", 20));
	sigac.sa_sigaction = recieve;
	sigac.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sigac, NULL) == -1)
		return (write(2, "Error", 6));
	if (sigaction(SIGUSR2, &sigac, NULL) == -1)
		return (write(2, "Error", 6));
	while (argv[2][++i])
		handl(ft_atoi(argv[1]), argv[2]);
	return (0);
}	
