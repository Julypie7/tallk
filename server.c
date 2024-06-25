/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <ineimatu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 10:11:35 by ineimatu          #+#    #+#             */
/*   Updated: 2024/06/25 11:29:19 by ineimatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include "stdlib.h"
#include "stdio.h"


static char *connect(char *str, char c)
{
	char		*str2;
	int 		i;
	int 		b;

	i = 0;
	b = 0;
	str2 = (char *)malloc(sizeof(char) * (ft_strlen(str)));
	if (!str2)
		return (NULL);
	while (str[i] != '\0')
	{	
		write (1, "1", 1);
		str2[b] = str[i];
		b++;
		i++;
	}
	if (c)
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
	static char	c = 0;
	static char	*str = NULL;
	int			i;

	(void)siginfo;
	(void)context;
	i = 0;
	if (signum == SIGUSR1)
		c |= (1 << bit);
	bit++;
	if (bit == 8)
	{
		if (c)
		{
			if (!str)
			{
				str = malloc(sizeof(char) * 2);
				if (!str)
					return ;
				str[0] = '\0';
				str[1] = '\0';
			}
			str = connect(str, c);
			//printf("%s\n", str);
		}
		if (c == '0')
		{
			if (str)
			{			
				while(str[i])
					write(1, &str[i], 1);
				write(1, "\n", 1);
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
	
	pid = getpid();
	if(!pid)
		write(1, "Pid doesn't exist", 17);
	else
	{	
		write(1, "Server PID is: ", 15);
		ft_putnbr(pid);
		write(1, "\n", 1);
	}
	sigac.sa_sigaction = handl;
	sigac.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sigac, NULL) == -1)
		return (write(2, "Error", 6));
	if (sigaction(SIGUSR2, &sigac, NULL) == -1)
		return (write(2, "Error", 6));
	while (1)
		pause ();
	return (0);
}
