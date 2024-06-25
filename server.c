/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <ineimatu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 10:11:35 by ineimatu          #+#    #+#             */
/*   Updated: 2024/06/25 18:52:12 by ineimatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"


static char *connect(char *str, unsigned char c)
{
	char		*str2;
	int 		i;
	int 		b;

	i = 0;
	b = 0;
	str2 = (char *)malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!str2)
	{
		free(str);
		return (NULL);
	}
	if(!str)
	{
		str2[b] = c;
		str2[b + 1] = '\0';
		return(str2);
	}
	while (str[i] != '\0')
	{	
		str2[b] = str[i];
		b++;
		i++;
	}
	if (str[i] == '\0')
	{
		str2[b] = c;
		b++;
	}
	str2[b] = '\0';
	free (str);
	return (str2);
}
		
static void	handl(int signum, siginfo_t *siginfo, void *context)
{
	static int	bit = 0;
	static unsigned char	c = 0;
	static char	*str = NULL;
	int			i;

	(void)siginfo;
	(void)context;
	i = 0;
	if (signum == SIGUSR1)
		c = c | (1 << bit);
	bit++;
	if (bit == 8)
	{
		if (c != '\0')
		{
			str = connect(str, c);
			if (!str)
			{
				write(2, "malloc error\n", 13);
				return ;
			}
		}
		else
		{
			if (str != NULL)
			{	
				while(str[i] != '\0')
				{
					write(1, &str[i], 1);
					i++;
				}
				free(str);
				str = NULL;
			}	
		}
		bit = 0;
		c = 0;
	}
}

int	main(void)
{
	struct sigaction	sigac;
	int pid;
	sigset_t	sigset;
	
	pid = getpid();
	if(!pid)
		write(1, "Pid doesn't exist", 17);
	else
	{	
		write(1, "Server PID is: ", 15);
		ft_putnbr(pid);
		write(1, "\n", 1);
	}
	sigemptyset(&sigset);
	sigaddset(&sigset, SIGUSR1);
	sigaddset(&sigset, SIGUSR2);
	sigac.sa_mask = sigset;
	sigac.sa_flags = SA_SIGINFO;
	sigac.sa_sigaction = handl;
	if (sigaction(SIGUSR1, &sigac, NULL) == -1)
		return (write(2, "Error!\n", 7));
	if (sigaction(SIGUSR2, &sigac, NULL) == -1)
		return (write(2, "Error!\n", 7));
	while (1)
		pause();
}
